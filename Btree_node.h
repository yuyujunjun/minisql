#pragma once
class Btree_node
{
public:
	Btree_node();
	int keynum;//键值的多少
	Btree_node *parent;
	Btree_node *child;
	
	~Btree_node();
};

