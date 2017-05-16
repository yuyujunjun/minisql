#pragma once

#include"all.h"
#include<string>

using namespace std;


//�������ͺ�Լ��
const enum type{CHAR, INT, FLOAT};
const enum operato{MORE_EQUAL, LESS_EQUAL, LESS, MORE, NOT_EQUAL, EQUAL};
//enum constrain{PRIMARY};
const int quit = 999;
//�������Խṹ
class Attribute {
public:
	string attr_name;
	int attr_type;

	int attr_len;
	bool NOTNULL;
	bool UNIQUE;
	Attribute(string name, int type, bool notnull,bool unique,int len)  {
		attr_name = name;
		attr_type = type;
		attr_len = len;
		NOTNULL = notnull;
		UNIQUE = unique;
	}
	Attribute() {
	}
};
//������Ľṹ
class Table {
public:
	
	Attribute attribute[32];
	string table_name;
	int num_of_attribute;
	int primary_position;
	Table(string table_name, int num_of_attribute, int primary_position, Attribute tmp[]) {
		this->table_name = table_name;
		this->num_of_attribute = num_of_attribute;
		this->primary_position = primary_position;
		for (int i = 0; i < num_of_attribute; i++) {
			attribute[i] = tmp[i];
		}
		
	}
};

class Condition {
public:
	string Left;
	string Right;
	int op;
	Condition(string left, string right, int op) :Left(left), Right(right), op(op) {}
};
//������Ľṹ
struct Block
{
	string Filename; //�ÿ������ļ�
	bool IsLeaf; //�Ƿ���Ҷ�ڵ㣬��������������
	int BlockNum;  //���ļ��е�i����
	int Size; //���С=���ݵ�ƫ����
	int RecordLength;  //һ����¼����
	int FirstDelete;  // ���е�һ����ɾ�ļ�¼�ڿ��е�λ��
	bool pin;  //�Ƿ�����
	bool IsWritten;  //�Ƿ��޸Ĺ�
	bool last; //�Ƿ������һ����
	char * memory;  //ָ�򴢴�ռ�
};

struct LRUNode
{
	Block* BlockNode;
	LRUNode* pre;
	LRUNode* aft;
};