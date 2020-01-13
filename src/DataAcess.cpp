#include "DataAcess.h"
#include <fstream>
#include <iostream>

bool isPrintable(char c){
	return ( c == '\t' or c== '\n' or
			( c>= 0x20 and c<= 0x7B) );
}

std::string readWholeFile(std::string& filename){
	filename="./assets/"+filename;
	std::fstream file(filename);
	std::string res;
	char c;
	while(file.good()){
		file.get(c);
		if( isPrintable(c) ){
			res+=c;
		}else{
			return res;
		}
	}
	return res;
}

Domain::Localization DataAcess::getLocalizationOfPlayer(int player_id){
	Domain::Localization res;
	std::cerr<<"1.a : "<<std::endl;
	uint32_t loc_id = server.whereIsPlayer(player_id);
	std::cerr<<"LOC_ID : "<<loc_id<<std::endl;
	res.connections = db->getLocationConnections(loc_id);
	std::cerr<<"conn size : "<<res.connections.size()<<std::endl;
	auto a = db->getLocationNameDescription(loc_id);
	std::cerr<<"a.1 : "<<a.first<<std::endl;
	std::cerr<<"a.2 : "<<a.secend<<std::endl;
	res.description = readWholeFile(a.secend);
	std::cerr<<"File : "<<"xD"<<std::endl;
	res.name = a.first;	
	return res;
}

