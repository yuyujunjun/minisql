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
	parent = child = NULL;
}


Btree_node::~Btree_node()
{
	BM.WriteToDisk(filename,this->block);
}
