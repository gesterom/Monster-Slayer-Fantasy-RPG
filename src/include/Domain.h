#pragma once
#include <string>
#include <vector>
#include <stdint.h>

namespace Domain
{
	struct bar{
		int max = 100 ;
		int min = 0;
		int current = 100;
	};
	struct statistic{
		int base;
		int bias;
		double percent;
	};
	struct location{
		int id;
		std::string name;
		std::string desFileName;
		std::vector<int> connections;
	};
	struct character{
		bar hp;
		bar mana;
	};
}

using Player_id = uint32_t;
