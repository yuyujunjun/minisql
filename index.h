#pragma once//��ͷ��Ϣ��Ҫ��һ��������ʾ���Ǹ�����Ҷ�ӽ��
#include"all.h"
#define maxblock 128
#define maxlength 64
//�����ļ���������1��ʼ
void save_index(Bplus<string>* btree, Attribute attribute);
void save_index(Bplus<int>* btree, Attribute attribute);
void save_index(Bplus<float>* btree, Attribute attribute);
void  index_create_index(Table table, Attribute attribute, Bplus<string>* btree);
void  index_create_index(Table table, Attribute attribute, Bplus<int>* btree);
void  index_create_index(Table table, Attribute attribute, Bplus<float>* btree);

/*
void drop_index_record(Attribute index) {//��bufferɾ��index�ļ�

}
int query_on_index(Attribute index) {//��ȡ��Ӧ��index�Ŀ飬��ȡÿ�������Ӧ������ֵ�Ͷ�Ӧ�Ŀ��λ�ã��ؽ�b+����Ȼ�������ҵ���index���ܳ��ֵĿ飬���Ǹ���������ң�����ֵ�Ǹ��������ļ��еĿ�λ��
	return 0;
}
bool insert_into_index(Table table, Attribute attribute) {//�����ؽ�b+����Ȼ�����ֵ����д�ؿ�
	return true;
}
bool delete_from_index(Table table,Attribute attribute){//�����ؽ�b+����Ȼ��ɾ��ֵ����д�ؿ�
	return true;
}*/