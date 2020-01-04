#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace Domain{
	struct Localization
	{
		struct Connection{
			std::string description;
			int 				destination;
			std::string serialize(){
				return description+";"+std::to_string(destination);
			}
		};
		std::string name;
		std::string description;
		std::vector<Connection> connections;
		
		std::string serialize(){ 
			std::string res = name + " " + std::to_string(connections.size()) + " ";
			for(auto i : connections){
				res+=i.serialize()+" ";
			}
			res+=" #"+description;
			return res;
		}
	};
}
