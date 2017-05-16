#pragma once

#include"all.h"
#include<string>

using namespace std;


//声明类型和约束
const enum type{CHAR, INT, FLOAT};
const enum operato{MORE_EQUAL, LESS_EQUAL, LESS, MORE, NOT_EQUAL, EQUAL};
//enum constrain{PRIMARY};
const int quit = 999;
//声明属性结构
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
//声明表的结构
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
//声明块的结构
struct Block
{
	string Filename; //该块所属文件
	bool IsLeaf; //是否是叶节点，仅在索引里有用
	int BlockNum;  //该文件中第i个块
	int Size; //块大小=内容的偏移量
	int RecordLength;  //一条记录长度
	int FirstDelete;  // 块中第一条被删的记录在块中的位置
	bool pin;  //是否锁定
	bool IsWritten;  //是否被修改过
	bool last; //是否是最后一个块
	char * memory;  //指向储存空间
};

struct LRUNode
{
	Block* BlockNode;
	LRUNode* pre;
	LRUNode* aft;
};