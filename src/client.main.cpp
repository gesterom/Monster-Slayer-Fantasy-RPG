#include <iostream>
#include <unistd.h>
#include <string>

int main(int argc, char** args)
try
{
	if(argc<2) return -1;
}
catch( std::exception& e)
{
	std::cout<<e.what()<<std::endl;
}
