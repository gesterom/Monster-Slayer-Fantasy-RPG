#pragma once
#include <stdint.h>

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
		auto it = players_location.find( player_id );

		if( it != players_location.end() ) {
			return -1; //found
		}

		players_location[player_id] = location_id;
		return 0;
	}
	Location_id getPlayerLocation( Player_id player_id ) {
		auto it = players_location.find( player_id );

		if( it == players_location.end() ) {
			return -1; //not found
		}

		return players_location.at( player_id );
	}
	void saveToDB() {} //TODO
};
