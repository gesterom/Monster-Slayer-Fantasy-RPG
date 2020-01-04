#include <iostream>
#include <unistd.h>
#include <string>
#include <stdint.h>

#include <Poco/Net/StreamSocket.h>

using Socket_t = Poco::Net::StreamSocket;

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

std::string login(Socket_t& sock,std::string username, std::string password)
{
	char buff[1024];
	std::string req = "AAAA L ";
	std::string data =username+" "+password;
	data=std::to_string(data.size()) + " "+ data;
	req=req+data;
	int z = sock.sendBytes(req.c_str(),req.size());
	int n = getIntFromSocket(sock);
	int a = sock.receiveBytes(buff,n);
	std::string token = sub(std::string(buff,n))[2];
	char zzz[5] = {};
	for(int i = 0; i < 4; i++){
		zzz[i] = token[i];
	}
	std::cout<<"["<<token<<"]\n=====================\n";
	return std::string(zzz,4);
}

std::string sendG(Socket_t& sock, std::string token, std::string data){
	char buff[1024];
	char zeff[8];
	std::string req(zeff,7);
	req=token+" G ";
	data=std::to_string(data.size())+" "+data;
	req = req + data;
	int z = sock.sendBytes(req.c_str(),req.size());
	int n = getIntFromSocket(sock);
	n = sock.receiveBytes(buff,n);
	std::cout<<"RECV : "<<std::string(buff,n)<<std::endl;
	return std::string(buff,n);
}

int main(int argc, char** args)
try
{
	if(argc<4) return -1;
	uint16_t port = std::stoi(args[1]);
	std::string username = args[2];
	std::string password = args[3];
	Socket_t sock;
	std::string s_adr = "localhost:";
	s_adr=s_adr+std::to_string(port);
	std::cout<<s_adr<<std::endl;
	Poco::Net::SocketAddress adr{"127.0.0.1",port};
	sock.connect(adr);
	std::string token = login(sock,username,password);
	std::string r = sendG(sock,token,"halo???");
	std::string input;
	while(input!="exit"){
		getline(std::cin,input);
	}
}
catch( std::exception& e)
{
	std::cout<<e.what()<<std::endl;
}
