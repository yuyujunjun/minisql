#pragma once
class Btree_node
{
public:
	Btree_node();
	int keynum;//��ֵ�Ķ���
	Btree_node *parent;
	Btree_node *child;
	
	~Btree_node();
};

