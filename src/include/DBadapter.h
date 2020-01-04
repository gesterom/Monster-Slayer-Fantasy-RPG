#pragma once

#include "Domain.h"
#include "Domain/Localization.h"

template<typename T1,typename T2>
struct pair{
	T1 first;
	T2 secend;
};

class DBadapter {
  public:
	virtual bool areLocationConnected( int oneLocation, int secendLocation ) = 0;
	virtual bool isSign( std::string username, std::string password ) = 0;
	virtual Player_id getPlayer_idByUsername( std::string username ) = 0;
	virtual std::vector<Domain::Localization::Connection> getLocationConnections(int id) = 0;
	virtual pair<std::string,std::string> getLocationNameDescription(int id) = 0;
	virtual ~DBadapter() {}
};

