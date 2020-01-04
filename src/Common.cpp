#include "Common.h"


std::vector<std::string> sub( std::string data ) {
	std::vector<std::string> res;
	std::string word;

	for( size_t i = 0 ; i < data.size(); i++ ) {
		if( data[i] == ' ' ) {
			res.push_back( word );
			word = "";
		}
		else {
			word += data[i];
		}
	}

	if( word != "" ) {
		res.push_back( word );
	}

	return res;
}

uint32_t getIntFromSocket( Poco::Net::StreamSocket& socket ) {
	uint32_t res = 0;
	uint8_t buf;

	while ( true ) {
		socket.receiveBytes( &buf, sizeof( buf ) );

		if( buf >= '0' and buf <= '9' ) {
			res = res * 10;
			res = res + buf - '0';
		}
		else {
			break;
		}
	}

	return res;
}
