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
	int GetAttributeLength(int type,int typelength = 0); //�õ�һ�����Եĳ���
	int GetRecordLength(string tablename); //�õ�����һ����¼�ĳ���
};

