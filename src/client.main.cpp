#include <iostream>
#include <unistd.h>
#include <string>
#include <stdint.h>

#include <Poco/Net/StreamSocket.h>

#include "Common.h"

using Socket_t = Poco::Net::StreamSocket;

std::string login( Socket_t& sock, std::string username, std::string password ) {
	char buff[1024];
	std::string req = "AAAA L ";
	std::string data = username + " " + password;
	data = std::to_string( data.size() ) + " " + data;
	req = req + data;
	sock.sendBytes( req.c_str(), req.size() );
	int n = getIntFromSocket( sock );
	sock.receiveBytes( buff, n );
	std::string token = sub( std::string( buff, n ) )[2];
	char zzz[5] = {};

	for( int i = 0; i < 4; i++ ) {
		zzz[i] = token[i];
	}

	std::cout << "[" << token << "]\n=====================\n";
	return std::string( zzz, 4 );
}

std::string sendG( Socket_t& sock, std::string token, std::string data ) {
	char buff[1024];
	char zeff[8];
	std::string req( zeff, 7 );
	req = token + " G ";
	data = std::to_string( data.size() ) + " " + data;
	req = req + data;
	sock.sendBytes( req.c_str(), req.size() );
	int n = getIntFromSocket( sock );
	n = sock.receiveBytes( buff, n );
	return std::string( buff, n );
}

bool sendC( Socket_t& sock, std::string token, std::string data ){
	char buff[1024];
	char zeff[8];
	std::string req( zeff, 7 );
	req = token + " C ";
	data = std::to_string( data.size() ) + " " + data;
	req = req + data;
	sock.sendBytes( req.c_str(), req.size() );
	
	int n = getIntFromSocket( sock );
	n = sock.receiveBytes( buff, n );
	std::string respond( buff, n );
	if(respond == "OK\n"){	
		return true;
	}
	else{
		return false;
	}
}

int main( int argc, char** args )

try {
	if( argc < 2 ) {
		return -1;
	}
	uint16_t port = std::stoi( args[1] );
	std::string username,password;
	getline(std::cin,username);
	getline(std::cin,password);
	std::cout<<"username : "<<username<<std::endl;
	std::cout<<"password : "<<password<<std::endl;
	Socket_t sock;
	for( int i = 0; i < 100 ; i++){
		Poco::Net::SocketAddress adr{"127.0.0.1", port};
		sock.connect( adr );
		std::string token = login( sock, username, password );
		std::string r = sendG( sock, token, "localization" );
		std::cout<<"RECV : ["<<r<<"]\n";
		bool zzz = sendC( sock, token, "move 3" );
		std::cout<<"RECV : ["<<zzz<<"]\n";
	}
	std::string input;

	while( input != "exit" ) {
		getline( std::cin, input );
	}
}
catch( std::exception& e ) {
	std::cout << e.what() << std::endl;
}
