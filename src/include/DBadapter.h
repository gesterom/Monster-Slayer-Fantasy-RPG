#include "Domain.h"

class DBadapter
{
	public:
	virtual Domain::location getLocationById(int id) = 0;
	virtual ~DBadapter(){}
};

