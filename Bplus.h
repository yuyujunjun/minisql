
#pragma once
#include"all.h"
//#include"Btree_node.h"
template<class T>class Bplus
{
public:
	int degree;
	int type;
	int typelength;
	string indexname;//����������������
	Btree_node<T>* root;
	bool insert_into_btree(T key, int type, int offset);
	void insert_into_node(Btree_node<T> * node, T key, int offset, Btree_node<T>* child);
	void split(Btree_node<T> *node);
	bool delete_from_btree(T key);
	void delete_from_node(Btree_node<T>* node, T key);
	Btree_node<T> * find_parent(Btree_node<T> *node, Btree_node<T> * root);
	//bool delete_from_btree();
	vector<int> query_on_btree(T key,T QWQ,bool min=true,bool max=true);
	Btree_node<T>* find_leaf(T key);
	void combine(Btree_node<T>* node, T key);
	Bplus(string indexname, int type, int typelength);
	void DEBUG();
	void Print_leaf();//using just for test
	~Bplus();
};

template <class T> void Bplus<T>::DEBUG() {
	Btree_node<T>* a = root;

}

template <class T> Bplus<T>::Bplus(string indexname, int type, int typelength)
{
	root = new Btree_node<T>(indexname);
	root->isleaf = true;
	root->isroot = true;
	int length = GetAttributeLength(INT) + GetAttributeLength(type, typelength);
	degree = (BlockSize - BlockHeadSize) / length;
	//degree = 4;
	this->indexname = indexname;
	this->degree = degree;
	this->typelength = typelength;
	this->type = type;

}
template <class T> Btree_node<T>* Bplus<T>::find_leaf(T key) {
	Btree_node<T>* now = root;
	while (!now->isleaf) {
		for (int i = 0; i <= now->keynum; i++) {
			if (i == now->keynum || key < now->attr[i]) {
				now = now->child[i];
				//cout << "find leaf: " << i << endl;
				break;
			}
		}
	}
	return now;
}
template <class T> bool Bplus<T>::insert_into_btree(T key,int type, int offset) {
	Btree_node<T>* leaf;
	leaf = find_leaf(key);
	for (int i = 0; i < leaf->keynum; i++) {
		if (key == leaf->attr[i]) {//���ԭ�����Ǹ��������ͬ�ļ�ֵ
			return false;
		}
	}
	insert_into_node(leaf, key, offset, NULL);
	return true;
}
template <class T> void Bplus<T>::insert_into_node(Btree_node<T> * node, T key, int offset, Btree_node<T>* child) {
	int x = 0;
	while (x < node->keynum&&node->attr[x] < key)x++;
	for (int i = node->keynum; i > x; i--) {
		node->attr[i] = node->attr[i - 1];
		node->blocknum[i] = node->blocknum[i - 1];
	}
	for (int i = node->keynum + 1; i > x + 1; i--) {
		node->child[i] = node->child[i - 1];
	}
	node->attr[x] = key;
	node->blocknum[x] = offset;
	node->child[x + 1] = child;
	node->keynum++;
	if (node->keynum == degree) {
		split(node);
	}
	node->min = node->attr[0];
	//node->parent = find_parent(node, root);
}
template <class T> Bplus<T>::~Bplus()
{
}
template <class T> void Bplus<T>::split(Btree_node<T> *node) {
	Btree_node<T> * newnode = new Btree_node<T>(indexname);
	T mid_key = node->attr[degree / 2];
	newnode->keynum = degree - degree / 2 - 1;
	for (int i = 0; i < newnode->keynum; i++) {
		newnode->attr[i] = node->attr[i + (degree / 2 + 1)];
		newnode->blocknum[i] = node->blocknum[i + (degree / 2 + 1)];
		newnode->child[i] = node->child[i + (degree / 2 + 1)];
	//	if (newnode->child[i])
		//	newnode->child[i]->parent = newnode;
		//if (node->isroot)newnode->child[i]->parent = newnode;
	}
	newnode->child[newnode->keynum] = node->child[degree];
	//if (newnode->child[newnode->keynum])newnode->child[newnode->keynum]->parent = newnode;
	node->keynum = degree / 2;
	//newnode->parent = node->parent;
	if (node->isleaf) {
		node->keynum++;
		if (node->child[0])node->child[0]->lastsilbling = newnode;
		newnode->child[0] = node->child[0];
		node->child[0] = newnode;
		newnode->lastsilbling = node;
		newnode->isleaf = true;
		mid_key = node->attr[degree / 2 + 1];
		newnode->min = newnode->attr[0];
		//newnode->parent = node->parent;
	}
	if (node->isroot) {
		node->isroot = false;
		root = new Btree_node<T>(indexname);
		root->isroot = true;
		root->attr[0] = mid_key;
		root->child[0] = node;
		root->child[1] = newnode;
		//node->parent = root;
		root->keynum = 1;
		root->min = root->attr[0];
		//node->parent = newnode->parent = root;
		newnode->min = newnode->attr[0];

		//newnode->min = newnode->attr[0];
		//	newnode->parent = node->parent = find_parent(newnode, root);

	}
	else {
		//newnode->parent = node->parent;
		Btree_node<T> * par = find_parent(node, root);
		//node->parent->child[node->parent->keynum+1]=newnode;
		insert_into_node(par, mid_key, 0, newnode);
		//newnode->parent = node->parent = find_parent(node, root);
	}
	/*cout << "midnum: " << mid_key << endl;
	//cout << "parent: " << node->parent << endl;
	cout << "newnode: " << newnode->keynum << endl;
	cout<<"node:"<<node->keynum<<endl;*/
}
template <class T> Btree_node<T>* Bplus<T>::find_parent(Btree_node<T> * now, Btree_node<T>* root) {
	T key = now->min;
	for (int i = 0; i <= root->keynum; i++) {
		if (root->child[i] == now)return root;
		if (i == root->keynum || key < root->attr[i]) {
			root = find_parent(now, root->child[i]);
			break;
		}
	}
	return root;
}
template <class T> bool Bplus<T>::delete_from_btree(T key) {
	Btree_node<T>* leaf = find_leaf(key);
	for (int i = 0; i < leaf->keynum; i++) {
		if (key == leaf->attr[i]) {
			delete_from_node(leaf, key);
			return true;
		}
	}
	return false;
}
template <class T> void Bplus<T>::delete_from_node(Btree_node<T>* node, T key) {
	int x = 0;
	while (key != node->attr[x])x++;
	for (int i = x; i < node->keynum - 1; i++) {
		node->attr[i] = node->attr[i + 1];
		node->blocknum[i] = node->blocknum[i + 1];
	}
	for (int i = x + 1; i < node->keynum; i++) {
		node->child[i] = node->child[i + 1];
	}
	node->keynum--;
	node->min = node->attr[0];
	if (node->keynum < degree / 2) {
		//combine(node, key);
	}
}


template <class T> vector<int> Bplus<T>::query_on_btree(T key,T QWQ,bool min,bool max) {
	vector<int> results;
	Btree_node<T>* leaf1 = find_leaf(key);
	Btree_node<T>* leaf2 = find_leaf(QWQ);
	bool isfindfirst = false;
	bool islast = false;
	if (leaf1 == NULL) {
		cout << "�һ���˵ɶ�أ���ð���Ŷ��������query on btree�����ص��ǿս�㣬���Ը���û��������bplus tree �ɣ�����������ǲ��ᷢ���ģ��Ҿ�д�����" << endl;
		vector<int> temp;
		return temp;
	}
	if (min)isfindfirst = true;
	if (max)islast = true;
	int i = 0;
	while (leaf1 != leaf2) {
		for (i = 0; i < leaf1->keynum; i++) {
			if (key >= leaf1->attr[i]||isfindfirst==true) {
				isfindfirst = true;
				results.push_back(leaf1->blocknum[i]);
			}
		}
		leaf1 = leaf1->child[0];
	}
	if (leaf1 == leaf2) {
		for (i = 0; i < leaf1->keynum; i++) {
			if ((key <= leaf1->attr[i]||min )&& (QWQ >= leaf1->attr[i]||max)) {
				isfindfirst = true;
				results.push_back(leaf1->blocknum[i]);
			}
		}
	}
	return results;
}
template <class T> void Bplus<T>::combine(Btree_node<T>* node, T key) {
	if (node->isroot) {
		if (root->keynum == 0) {
			if (root->child[0]) {
				root->child[0]->isroot = true;
				//root->child[0]->isroot = true;
				root = root->child[0];
				if (root == NULL)root->isleaf = true;
			}
			else { root->isleaf = true; }
		}
	}
	else if (node->isleaf) {
		if (node->keynum < degree / 2) {
			if (node->lastsilbling&&node->lastsilbling->parent == node->parent&&node->lastsilbling->keynum > degree / 2) {
				Btree_node<T>* par = find_parent(node, root);//fujiedian
				Btree_node<T> *last = node->lastsilbling;
				//delete_from_node(last, last->attr[last->keynum-1]);��������䲻��ͬʱʹ��
				last->keynum--;
				insert_into_node(node, last->attr[last->keynum], last->blocknum[last->keynum], NULL);//�˴���node��keynum���м�
				for (int i = 0; i < par->keynum; i++) {
					if (last->attr[last->keynum] < par->attr[i]) {
						par->attr[i] = last->attr[last->keynum];
						break;
					}
				}
				par->min = par->attr[0];//����min
			}
			else if (node->child[0] && node->child[0]->parent == node->parent&&node->child[0]->keynum > degree / 2) {
				Btree_node<T>* par = find_parent(node, root);;
				Btree_node<T>* next = node->child[0];
				delete_from_node(next, next->attr[0]);

				insert_into_node(node, next->attr[0], next->attr[0], NULL);
				for (int i = 0; i < par->keynum; i++) {
					if (next->attr[0] < par->attr[i]) {
						par->attr[i] = next->attr[0];
						break;
					}
				}
				par->min = par->attr[0];
			}
			else {
				if (node->child[0] && node->child[0]->parent == node->parent) {
					Btree_node<T>* next = node->child[0];
					node->child[0] = next->child[0];
					if (node->child[0])node->child[0]->lastsilbling = node;//����ָ��

					for (int i = 0; i < next->keynum; i++) {
						insert_into_node(node, next->attr[i], next->blocknum[i], NULL);
					}
					delete_from_node(node->parent, next->attr[0]);
				}
				else if (node->lastsilbling&&node->lastsilbling->parent == node->parent) {
					Btree_node<T>* last = node->lastsilbling;
					if (last->lastsilbling)last->lastsilbling->child[0] = node;
					node->lastsilbling = last->lastsilbling;
					for (int i = 0; i < last->keynum; i++) {
						insert_into_node(node, last->attr[i], last->blocknum[i], NULL);
					}
					delete_from_node(node->parent, last->attr[0]);
				}
				else {
					delete_from_node(node->parent, key);//�ø��ڵ�û�������ӽڵ�
				}
			}
		}
	}
	else {//��Ҫ���º����ǵĸ��׽ڵ���Ϣ���������׽ڵ�ϲ���ʱ��
		T midkey = node->attr[0];
		int x = 0;
		for (x = 0; x < node->parent->keynum; x++) {
			if (midkey < node->parent->attr[x])
			{
				break;
			}
		}
		Btree_node<T>* last = NULL;
		Btree_node<T>* next = NULL;
		if (x == 0 && x != node->parent->keynum) {//ֻ���ұ߽��
			last = NULL;
			next = node->parent->child[x + 1];
		}
		else if (x != 0 && x != node->parent->keynum) {//���߽�㶼��
			last = node->parent->child[x - 1];
			next = node->parent->child[x + 1];
		}
		else if (x == node->parent->keynum&&x != 0) {//����߽�㵫û���ұ�
			last = node->parent->child[x - 1];
			next = NULL;
		}
		else if (x == 0 && x == node->parent->keynum) {//���ڵ�û�н�㣿woc����ʲô��
			last = NULL;
			next = NULL;
		}
		if (last&&last->keynum > degree / 2) {
			last->keynum--;
			insert_into_node(node, last->attr[last->keynum], 0, last->child[last->keynum + 1]);
			Btree_node<T>* par = node->parent;
			int i = 0;
			for (i = 0; i < par->keynum; i++) {
				if (last->attr[last->keynum] < par->attr[i]) {
					break;
				}
			}
			Btree_node<T>* now = last->child[i];///���׽��Ӧ�øĳ��µ���С��λ�õĽ��
			while (!now->isleaf) {
				now = now->child[0];
			}
			par->attr[i] = now->attr[0];
			par->min = par->attr[0];
		}
		else if (next&&next->keynum > degree / 2) {
			next->keynum--;
			T midkey = next->attr[0];
			int offset = next->blocknum[0];
			Btree_node<T> *child = next->child[0];
			delete_from_node(next, next->attr[0]);
			insert_into_node(node, midkey, offset, child);
			Btree_node<T> * now = next->child[0];
			while (!now->isleaf) {
				now = now->child[0];
			}
			Btree_node<T>* par = node->parent;
			int i;
			for (i = 0; i < par->keynum; i++) {
				if (midkey < par->attr[i])break;
			}
			par->attr[i] = now->attr[0];
		}
		else {}
	}
}
template <class T> void Bplus<T>::Print_leaf() {
	Btree_node<T> *leaf = find_leaf(-1);
	while (leaf != NULL) {
		for (int i = 0; i < leaf->keynum; i++) {
			cout << leaf->attr[i] << " ";
		}
		cout << " <<<<<<< " << endl;
		leaf = leaf->child[0];
	}
}
