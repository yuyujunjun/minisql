#pragma once
#include <string>
#include "minisql.h"
#include "BufferManager.h"
using namespace std;

class Catalog
{
public:
	Catalog();
	~Catalog();
	int GetAttributeLength(int type); //得到一种属性的长度
	int GetRecordLength(string tablename); //得到表中一条记录的长度
};

