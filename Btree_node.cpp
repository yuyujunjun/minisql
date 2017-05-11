#include "stdafx.h"
#include "Btree_node.h"
extern BufferManager BM;
Btree_node::Btree_node(int type, int typelength, string indexname)
{
	int attri_length =GetAttributeLength(type, typelength);
	int offset_length = GetAttributeLength(INT);
	keynum = (BlockSize - BlockHeadSize)/(attri_length+offset_length);
	filename = "index_" + indexname + ".record";
	this->block = BM.GetBlock(filename);
	parent  = NULL;
	
}
Btree_node::Btree_node(Block* block, int type, int typelength, string indexname) {//已经有块了，从缓存中把块生成结点，再生成b+树
	int attri_length = GetAttributeLength(type, typelength);
	int offset_length = GetAttributeLength(INT);
	keynum = (BlockSize - BlockHeadSize) / (attri_length + offset_length);
	filename = "index_" + indexname + ".record";
	this->block = block;
	parent =  NULL;
}

Btree_node::~Btree_node()
{
	BM.WriteToDisk(filename,this->block);
}
