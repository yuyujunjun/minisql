#pragma once

#include"all.h"


using namespace std;
class Btree_node
{
public:
	Btree_node(int type,int typelength,string indexname);//�����������������������Եĳ��ȣ������Ե�����
	Btree_node(Block* block,int type,int typelength,string indexname);//���ļ���ʱ���Խ����õ������Ŀ����ɽ��
	int keynum;//��ֵ�Ķ���,Ҳ�����degree
	//����ؽṹ
	Btree_node *parent;
	vector<Btree_node *>child;
	Btree_node *nextsilbling;
	//��Ϣ�ṹ
	vector<int> blocknum;//���ļ��ĵڼ�����
	vector<int> attr_int;//���͵�����
	vector<float> attr_float;
	vector<string> attr_char;
	//�洢�Ľṹ
	Block* block;//�ÿ����ݴ洢�ĵط�
	string filename;//�ÿ����ݴ���ط�������
	~Btree_node();
};

class Bptree {
	Btree_node* node;

};