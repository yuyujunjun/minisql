#include "Catalog.h"



Catalog::Catalog()
{
}


Catalog::~Catalog()
{
}

int Catalog::GetAttributeLength(int type , int typelength)
{
	if (type = INT)
	{
		return 10;
	}
	else if (type = FLOAT)
	{
		return 11;
	}
	else
	{
		return typelength;
	}
}

int Catalog::GetRecordLength(string tablename)
{
	return 0;
}
