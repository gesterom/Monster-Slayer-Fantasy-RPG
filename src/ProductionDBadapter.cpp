
#include "ProductionDBadapter.h"

ProductionDBadapter::ProductionDBadapter(Config config)
{
	conn.connect(
								config.database.databaseName.c_str(),
								config.database.url.c_str(),
								config.database.usr.c_str(),
								config.database.password.c_str(),
								config.database.port);
}

Domain::location ProductionDBadapter::getLocationById(int id){
	return Domain::location{};
}

