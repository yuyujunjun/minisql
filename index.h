#pragma once//��ͷ��Ϣ��Ҫ��һ��������ʾ���Ǹ�����Ҷ�ӽ��
#include"all.h"
#define maxblock 128

//�����ļ���������1��ʼ
template<class T> void  index_create_index(Table table, Attribute attribute, T key, Bplus<T>* btree) {
	int each_length = 30;//ÿ����¼�ĳ���
	int attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//�����Եĳ���
	Block* temp[maxblock];//��ȡ�����¼�Ŀ鲢�洢
	int i = 0;
	int attribute_position = 0;//��������ÿ����¼��λ��
							   //int blocknumber = BM.BlockNum(table.table_name + RECORD);//�ļ����м�����
	int blocknumber = 7;
	for (i = 0; i < table.num_of_attribute; i++) {
		if (attribute.attr_name == table.attribute[i].attr_name)break;
		else {
			attribute_position += GetAttributeLength(table.attribute[i].attr_type, table.attribute[i].attr_len);
		}
	}
	if (i == table.num_of_attribute)return;//û���������

	for (int j = 1; j <= blocknumber; j++) {
		temp[j] = BM.GetBlock("1.txt", j);
		int delet = temp[j]->FirstDelete;//��ʼ����һ����ɾ����λ��
		BM.SetPin(temp[j], true);
		int recordnumber = (temp[j]->Size - BlockHeadSize) / each_length;//����bm�ĺ���
		for (int i = 0; i < recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp[j]->memory + BlockHeadSize + i*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				cout << "delete: " << delet;
			}
			else {
				char* record = new char[100];
				memcpy(record, temp[j]->memory + BlockHeadSize + i*each_length, each_length);
				int offset = j;
				char* char_value = new char[100];
				T value;
				if (attribute.attr_type == INT) {
					memcpy(char_value, record + attribute_position, attri_length);
					sscanf_s(char_value, "%d", &value);
					cout << value << endl;

				}
				else if (attribute.attr_type == FLOAT) {


					memcpy(char_value, record + attribute_position, attri_length);
					sscanf_s(char_value, "%f", &value);
					cout << value << endl;
					//btree_float->insert_into_btree(value, offset);
				}
				else if (attribute.attr_type == CHAR) {


					memcpy(char_value, record + attribute_position, attri_length);
					sscanf_s(char_value, "%s", &value);
					//btree_string->insert_into_btree(value, offset);
					cout << value << endl;
				}
				btree->insert_into_btree(value, offset);
			}
			
		}
	}
	
	return;
}
template<class T>void save_index(Bplus<T>* btree) {

}
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