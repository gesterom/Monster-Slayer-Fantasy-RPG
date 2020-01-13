#pragma once
#include <string>
#include <mysql++/mysql++.h>


#include "Config.h"
#include "Domain.h"
#include "Domain/Localization.h"
#include "DBadapter.h"

class ProductionDBadapter : public DBadapter {
  private:
	mysqlpp::Connection conn;
  public:
	ProductionDBadapter ( Config config );
	virtual bool areLocationConnected( int one, int secend ) override;
	virtual bool isSign( std::string username, std::string password ) override;
	virtual Player_id getPlayer_idByUsername( std::string username ) override;
	virtual std::vector<Domain::Localization::Connection> getLocationConnections(int id) override;
	virtual pair<std::string,std::string> getLocationNameDescription(int id) override;
	virtual int getPlayerLocation(int player_id) override; 
	virtual ~ProductionDBadapter() {}
};
