#pragma once
#include <string>
#include <stdint.h>
#include <iostream>

#include "Tokens.h"


using Player_id = uint32_t;

class Authorization {
	DBadapter* db;
	Tokens& tokens;
  public:
	Authorization( DBadapter* dba, Tokens& tok ) : db( dba ), tokens( tok ) {}
	std::string login( std::string username, std::string password ) {
		bool isIN_DB = db->isSign( username, password );

		if( isIN_DB == true ) {
			return tokens.getNewToken( username );
		}
		else {
			return "";
		}
	}
	Player_id getPlayerId( std::string token ) {
		std::cout << "TOKEN TO VALIDATION : " << token << " s : " << token.size() << "\n";
		std::string username = tokens.getUsernameBy( token );
		std::cout << "User name : " << username << std::endl;

		if( username == "" ) {
			return 0;    // invalid user;
		}

		std::cout << "User name : " << username << std::endl;
		return db->getPlayer_idByUsername( username );
	}
	/*  bool isAuthorized(Player_id player_id){
		if(player_id == 0)
			return false;
		return true;
		//std::string username = db->getUsernameByPlayer_id(playerid);
	    }*/
};
