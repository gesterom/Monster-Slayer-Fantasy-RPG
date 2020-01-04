#include "Server.h"
#include <iostream>

void Server::run() {
	if( db == nullptr ) {
		std::cout << "[ERROR] not database init\n";
		return;
	}

	while( true ) { 
		try {
			Command com = commandQ.pop();

			if( com.data[0] == "move" ) {
				int destinationLocation = std::stoi( com.data[1] );
				int currentPlayerLocation = current.getPlayerLocation( com.player_id );
				bool LocationsIsConnected = db->areLocationConnected( currentPlayerLocation, destinationLocation );

				if( LocationsIsConnected ) {
					backBuffer.setLocationForPlayer( com.player_id, destinationLocation );
				}

				//TEST
				std::cout << "[TEST] " << backBuffer.getPlayerLocation( com.player_id ) << std::endl;
			}
		}
		catch( std::exception& e ) {
			std::cout << "[ Server Exception ] " << e.what() << std::endl;
		}
	}
}
