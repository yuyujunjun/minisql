#pragma once

#include"all.h"
//extern BufferManager BM;

using namespace std;
const int N = 500;
template<class T>class Btree_node
{
public:
	Btree_node(string indexname);//建立索引的属性名，该属性的长度，该属性的名字
								 //Btree_node(Block* block,int type,int typelength,string indexname);//从文件打开时，对建立好的索引的块生成结点
	int keynum;//键值的多少,最大时等于degree
			   //树相关结构
	Btree_node<T> *parent;
	Btree_node<T> *child[N];
	Btree_node<T> *lastsilbling;
	bool isleaf;
	bool isroot;
	//信息结构
	int blocknum[N];//在文件的第几个块
	T min;
	//	float float_min;
	//	string string_min;
	T attr[N];//整型的属性
			  //	float attr_float[N];
			  //	string attr_char[N];
			  //存储的结构
			  //Block* block;//该块数据存储的地方

	~Btree_node();
};

template<class T> Btree_node<T>::Btree_node(string filename)
{
	keynum = 0;
	//this->block = BM.GetBlock(filename);
	parent = NULL;
	isleaf = 0;
	isroot = 0;
	//min = 0;
	child[0] = NULL;
	lastsilbling = NULL;
	//	float_min = 0;
	//	string_min = '\0';
}
/**
Btree_node::Btree_node(Block* block, int type, int typelength, string filename) {//已经有块了，从缓存中把块生成结点，再生成b+树
int attri_length = GetAttributeLength(type, typelength);
int offset_length = GetAttributeLength(INT);
keynum = (BlockSize - BlockHeadSize) / (attri_length + offset_length);

this->block = block;
parent =  NULL;
isleaf = 0;
min = 0;
float_min = 0;
string_min = '\0';
}
*/
template<class T> Btree_node<T>::~Btree_node()
{
	//BM.WriteToDisk(filename,this->block);
}