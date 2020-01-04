#pragma once
#include <string>
#include <mysql++/mysql++.h>


#include "Config.h"
#include "Domain.h"
#include "DBadapter.h"

class ProductionDBadapter : public DBadapter {
  private:
	mysqlpp::Connection conn;
  public:
	ProductionDBadapter ( Config config );
	virtual bool getConnectionLocation( int one, int secend ) override;
	virtual bool isSign( std::string username, std::string password ) override;
	virtual Player_id getPlayer_idByUsername( std::string username ) override;
	virtual Domain::location getLocationById( int id );
};
