#pragma once

#include"all.h"


using namespace std;
class Btree_node
{
public:
	Btree_node(int type,int typelength,string indexname);//建立索引的属性名，该属性的长度，该属性的名字
	int keynum;//键值的多少,也是最大degree
	Btree_node *parent;
	Btree_node *child;
	vector<int> blocknum;//在文件的第几个块
	vector<int> attr_int;//整型的属性
	vector<float> attr_float;
	vector<string> attr_char;
	Block* block;//该块数据存储的地方
	string filename;//该块数据储存地方的名字
	~Btree_node();
};

