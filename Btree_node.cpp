#include "stdafx.h"
#include "Btree_node.h"
extern BufferManager BM;
Btree_node::Btree_node(string filename)
{
	keynum = 0;
	//this->block = BM.GetBlock(filename);
	parent  = NULL;
	isleaf = 0;
	isroot = 0;
	int_min = 0;
//	float_min = 0;
//	string_min = '\0';
}
/**
Btree_node::Btree_node(Block* block, int type, int typelength, string filename) {//�Ѿ��п��ˣ��ӻ����аѿ����ɽ�㣬������b+��
	int attri_length = GetAttributeLength(type, typelength);
	int offset_length = GetAttributeLength(INT);
	keynum = (BlockSize - BlockHeadSize) / (attri_length + offset_length);
	
	this->block = block;
	parent =  NULL;
	isleaf = 0;
	int_min = 0;
	float_min = 0;
	string_min = '\0';
}
*/
Btree_node::~Btree_node()
{
	//BM.WriteToDisk(filename,this->block);
}
