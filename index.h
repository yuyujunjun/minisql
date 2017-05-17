#pragma once//块头信息需要有一个量来表示它是根还是叶子结点
#include"all.h"
#define maxblock 128
#define maxlength 64
//块在文件中索引从1开始
void save_index(Bplus<string>* btree, Attribute attribute);
void save_index(Bplus<int>* btree, Attribute attribute);
void save_index(Bplus<float>* btree, Attribute attribute);
void  index_create_index(Table table, Attribute attribute, Bplus<string>* btree);
void  index_create_index(Table table, Attribute attribute, Bplus<int>* btree);
void  index_create_index(Table table, Attribute attribute, Bplus<float>* btree);

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