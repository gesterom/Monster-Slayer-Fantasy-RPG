#include <iostream>
// #include <mysql++/mysql++.h>

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/NetException.h>

#include "ProductionDBadapter.h"
#include "CommandQueue.h"
#include "Server.h"
#include "Config.h"
#include "Authorization.h"

#include "IOHandler.h"

Config getConfig() {
	Config config = {
		{
			"localhost",//database url
			3306,//database port
			"gameServer",//database user
			"",//password,
			"game"//databaseName
		},
		{8085}
	};
	return config;
}

class IOHandlerFactory : public Poco::Net::TCPServerConnectionFactory {
	CommandQueue& q;
	Authorization& auth;
	DataAcess& dao;
  public:
	virtual Poco::Net::TCPServerConnection* createConnection( const Poco::Net::StreamSocket& socket ) override {
		return new IOHandler( socket, q, auth, dao );
	}
	IOHandlerFactory( CommandQueue& commandQ, Authorization& a , DataAcess& d ) 
			: q( commandQ ), auth( a ),dao(d) {}
	virtual ~IOHandlerFactory() {}
};

bool testDatabaseAdapter(DBadapter* db);
bool testDAO(DataAcess& dao);

int main( int argc, char** args )
try {
	if( argc < 2 ) {
		std::cout << "Pass password as secend argument\n";
		return -1;
	}

	Config config = getConfig();
	config.database.password = args[1];

	std::cout << "Database : ";
	DBadapter* dba = new ProductionDBadapter( config );
	std::cout << "[DONE]\n";

	if(testDatabaseAdapter(dba)){
		return 0;
	}

	std::cout << "CommandQ ";
	CommandQueue commandQ;
	std::cout << "[DONE]\n";

	std::cout << "Tokens ";
	Tokens tokens( 60 );
	std::cout << "[DONE]\n";

	std::cout << "Authorization ";
	Authorization auth( dba, tokens );
	std::cout << "[DONE]\n";

	std::cout << "Server ";
	Server server( commandQ, dba );
	std::cout << "[DONE]\n";

	std::cout<<"DataAcess ";
	DataAcess dao(dba,server);
	std::cout << "[DONE]\n";
	if(testDAO(dao)){
		return 0;
	}	
	
	std::cout << "TCPServer ";
	Poco::Net::TCPServer tcpserver( new IOHandlerFactory( commandQ, auth , dao ), config.server.port );
	std::cout << "[DONE]\n";
	
	std::cout << "TCPServer Start ";
	tcpserver.start();
	std::cout << "[DONE]\n";

	std::cout << "Server Start \n\n==============================\n\n";
	server.run();

	delete dba;
}
catch( std::exception& e ) {
	std::cerr << e.what() << std::endl;
}



bool testDAO(DataAcess& dao){
	//return false;
	std::cout<<"DAO : ["<<dao.getLocalization(1).serialize()<<"]\n";
	return true;	
}


bool testDatabaseAdapter(DBadapter* db){
	return false;
	auto t = db->getLocationConnections(1);
	for(auto i : t){
		std::cout<<"description : "<<i.description<<" destination : "<<i.destination<<"\n";
	}
	return true;
}

