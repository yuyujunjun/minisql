#include"stdafx.h"
#include "Catalog.h"

int GetAttributeLength(int type , int typelength)
{
	if (type == INT)
	{
		return 10;
	}
	else if (type == FLOAT)
	{
		return 11;
	}
	else
	{
		return typelength;
	}
}

int GetRecordLength(string tablename)
{
	return 0;
}