#include <iostream>
#include "ProductionDBadapter.h"

ProductionDBadapter::ProductionDBadapter( Config config ) {
	conn.connect(
		config.database.databaseName.c_str(),
		config.database.url.c_str(),
		config.database.usr.c_str(),
		config.database.password.c_str(),
		config.database.port );

	if( conn.connected() == false ) {
		std::cout << "DB ???\n";
		throw std::runtime_error( "db not connected" );
	}
}

bool ProductionDBadapter::areLocationConnected( int one, int secend ) {
	auto a = conn.query( "select * from loc_connections where source = " ) ;
	a << one << " and  destination = " << secend << " ; ";

	if( not a ) {
		return false;
	}

	for( auto i : a.store() ) {
		return true;
	}

	return false;
}

bool ProductionDBadapter::isSign( std::string username, std::string password ) {
	auto a = conn.query( "select player_id from users where username " ) ;
	a << " like '" << username << "' and  password like '" << password << "' ; ";

	if( not a ) {
		std::cout << "???\n";
		return false;
	}

	for( auto i : a.store() ) {
		return true;
	}

	return false;
}
Player_id ProductionDBadapter::getPlayer_idByUsername( std::string username ) {
	auto a = conn.query( "select player_id from users where username " ) ;
	a << " like '" << username << "';";

	if( not a ) {
		std::cout << "???\n";
		return 0;
	}

	for( auto i : a.store() ) {
		return i[0];
	}

	return 0;
}
std::vector<Domain::Localization::Connection> ProductionDBadapter::getLocationConnections(int id){
	std::vector<Domain::Localization::Connection> res;
	auto a = conn.query( "select description,destination from loc_connections where source = " ) ;
	a << id << " ;";
	
	if( not a ) {
		std::cout << "???\n";
		throw std::runtime_error("database explode");
	}

	Domain::Localization::Connection temp;
	for( auto i : a.store() ) {
		i[0].to_string(temp.description);
		temp.destination = i[1];
		res.push_back(temp);
	}
	return res;
}

pair<std::string,std::string> ProductionDBadapter::getLocationNameDescription(int id){ //TODO
	pair<std::string,std::string> res;
	
	auto a = conn.query( "select location_name,file_name from location where id = " ) ;
	a << id << " ;";
	
	if( not a ) {
		std::cout << "???\n";
		throw std::runtime_error("database explode");
	}

	for( auto i : a.store() ) {
		i[0].to_string(res.first);
		i[1].to_string(res.secend);
	}
	
	return res;
}
