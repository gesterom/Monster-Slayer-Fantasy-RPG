#pragma once

#include "Command.h"
#include "Authorization.h"
#include "CommandQueue.h"
#include "DBadapter.h"
#include "DataAcess.h"

#include <thread>

#include <Poco/Net/TCPServer.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/NetException.h>

class IOHandler : public Poco::Net::TCPServerConnection {
  private:
	
	
	uint8_t header[8] = {}; //"AAAA C "
	uint8_t buf[1024] = {};
	Command reciveCommand();
	
	CommandQueue& q;
	void send( std::string str ) ;
	void shutdownSocket( std::string msg ) ;
	//handlers
	bool handleLogin	( Command& com ) ;
	bool handleGet		( Command& com ) ;
	Authorization& auth;
	DataAcess& dao;
  public:
	IOHandler( const Poco::Net::StreamSocket& socket, CommandQueue& commandQ, Authorization& a, DataAcess da ) :
		Poco::Net::TCPServerConnection( socket ),
		q( commandQ ),
		auth( a ),
		dao(da)
		{}
	void run() override;
};

