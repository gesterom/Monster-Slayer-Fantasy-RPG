#pragma once
#include <stdint.h>
#include <iostream>
#include <mutex>
#include <future>

using Player_id = uint32_t;
using Location_id = uint32_t;

class GameState {
	std::unordered_map<Player_id, Location_id> players_location; //player_id, location_id
  public:
	int setLocationForPlayer( Player_id player_id, Location_id newLocation_id ) { // 0 good !=0 error
		auto it = players_location.find( player_id );

		if( it == players_location.end() ) {
			return -1; //not found
		}

		players_location[player_id] = newLocation_id;
		return 0;
	}
	int loadPlayer( Player_id player_id, Location_id location_id ) {
		std::cerr<<"--- LOAD [I]---\n";
		auto it = players_location.find( player_id );

		if( it != players_location.end() ) {
			std::cerr<<"--- LOAD [E]---\n";
			return -1; //found
		}

		players_location[player_id] = location_id;
		std::cerr<<"--- LOAD [O]---\n";
		return 0;
	}
	Location_id getPlayerLocation( Player_id player_id ) {
		std::cerr<<"i hate u x1\n"<<"Player_id: "<<player_id<<std::endl;
		auto it = players_location.find(player_id);
		std::cerr<<"i hate u x2\n";
		if( players_location.end() == it ) {
		std::cerr<<"i hate u x3\n";
			return -1; //not found
		}
		std::cerr<<"i hate u x4\n";
		return players_location.at( player_id );
	}
	void saveToDB() {} //TODO
};
