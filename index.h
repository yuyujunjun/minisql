#pragma once//��ͷ��Ϣ��Ҫ��һ��������ʾ���Ǹ�����Ҷ�ӽ��
#include"all.h"
#define maxblock 128
#define maxlength 64
#define rrrecord_filename "1.txt"
#define iiindex_filename "index_name"
//�����ļ���������1��ʼ
/*void save_index(Bplus<string>* btree, Attribute attribute);
void save_index(Bplus<int>* btree, Attribute attribute);
void save_index(Bplus<float>* btree, Attribute attribute);*/
void  index_create_index(Table table, Attribute attribute, Bplus<string>* btree);
void  index_create_index(Table table, Attribute attribute, Bplus<int>* btree);
void  index_create_index(Table table, Attribute attribute, Bplus<float>* btree);
void saveindex(Btree_node<int>* root, Attribute attribute);
void saveindex(Btree_node<string>* root, Attribute attribute);
void saveindex(Btree_node<float>* root, Attribute attribute);
Btree_node<int>* read_index(int blocksum,int &blockid,string filename,int each_length, int attri_length,int key);
Btree_node<string>* read_index(int blocksum, int &blockid, string filename, int each_length, int attri_length,string key);
Btree_node<float>* read_index(int blocksum, int &blockid, string filename, int each_length, int attri_length,float key);
Bplus<int>* read_from_block(Table table,Attribute index,int key);
Bplus<string>* read_from_block(Table table, Attribute index,string key);
Bplus<float>* read_from_block(Table table, Attribute index,float key);
/*
void drop_index_record(Attribute index) {//��bufferɾ��index�ļ�

}*/
int query_on_index_from_file(Table table, Attribute index,int QAQ);
int query_on_index_from_file(Table table, Attribute index, string QAQ);
int query_on_index_from_file(Table table, Attribute index, float QAQ);
/*bool insert_into_index(Table table, Attribute attribute) {//�����ؽ�b+����Ȼ�����ֵ����д�ؿ�
	return true;
}
bool delete_from_index(Table table,Attribute attribute){//�����ؽ�b+����Ȼ��ɾ��ֵ����д�ؿ�
	return true;
}*/