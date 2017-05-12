#pragma once

#include"all.h"


using namespace std;
const int N = 500;
class Btree_node
{
public:
	Btree_node(string indexname);//建立索引的属性名，该属性的长度，该属性的名字
	//Btree_node(Block* block,int type,int typelength,string indexname);//从文件打开时，对建立好的索引的块生成结点
	int keynum;//键值的多少,最大时等于degree
	//树相关结构
	Btree_node *parent;
	Btree_node *child[N];
//	Btree_node *nextsilbling;
	bool isleaf;
	bool isroot;
	//信息结构
	int blocknum[N];//在文件的第几个块
	int int_min;
//	float float_min;
//	string string_min;
	int attr_int[N];//整型的属性
//	float attr_float[N];
//	string attr_char[N];
	//存储的结构
	//Block* block;//该块数据存储的地方
	
	~Btree_node();
};

