#include <iostream>
#include "ProductionDBadapter.h"

ProductionDBadapter::ProductionDBadapter(Config config)
{
	conn.connect(
								config.database.databaseName.c_str(),
								config.database.url.c_str(),
								config.database.usr.c_str(),
								config.database.password.c_str(),
								config.database.port);
	if(conn.connected() == false ){
		std::cout<<"DB ???\n";
		throw std::runtime_error("db not connected");
	}
}

Domain::location ProductionDBadapter::getLocationById(int id){
	return Domain::location{};
}
bool ProductionDBadapter::getConnectionLocation(int one,int secend){
	return true; //TODO
}

bool ProductionDBadapter::isSign(std::string username,std::string password){
	auto a = conn.query("select player_id from users where username ") ; //conn.query("set @aaa = 'select player_id from users where username like ? and password like ?';");
	a<<" like '"<<username<<"' and  password like '"<<password<<"' ; ";
	if( not a ){
		std::cout<<"???\n";
	 return false;
	}
		
	for(auto i : a.store()){
		std::cout<<"xxxxxxxxxxxxxx ["<<i[0]<<"]"<<std::endl;	
		return true;	
	}
	return false;
}
Player_id ProductionDBadapter::getPlayer_idByUsername(std::string username){
	return 1;
}
