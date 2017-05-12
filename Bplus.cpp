#include "stdafx.h"
#include "Bplus.h"
void Bplus::DEBUG() {
	Btree_node* a= root;
	
}

Bplus::Bplus(string indexname,int type,int typelength)
{
	root = new Btree_node(indexname);
	root->isleaf = true;
	root->isroot = true;
	int length = GetAttributeLength(INT) + GetAttributeLength(type, typelength);
	//degree = (BlockSize - BlockHeadSize) / length;
	degree = 3;
	this->indexname = indexname;
	this->degree = degree;
	this->typelength = typelength;
	this->type = type;

}
Btree_node* Bplus:: find_leaf(int key) {
	Btree_node* now = root;
	while (!now->isleaf) {
		for (int i = 0; i <= now->keynum; i++) {
			if (i == now->keynum || key < now->attr_int[i]) {
				now = now->child[i];
				//cout << "find leaf: " << i << endl;
				break;
			}
		}
	}
	return now;
}
bool Bplus::insert_into_btree(int key,int offset) {
	Btree_node* leaf = find_leaf(key);
	for (int i = 0; i < leaf->keynum; i++) {
		if (key == leaf->attr_int[i]) {//如果原来的那个块就有相同的键值
			return false;
		}
	}
	insert_into_node(leaf, key, offset,NULL);
	return true;
}
void Bplus::insert_into_node(Btree_node * node, int key, int offset,Btree_node* child) {
	int x = 0;
	while (x < node->keynum&&node->attr_int[x] < key)x++;
	for (int i = node->keynum; i > x; i--) {
		node->attr_int[i] = node->attr_int[i - 1];
		node->blocknum[i] = node->blocknum[i - 1];
	}
	for (int i = node->keynum+1 ; i > x +1; i--) {
		node->child[i] = node->child[i - 1];
	}
	node->attr_int[x] = key;
	node->blocknum[x ] = offset;
	node->child[x + 1] = child;
	node->keynum++;
	if (node->keynum == degree) {
		split(node);
	}
	node->int_min = node->attr_int[0];
	//node->parent = find_parent(node, root);
}
Bplus::~Bplus()
{
}
void Bplus::split(Btree_node *node) {
	Btree_node * newnode = new Btree_node(indexname);
	int mid_key = node->attr_int[degree / 2];
	newnode->keynum = degree - degree / 2 - 1;
	for (int i = 0; i < newnode->keynum; i++) {
		newnode->attr_int[i] = node->attr_int[i + (degree / 2 + 1)];
		newnode->blocknum[i] = node->blocknum[i + (degree / 2 + 1)];
		newnode->child[i] = node->child[i + (degree / 2 + 1)];
		//if (node->isroot)newnode->child[i]->parent = newnode;
	}
	newnode->child[newnode->keynum] = node->child[degree];
	node->keynum = degree / 2;
	if (node->isleaf) {
		node->keynum++;
		newnode->child[0] = node->child[0];
		node->child[0] = newnode;
		newnode->isleaf = true;
		mid_key = node->attr_int[degree / 2 + 1];
		newnode->int_min = newnode->attr_int[0];
	}
	if (node->isroot) {
		node->isroot = false;
		root = new Btree_node(indexname);
		root->isroot = true;
		root->attr_int[0] = mid_key;
		root->child[0] = node;
		root->child[1] = newnode;
		//node->parent = root;
		root->keynum = 1;
		root->int_min = root->attr_int[0];
		node->parent = newnode->parent = root;
		newnode->int_min = newnode->attr_int[0];
		//newnode->int_min = newnode->attr_int[0];
	//	newnode->parent = node->parent = find_parent(newnode, root);
		
	}
	else {
		newnode->parent = node->parent;
		Btree_node * par = find_parent(node, root);
		//node->parent->child[node->parent->keynum+1]=newnode;
		insert_into_node(par, mid_key, 0,newnode);
		//newnode->parent = node->parent = find_parent(newnode,root);
	}
	/*cout << "midnum: " << mid_key << endl;
	//cout << "parent: " << node->parent << endl;
	cout << "newnode: " << newnode->keynum << endl;
	cout<<"node:"<<node->keynum<<endl;*/
}
Btree_node* Bplus::find_parent(Btree_node * now,Btree_node* root) {
	int key = now->int_min;
	for (int i = 0; i <= root->keynum; i++) {
		if (root->child[i] == now)return root;
		if (i == root->keynum || key < root->attr_int[i]) {
			root = find_parent(now, root->child[i]);
			break;
		}
	}
	return root;
}
