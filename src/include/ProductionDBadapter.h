#pragma once
#include <string>
#include <mysql++/mysql++.h>


#include "Config.h"
#include "Domain.h"
#include "DBadapter.h"

class ProductionDBadapter : public DBadapter
{	
	private:
	mysqlpp::Connection conn;
	public:
	ProductionDBadapter ( Config config);
	virtual Domain::location getLocationById(int id);
};
