#include "Tokens.h"

#include <iostream>

Tokens::Tokens(int expireTimeSecends){
	this->t_expire_duration = std::chrono::seconds(expireTimeSecends);
}

std::string genRandomStringToken(int size)
{
	std::string res;
	res.reserve(size);
	char tab[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-_";
	for(int i = 0 ; i < size ; i++)
	{
		res+=tab[rand()%65];
	}
	return res;
}

std::string Tokens::getNewToken(std::string username){
	auto t_now = std::chrono::system_clock::now();

	Token token{username,t_now+t_expire_duration};
	std::string toks;
	while(true){
		toks = genRandomStringToken(4);
		auto it = map.find(toks);
		if(it == map.end()){
			map[toks] = token;
			return toks;
			break;
		}
		if ( it->second.expiry < std::chrono::system_clock::now() )
		{
			map.erase(it);
		}
	}
	return "XXXX";
}
bool Tokens::isValidToken(std::string token){
	auto it = map.find(token);
	if(it == map.end()){
		return false;		
	}
	if ( it->second.expiry < std::chrono::system_clock::now() )
	{
		map.erase(it);
		return false;
	}
	return true;
}
void Tokens::refreshToken(std::string token)
{
	auto it = map.find(token);
	if(it == map.end()){
		return;
	}
	if ( it->second.expiry < std::chrono::system_clock::now() )
	{
		map.erase(it);
		return;
	}
	it->second.expiry = std::chrono::system_clock::now() + this->t_expire_duration;
	return;
}
std::string Tokens::getUsernameBy(std::string token){
	auto it = map.find(token);
	if(it == map.end()){
		return "";
	}
	if ( it->second.expiry < std::chrono::system_clock::now() )
	{
		map.erase(it);
		return "";
	}
	return it->second.username;
}
