#pragma once

#include "DBadapter.h"
#include "Server.h"
#include "Domain/Localization.h"

class DataAcess{
	private:
		DBadapter* db;
		Server& server;
	public:
		DataAcess(DBadapter* dba,Server& serv) : db(dba), server(serv) {}
		Domain::Localization getLocalizationOfPlayer(int player_id);	
};
