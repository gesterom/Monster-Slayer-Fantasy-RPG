#include "DataAcess.h"
#include <fstream>

bool isPrintable(char c){
	return ( c == '\t' or
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

Domain::Localization DataAcess::getLocalization(int id){
	Domain::Localization res;
	res.connections = db->getLocationConnections(id);
	auto a = db->getLocationNameDescription(id);
	res.description = readWholeFile(a.secend);
	res.name = a.first;	
	return res;
}

