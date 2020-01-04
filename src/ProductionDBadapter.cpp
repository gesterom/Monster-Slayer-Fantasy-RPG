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

Domain::location ProductionDBadapter::getLocationById( int id ) {
	return Domain::location{};
}
bool ProductionDBadapter::getConnectionLocation( int one, int secend ) {
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
