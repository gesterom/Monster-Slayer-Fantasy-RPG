#pragma once
#include <string>
#include <vector>
#include <stdint.h>

using Player_id = uint32_t;

enum class c_error_t : int {
	none = 0,
	too_big = 1,
	too_small = 2,
};

struct Command {
	c_error_t error;
	//std::string username;
	Player_id player_id;
	std::vector<std::string> data;
	uint8_t type;

	Command( uint8_t type, Player_id player_id, std::vector<std::string>&& arg ) {
		data = arg;
		this->type = type;
		this->player_id = player_id;
		this->error = c_error_t::none;
	}
	Command( c_error_t error ) {
		this->error = error;
	}
	std::string serialize(){
		return "TODO";
	}
};
