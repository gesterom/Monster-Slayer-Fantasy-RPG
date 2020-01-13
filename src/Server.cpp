#include "Server.h"
#include <iostream>

void Server::run() {
	if( db == nullptr ) {
		std::cout << "[ERROR] not database init\n";
		return;
	}

	while( true ) { 
		Command com = commandQ.pop();
		this->execCommand(com);
	}
}
int Server::whereIsPlayer(int player_id){
	std::cerr<<"Server : to nie moja winna\n";
	return current.getPlayerLocation( player_id );
}
bool Server::loginPlayer(int player_id){
	int loc_id = db->getPlayerLocation(player_id);
	backBuffer.loadPlayer(player_id,loc_id);
	current.loadPlayer(player_id,loc_id); //FIXME
	return true;
}

void Server::execCommand(Command& com){
	try {
		if( com.data.size() > 0 and com.data[0] == "move" ) {
				int destinationLocation = std::stoi( com.data[1] );
				int currentPlayerLocation = current.getPlayerLocation( com.player_id );
				bool LocationsIsConnected = db->areLocationConnected( currentPlayerLocation, destinationLocation );

				if( LocationsIsConnected ) {
					backBuffer.setLocationForPlayer( com.player_id, destinationLocation );
				}
			}
			else if( com.type == 'L' ){
				this->loginPlayer(com.player_id);
			}
		}
		catch( std::exception& e ) {
			std::cout << "[ Server Exception ] " << e.what() << std::endl;
		}
}
