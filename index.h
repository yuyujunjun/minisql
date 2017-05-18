#pragma once//块头信息需要有一个量来表示它是根还是叶子结点
#include"all.h"
#define maxblock 128
#define maxlength 64
#define rrrecord_filename "1.txt"
#define iiindex_filename "index_name"
#define tempfile "TEMPFILE"
//块在文件中索引从1开始
/*void save_index(Bplus<string>* btree, Attribute attribute);
void save_index(Bplus<int>* btree, Attribute attribute);
void save_index(Bplus<float>* btree, Attribute attribute);*/
void  index_create_index(Table table, Attribute attribute, Bplus<string>* btree,string __indexname__);
void  index_create_index(Table table, Attribute attribute, Bplus<int>* btree, string __indexname__);
void  index_create_index(Table table, Attribute attribute, Bplus<float>* btree, string __indexname__);
void saveindex(Btree_node<int>* root, Attribute attribute,int &index,string filename);
void saveindex(Btree_node<string>* root, Attribute attribute,int &index, string filename);
void saveindex(Btree_node<float>* root, Attribute attribute,int &index, string filename);
Btree_node<int>* read_index(int blocksum,int &blockid,string filename,int each_length, int attri_length,int key);
Btree_node<string>* read_index(int blocksum, int &blockid, string filename, int each_length, int attri_length,string key);
Btree_node<float>* read_index(int blocksum, int &blockid, string filename, int each_length, int attri_length,float key);
Bplus<int>* read_from_block(Table table,Attribute index,int key, string __indexname__);
Bplus<string>* read_from_block(Table table, Attribute index,string key, string __indexname__);
Bplus<float>* read_from_block(Table table, Attribute index,float key, string __indexname__);

int query_on_index_from_file(Table table, Attribute index,int QAQ, string __indexname__);
int query_on_index_from_file(Table table, Attribute index, string QAQ, string __indexname__);
int query_on_index_from_file(Table table, Attribute index, float QAQ, string __indexname__);
bool insert_into_index(Table table, Attribute attribute, int QAQ,int offset, string __indexname__); //如上重建b+树，然后插入值，再写回块
bool insert_into_index(Table table, Attribute attribute, string QAQ,int offset, string __indexname__); //如上重建b+树，然后插入值，再写回块
bool insert_into_index(Table table, Attribute attribute, float QAQ,int offset, string __indexname__); //如上重建b+树，然后插入值，再写回块

bool delete_from_index(Table table, Attribute attribute,int QAQ,string __indexname__);//如上重建b+树，然后删除值，再写回块
bool delete_from_index(Table table, Attribute attribute, string QAQ, string __indexname__);
bool delete_from_index(Table table, Attribute attribute, float QAQ, string __indexname__);
void rewrite(string oldname);