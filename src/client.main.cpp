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
	std::cout << "RECV : " << std::string( buff, n ) << std::endl;
	return std::string( buff, n );
}

int main( int argc, char** args )

try {
	if( argc < 4 ) {
		return -1;
	}

	uint16_t port = std::stoi( args[1] );
	std::string username = args[2];
	std::string password = args[3];
	Socket_t sock;
	std::string s_adr = "localhost:";
	s_adr = s_adr + std::to_string( port );
	std::cout << s_adr << std::endl;
	Poco::Net::SocketAddress adr{"127.0.0.1", port};
	sock.connect( adr );
	std::string token = login( sock, username, password );
	std::string r = sendG( sock, token, "halo???" );
	std::string input;

	while( input != "exit" ) {
		getline( std::cin, input );
	}
}
catch( std::exception& e ) {
	std::cout << e.what() << std::endl;
}
