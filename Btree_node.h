#pragma once

#include"all.h"


using namespace std;
class Btree_node
{
public:
	Btree_node(int type,int typelength,string indexname);//�����������������������Եĳ��ȣ������Ե�����
	int keynum;//��ֵ�Ķ���,Ҳ�����degree
	Btree_node *parent;
	Btree_node *child;
	vector<int> blocknum;//���ļ��ĵڼ�����
	vector<int> attr_int;//���͵�����
	vector<float> attr_float;
	vector<string> attr_char;
	Block* block;//�ÿ����ݴ洢�ĵط�
	string filename;//�ÿ����ݴ���ط�������
	~Btree_node();
};

