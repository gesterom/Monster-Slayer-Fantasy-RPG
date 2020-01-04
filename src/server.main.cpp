#include <iostream>
#include <thread>
#include <mysql++/mysql++.h>

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/NetException.h>

#include "ProductionDBadapter.h"
#include "CommandQueue.h"
#include "Server.h"
#include "Config.h"
#include "Authorization.h"

Config getConfig()
{
	Config config =
	{
		{
			"localhost",//database url
			3306,//database port
			"gameServer",//database user
			"",//password,
			"game"//databaseName
		},
		{8085}
	};
	return config;
}
std::vector<std::string> sub(std::string data)
{
	std::vector<std::string> res;
	std::string word;
	for(size_t i = 0 ; i < data.size(); i++)
	{
		if(data[i] == ' ') {
			res.push_back(word);
			word="";
		}else{
			word+=data[i];
		}
	}
	if(word!="") res.push_back(word);
	return res;
}
class IOHandler : public Poco::Net::TCPServerConnection {
	private:
		uint32_t getIntFromSocket(Poco::Net::StreamSocket& socket){
			uint32_t res = 0;
			uint8_t buf;
			while (true){
				int n = socket.receiveBytes( &buf ,sizeof(buf));
				if( buf >='0' and buf <='9'){
					res=res*10;
					res=res + buf-'0';
				}else{ break;}
			}
			return res;
		}
		void handleGet(Command com)
		{
			//TODO
			std::cout<<"data: "<<com.data[0]<<std::endl;
			this->send(com.data[0]);
		}
	uint8_t header[8] = {}; //"AAAA C "
	uint8_t buf[1024]={};
	Command reciveCommand(){
		int n;
		//while(header[0]=='\0'){
			n = socket().receiveBytes(header,7);
		//}
		//socket().receiveBytes(header+1,6);
		//FIXME
		//header[8]='\0';
			
		if(n==0) {
			return Command{c_error_t::too_big};
		}

		uint32_t size = getIntFromSocket(socket());
		if(size > 1024 ) { return Command{c_error_t::too_big};}
		n = socket().receiveBytes(buf,size);
		if( n == 0 ) { return Command{c_error_t::too_small};}
		if( n >= 1024) { return Command{c_error_t::too_big};}
		buf[n+1] = '0';
		return Command{
										header[5],
										auth.getPlayerId(std::string( (const char*)header,4)),
										sub(std::string((const char*)buf,n))
										};
	}
	//void login();
	CommandQueue& q;
	bool isLogin = false;
	void send(std::string str){
		str = std::to_string(str.size()+1) + " " + str;
		socket().sendBytes(str.c_str(),str.size());
	}
	void shutdownSocket(std::string msg){
		this->send(msg);
		std::cout<<"[-----]\n";
		socket().shutdown();
	}
	Authorization& auth;
	public:
		IOHandler(const Poco::Net::StreamSocket& socket, CommandQueue& commandQ ,Authorization& a ) : 
						Poco::Net::TCPServerConnection(socket),
						q(commandQ),
						auth(a) {}
		void run() override {
			try{
				bool isConnected = true;
				while(isConnected)
				{
					Command com = reciveCommand();
					std::cout<<"[new command]\n";
					if(com.error != c_error_t::none){
						this->shutdownSocket("Invalid Command");
						return;
					}
					std::cout<<"Player id : "<<com.player_id<<std::endl;
					std::cout<<"Type : "<<com.type<<std::endl;
					std::cout<<"Error : "<<(int)com.error<<std::endl;
					bool isAuthorized = ( com.player_id != 0 ); 
					if(com.type == 'C' and isAuthorized ){
						//COMMAND
						q.push( com );
						this->send("OK\n");
					}
					else if(com.type == 'G' and isAuthorized ){
						//GET
						handleGet(com);
					}
					else if(com.type == 'L'){
							std::cout<<"size : "<<com.data.size()<<std::endl;
							if(com.data.size() < 2) {
								this->shutdownSocket("not enough argument \n");
								return;
							} 
							std::cout<<"user : "<<com.data[0]<<std::endl;
							std::cout<<"pass : "<<com.data[1]<<std::endl;
							std::string token = auth.login(com.data[0],com.data[1]);
							std::cout<<"token : ["<<token<<"] : size: "<<token.size()<<std::endl;
							if( token != "" ){
								this->send( std::string("TOKEN : ") + token + " \n");
							}else{
								this->send("invalid username or password");
							}
					}
					else{
						std::cout<<"Type : "<<com.type<<std::endl;
						this->shutdownSocket("invalid header");
					}
					//if "get" go to dbadapter;
					//if "command" go to Server object
					std::cout<<"-----\n";
				}
			}
			catch(Poco::Net::NetException& e)
			{
				std::cerr<<"[Thread : "<<std::this_thread::get_id<<" ] "<<e.what()<<std::endl;
			}
		}
};

class IOHandlerFactory : public Poco::Net::TCPServerConnectionFactory{
	CommandQueue& q;
	Authorization& auth;
	public:
	virtual Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket) override{
		return new IOHandler(socket,q,auth);
	}
	IOHandlerFactory(CommandQueue& commandQ, Authorization& a) : q(commandQ), auth(a) {}
	virtual ~IOHandlerFactory(){}
};

int main(int argc, char** args)
try
{
	if(argc<2){
		std::cout<<"Pass password as secend argument\n";
		return -1;
	}	
	Config config = getConfig();
	config.database.password = args[1];
	
	std::cout<<"Database : ";
	DBadapter* dba = new ProductionDBadapter(config);
	std::cout<<"[DONE]\n";
	
	std::cout<<"CommandQ ";	
	CommandQueue commandQ;
	std::cout<<"[DONE]\n";
	
	std::cout<<"Tokens ";	
	Tokens tokens(60);
	std::cout<<"[DONE]\n";
	
	std::cout<<"Authorization ";	
	Authorization auth(dba,tokens);
	std::cout<<"[DONE]\n";
	
	std::cout<<"TCPServer ";	
	Poco::Net::TCPServer tcpserver(new IOHandlerFactory(commandQ,auth),config.server.port);
	std::cout<<"[DONE]\n";
	
	std::cout<<"Server ";	
	Server server(commandQ,dba);
	std::cout<<"[DONE]\n";
	
	std::cout<<"TCPServer Start ";	
	tcpserver.start();
	std::cout<<"[DONE]\n";

	std::cout<<"Server Start ";	
	server.run();	
	std::cout<<"[DONE]\n";

	/*	std::string input;
	while(input!="exit"){
		getline(std::cin,input);
	}*/
	delete dba;
}
catch(std::exception& e)
{
	std::cerr<<e.what()<<std::endl;
}
