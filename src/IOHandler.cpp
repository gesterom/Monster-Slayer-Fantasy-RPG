#include "IOHandler.h"
#include "Common.h"
#include <iostream>

#include "Common.h"


void IOHandler::run() {
	try {
		bool isConnected = true;

		while( isConnected ) {
			Command com = reciveCommand();
			std::cout << "[new command]\n";

			if( com.error != c_error_t::none ) {
				this->shutdownSocket( "Invalid Command" );
				return;
			}

			bool isAuthorized = ( com.player_id != 0 );

			if( com.type == 'C' and isAuthorized ) {
				//COMMAND
				q.push( com );
				this->send( "OK\n" );
			}
			else if( com.type == 'G' and isAuthorized ) {
				//GET
				handleGet( com );
			}
			else if( com.type == 'L' ) {
				if( handleLogin(com) == false ){
					return;
				}
			}
			else {
				std::cout << "Type : " << com.type << std::endl;
				this->shutdownSocket( "invalid header" );
			}

			//if "get" go to dbadapter;
			//if "command" go to Server object
			std::cout << "-----\n";
		}
	}
	catch( Poco::Net::NetException& e ) {
		std::cerr << "[Thread : " << std::this_thread::get_id << " ] " << e.what() << std::endl;
	}
}

bool IOHandler::handleLogin(Command& com){
	if( com.data.size() < 2 ) {
		this->shutdownSocket( "not enough argument \n" );
		return false;
	}

	std::string token = auth.login( com.data[0], com.data[1] );
	std::cout << "LOGIN | TOKEN : ["<<token<<"] , username : "<<com.data[0]<<std::endl; 

	if( token != "" ) {
		this->send( std::string( "TOKEN : " ) + token + " \n" );
		return true;
	}
	else {
		this->send( "invalid username or password" );
		return false;
	}
}

bool IOHandler::handleGet( Command& com ) {
	//TODO GET handler
	if(com.data.size() > 1 and com.data[0] == "localization"){
		auto loc = dao.getLocalization(std::stoi(com.data[1]));
		this->send(std::string("LOCALIZATION ") + loc.serialize());
	}
	std::cout << "data: " << com.data[0] << std::endl;
	this->send( com.data[0] );
	return true;
} 

Command IOHandler::reciveCommand() {
	int n;
	n = socket().receiveBytes( header, 7 );
	
	if( n == 0 ) {
		return Command{c_error_t::too_big};
	}

	uint32_t size = getIntFromSocket( socket() );

	if( size > 1024 ) {
		return Command{c_error_t::too_big};
	}

	n = socket().receiveBytes( buf, size );

	if( n == 0 ) {
		return Command{c_error_t::too_small};
	}

	if( n >= 1024 ) {
		return Command{c_error_t::too_big};
	}

	buf[n + 1] = '0';
	return Command{
		header[5],
		auth.getPlayerId( std::string( ( const char* )header, 4 ) ),
		sub( std::string( ( const char* )buf, n ) )
	};
}

void IOHandler::send( std::string str ) {
	str = std::to_string( str.size() + 1 ) + " " + str;
	socket().sendBytes( str.c_str(), str.size() );
}
void IOHandler::shutdownSocket( std::string msg ) {
	this->send( msg );
	std::cout << "[-----]\n";
	socket().shutdown();
}
