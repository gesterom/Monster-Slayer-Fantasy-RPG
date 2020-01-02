#include <iostream>
#include <thread>
#include <mysql++/mysql++.h>

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/NetException.h>

#include "ProductionDBadapter.h"

#include "Config.h"

class IOHandler : public Poco::Net::TCPServerConnection {
	private:
		int getIntFromSocket(Poco::Net::StreamSocket& socket,char delimiter){
			int res = 0;
			uint8_t buf;
			while (true){
				int n = socket.receiveBytes(&buf,sizeof(buf));
				if(buf>='0' and buf <='9'){
					res+=buf;
					res=res*10;
				}else{ break;}
			}
			return res;
		}
	uint8_t buf[1024]={};
	public:
		IOHandler(const Poco::Net::StreamSocket& socket) : Poco::Net::TCPServerConnection(socket){}
		void run() override {
			try{
				bool isConnected = true;
				while(isConnected)
				{
					int size = getIntFromSocket(socket(),' ');
					if(size > 1024 and size < 0 ) {socket().shutdown(); break;}
					int n = socket().receiveBytes(buf,size);
					if( n == 0 ) {socket().shutdown(); break;}
					if( n >= 1024) {socket().shutdown(); break;}
					std::string res( (const char*) buf,n);
					//VERIFY USR
					//if "get" go to dbadapter;
					//if "command" go to Server object
					std::cout<<"recv : [ "<<res<<" ] "<<std::endl;
					socket().sendBytes(res.c_str(),res.size());
				}
			}
			catch(Poco::Net::NetException& e)
			{
				std::cout<<"[Thread : "<<std::this_thread::get_id<<" ] "<<e.what()<<std::endl;
			}
		}
};

class IOHandlerFactory : public Poco::Net::TCPServerConnectionFactory{
	public:
	virtual Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket) override{
		return new IOHandler(socket);
	}
	IOHandlerFactory(){}
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
	DBadapter* dba = new ProductionDBadapter(config);
	
	Poco::Net::TCPServer server(new IOHandlerFactory(),config.server.port);
	server.start();
	std::string input;
	while(input!="exit"){
		getline(std::cin,input);
	}
	delete dba;
}
catch(std::exception& e)
{
	std::cerr<<e.what()<<std::endl;
}
