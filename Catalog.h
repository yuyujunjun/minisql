#pragma once



#include <string>
#include "BufferManager.h"
#include "minisql.h"
using namespace std;

class Catalog
{
public:
	Catalog();
	~Catalog();
	int GetAttributeLength(int type,int typelength = 0); //�õ�һ�����Եĳ���
	int GetRecordLength(string tablename); //�õ�����һ����¼�ĳ���
};

