#pragma once
#include <vector>
#include <string>
#include <Poco/Net/StreamSocket.h>

using Socket_t = Poco::Net::StreamSocket;

std::vector<std::string> sub(std::string data);
uint32_t getIntFromSocket( Poco::Net::StreamSocket& socket ) ;
