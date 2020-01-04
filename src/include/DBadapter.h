#pragma once
#include "Domain.h"

class DBadapter {
  public:
	virtual Domain::location getLocationById( int id ) = 0;
	virtual bool getConnectionLocation( int oneLocation, int secendLocation ) = 0;
	virtual bool isSign( std::string username, std::string password ) = 0;
	virtual Player_id getPlayer_idByUsername( std::string username ) = 0;
	virtual ~DBadapter() {}
};

