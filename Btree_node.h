#pragma once

#include"all.h"


using namespace std;
class Btree_node
{
public:
	Btree_node(int type,int typelength,string indexname);//建立索引的属性名，该属性的长度，该属性的名字
	Btree_node(Block* block,int type,int typelength,string indexname);//从文件打开时，对建立好的索引的块生成结点
	int keynum;//键值的多少,也是最大degree
	//树相关结构
	Btree_node *parent;
	vector<Btree_node *>child;
	Btree_node *nextsilbling;
	//信息结构
	vector<int> blocknum;//在文件的第几个块
	vector<int> attr_int;//整型的属性
	vector<float> attr_float;
	vector<string> attr_char;
	//存储的结构
	Block* block;//该块数据存储的地方
	string filename;//该块数据储存地方的名字
	~Btree_node();
};

class Bptree {
	Btree_node* node;

};