#pragma once

#include "all.h"

using namespace std;

class Catalog
{
public:
	Catalog();
	~Catalog();
	
	
};
int GetRecordLength(string tablename); //�õ�����һ����¼�ĳ���
int GetAttributeLength(int type, int typelength = 0); //�õ�һ�����Եĳ���