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
	bool loginPlayer(int player_id);
  void execCommand(Command& c);
	public:
	Server( CommandQueue& cQ, DBadapter* dba ) : commandQ( cQ ), db( dba ) {}
	int whereIsPlayer(int Player_id);
	void run();
};
