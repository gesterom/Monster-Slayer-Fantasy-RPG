#pragma once
#include <string>
#include <stdint.h>
#include <iostream>

#include "Tokens.h"
#include "DBadapter.h"

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
		std::string username = tokens.getUsernameBy( token );

		if( username == "" ) {
			return 0;    // invalid user;
		}

		return db->getPlayer_idByUsername( username );
	}
};
