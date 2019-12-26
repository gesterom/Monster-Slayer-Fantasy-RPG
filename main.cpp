#include <mysql++/mysql++.h>
#include <iostream>

int main()try
{
	mysqlpp::Connection conn("game","localhost","gameServer","1234" /*FIXME*/,3306);
	mysqlpp::Query q = conn.query("Select 'name'");
	if(auto res = q.store()){
		std::cout<<"We have"<<std::endl;
		for(auto i : res){
			std::cout<<i[0]<<std::endl;
		}
	}else{
		std::cout<<"fuck\n";
	}
}
catch(std::exception& e)
{
	std::cout<<e.what()<<std::endl;
}
