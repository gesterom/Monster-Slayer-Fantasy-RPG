#pragma once

struct Config
{
	struct{
		std::string url;
		int port;
		std::string usr;
		std::string password;
		std::string databaseName;
	} database;
	struct{
		int port;
	} server;
};

Config getConfig()
{
	Config config =
	{
		{
			"localhost",
			3306,
			"gameServer",
			""//password,
			"game"//databaseName
		},
		{8085}
	};
	return config;
}
