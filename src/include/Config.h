#pragma once

struct Config {
	struct {
		std::string url;
		int port;
		std::string usr;
		std::string password;
		std::string databaseName;
	} database;
	struct {
		int port;
	} server;
};


