#pragma once
#include"all.h"
//#include"Btree_node.h"
class Bplus
{
public:
	int degree;
	int type;
	int typelength;
	string indexname;//建立的索引的名字
	Btree_node* root;
	bool insert_into_btree(int key,int offset);
	void insert_into_node(Btree_node * node, int key, int offset, Btree_node* child);
	void split(Btree_node *node);
	Btree_node * find_parent(Btree_node *node,Btree_node * root);
	//bool delete_from_btree();
	//int query_on_btree();
	Btree_node* find_leaf(int key);
	Bplus(string indexname,int type,int typelength);
	void DEBUG();
	~Bplus();
};

