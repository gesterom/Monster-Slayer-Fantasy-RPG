#include <iostream>

#include <mysql++/mysql++.h>
#include <zmq.hpp>

#include "Config.h"
#include "ProductionDBadapter.h"

Config getConfig()
{
	#include "../../assets/config"
	return config;
}
int main(int argc, char** args)
try
{
	if(argc<2){
		std::cout<<"Pass password as secend argument\n";
		return -1;
	}
	
	zmq::context_t ctx{500};

	Config config = getConfig();
	config.database.password = args[1];
	DBadapter* dba = new ProductionDBadapter(config);
	
	delete dba;
}
catch(std::exception& e)
{
	std::cerr<<e.what()<<std::endl;
}
