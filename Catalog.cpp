#include"stdafx.h"
#include "Catalog.h"



Catalog::Catalog()
{
}


Catalog::~Catalog()
{
}


int GetAttributeLength(int type , int typelength)
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
	return 0;

}

int GetRecordLength(string tablename)
{
	return 0;
}