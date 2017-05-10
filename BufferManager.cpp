#include "stdafx.h"
#include "BufferManager.h"
#include <iostream>
#include <sstream>
using namespace std;

BufferManager::BufferManager()
{
	int i;
	for (i = 0; i < MaxBlock; i++)
	{
		BufferBlock[i] = new Block;
		if (NULL == BufferBlock[i])
			cout << "out of memory" << endl;
	}
}


BufferManager::~BufferManager()
{
	int i;
	for (i = 0; i < MaxBlock; i++)
	{
		if (NULL != BufferBlock[i])
		{
			if (NULL != BufferBlock[i]->memory)
				delete BufferBlock[i]->memory;
			delete BufferBlock[i];
		}
	}
}

void BufferManager::InitalBlock()
{
	int i;
	for (i = 0; i < MaxBlock; i++)
	{
		//初始化各参数
		BufferBlock[i]->Filename = "";
		BufferBlock[i]->BlockNum = -1;
		BufferBlock[i]->HeadOffset = -1;
		BufferBlock[i]->Size = BlockHeadSize;
		BufferBlock[i]->RecordLength = -1;
		BufferBlock[i]->FirstRecord = "";
		BufferBlock[i]->pin = false;
		BufferBlock[i]->IsWritten = false;
		BufferBlock[i]->FirstDelete = BlockSize + 1;
		BufferBlock[i]->memory = new char[BlockSize];
		BufferBlock[i]->last = true;
		if (NULL == BufferBlock[i] || NULL == BufferBlock[i]->memory)
		{
			cout << "out of memory" << endl;
			exit(1);
		}
		//初始化memory
		memset(BufferBlock[i]->memory, 0, BlockSize);
		memset(BufferBlock[i]->memory, ' ', BlockHeadSize);
		//设置块头信息
		BufferManager::SetHead(BufferBlock[i]);
	}
}

Block* BufferManager::GetBlock(string FileName, int Offset)
{
	return NULL;
}

void BufferManager::SetPin(Block * BlockNode)
{
	BlockNode->pin = true;
}

void BufferManager::WriteToDisk(string FileName, Block * BlockNode)
{
}

Block * BufferManager::ReadToBlock(string FileName, int OffSet)
{
	return nullptr;
}

int BufferManager::GetUsingSize(Block * BlockNode)
{
	return BlockNode->BlockNum;
}

int BufferManager::BlockNum(string FileName)
{
	return 0;
}

void BufferManager::SetHead(Block* Temp)
{
	char offset[5], size[5], record[5], firstdelete[5];
	//memset(offset, 0, 5);
	//memset(size, 0, 5);
	//memset(record, 0, 5);
	//memset(firstdelete, 0, 5);
	sprintf_s(offset, 5 , "%-4d", Temp->BlockNum);
	offset[strlen(offset)] = ' ';
	sprintf_s(size, 5 , "%-4d", Temp->Size);
	size[strlen(size)] = ' ';
	sprintf_s(record, 5 ,"%-4d", Temp->RecordLength);
	record[strlen(record)] = ' ';
	sprintf_s(firstdelete, 5 , "%-4d", Temp->FirstDelete);
	firstdelete[strlen(firstdelete)] = ' ';
	memcpy(Temp->memory, offset, 5);
	memcpy(Temp->memory + 5, size, 5);
	memcpy(Temp->memory + 10, record, 5);
	memcpy(Temp->memory + 15, firstdelete, 5);
}

