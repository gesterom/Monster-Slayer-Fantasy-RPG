#pragma once
#include "Tokens.h"
#include "GameState.h"

class Server
{
	private:
	Tokens& tokens;
	GameState curent;
	GameState backBuffer;
	public:
	void run();
}
