#pragma once

#include <unordered_map>
#include <chrono>

class Tokens{
	std::unordered_map<std::string,std::chrono::time_point> map;
	public:
	Tokens(int expireTimeSecends);
	bool isValidToken(std::string token);
	std::string getNewToken();
	void refreshToken(std::string token);
};
