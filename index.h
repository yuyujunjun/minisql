#pragma once//块头信息需要有一个量来表示它是根还是叶子结点
#include"all.h"
#define maxblock 128

//块在文件中索引从1开始
template<class T> void  index_create_index(Table table, Attribute attribute, T key, Bplus<T>* btree) {
	int each_length = 30;//每条记录的长度
	int attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
	Block* temp[maxblock];//获取储存记录的块并存储
	int i = 0;
	int attribute_position = 0;//该属性在每个记录的位置
							   //int blocknumber = BM.BlockNum(table.table_name + RECORD);//文件中有几个块
	int blocknumber = 7;
	for (i = 0; i < table.num_of_attribute; i++) {
		if (attribute.attr_name == table.attribute[i].attr_name)break;
		else {
			attribute_position += GetAttributeLength(table.attribute[i].attr_type, table.attribute[i].attr_len);
		}
	}
	if (i == table.num_of_attribute)return;//没有这个属性

	for (int j = 1; j <= blocknumber; j++) {
		temp[j] = BM.GetBlock("1.txt", j);
		int delet = temp[j]->FirstDelete;//初始化第一个被删除的位置
		BM.SetPin(temp[j], true);
		int recordnumber = (temp[j]->Size - BlockHeadSize) / each_length;//调用bm的函数
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
void drop_index_record(Attribute index) {//叫buffer删掉index文件

}
int query_on_index(Attribute index) {//获取相应的index的块，获取每个块相对应的属性值和对应的块的位置，重建b+树，然后搜索找到此index可能出现的块，在那个块里面查找，返回值是该属性在文件中的块位置
	return 0;
}
bool insert_into_index(Table table, Attribute attribute) {//如上重建b+树，然后插入值，再写回块
	return true;
}
bool delete_from_index(Table table,Attribute attribute){//如上重建b+树，然后删除值，再写回块
	return true;
}*/