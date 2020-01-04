#pragma once
#include "Tokens.h"
#include "GameState.h"
#include "CommandQueue.h"
#include "DBadapter.h"
class Server {
  private:
	GameState current;
	GameState backBuffer;
	CommandQueue& commandQ;
	DBadapter* db;
  public:
	Server( CommandQueue& cQ, DBadapter* dba ) : commandQ( cQ ), db( dba ) {}
	void run();
};
