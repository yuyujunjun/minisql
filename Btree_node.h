#pragma once

#include"all.h"


using namespace std;
const int N = 500;
class Btree_node
{
public:
	Btree_node(string indexname);//�����������������������Եĳ��ȣ������Ե�����
	//Btree_node(Block* block,int type,int typelength,string indexname);//���ļ���ʱ���Խ����õ������Ŀ����ɽ��
	int keynum;//��ֵ�Ķ���,���ʱ����degree
	//����ؽṹ
	Btree_node *parent;
	Btree_node *child[N];
//	Btree_node *nextsilbling;
	bool isleaf;
	bool isroot;
	//��Ϣ�ṹ
	int blocknum[N];//���ļ��ĵڼ�����
	int int_min;
//	float float_min;
//	string string_min;
	int attr_int[N];//���͵�����
//	float attr_float[N];
//	string attr_char[N];
	//�洢�Ľṹ
	//Block* block;//�ÿ����ݴ洢�ĵط�
	
	~Btree_node();
};

