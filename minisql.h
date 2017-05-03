#pragma once
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
};
//声明表的结构
class Table {
public:
	Attribute attribute[32];
	string table_name;
	int num_of_attribute;
	int primary_position;
	int get_attri_id(string attri_name);
	int get_table_length();
};
class Condition {
public:
	string Left;
	string Right;
	int op;
	Condition(string left, string right, int op) :Left(left), Right(right), op(op) {}
};