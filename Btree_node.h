#pragma once

#include"all.h"
//extern BufferManager BM;

using namespace std;
const int N = 500;
template<class T>class Btree_node
{
public:
	Btree_node(string indexname);//�����������������������Եĳ��ȣ������Ե�����
								 //Btree_node(Block* block,int type,int typelength,string indexname);//���ļ���ʱ���Խ����õ������Ŀ����ɽ��
	int keynum;//��ֵ�Ķ���,���ʱ����degree
			   //����ؽṹ
	Btree_node<T> *parent;
	Btree_node<T> *child[N];
	Btree_node<T> *lastsilbling;
	bool isleaf;
	bool isroot;
	//��Ϣ�ṹ
	int blocknum[N];//���ļ��ĵڼ�����
	T min;
	//	float float_min;
	//	string string_min;
	T attr[N];//���͵�����
			  //	float attr_float[N];
			  //	string attr_char[N];
			  //�洢�Ľṹ
			  //Block* block;//�ÿ����ݴ洢�ĵط�

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
Btree_node::Btree_node(Block* block, int type, int typelength, string filename) {//�Ѿ��п��ˣ��ӻ����аѿ����ɽ�㣬������b+��
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