#pragma once

#include <unordered_map>
#include <chrono>
#include <stdint.h>
using Player_id = uint32_t;

struct Token {
	std::string username;
	//Player_id player_id;
	std::chrono::system_clock::time_point expiry;
};

class Tokens {

	std::unordered_map<std::string, Token> map;
	std::chrono::seconds t_expire_duration;
  public:
	Tokens( int expireTimeSecends );
	bool isValidToken( std::string token );
	std::string getNewToken( std::string username );
	void refreshToken( std::string token );
	std::string getUsernameBy( std::string token );
};
