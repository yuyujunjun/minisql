#pragma once

//#ifndef _BuferManager_H_
//#define _BuferManager_H_
#include "all.h"
#define BlockSize 1024*4
#define MaxBlock 4
#define BlockHeadSize 64

class BufferManager
{
public:
	Block* BufferBlock[MaxBlock];
	LRUNode* LRUHead;
	BufferManager();
	~BufferManager();
	void InitalBlock(Block* Resource); //初始化块结构
	Block* GetBlock(string FileName,int blocknumber = 0);  //获得一个块
	void SetPin(Block* BlockNode, bool IfPin);  //上锁
	void WriteToDisk(string FileName,Block* BlockNode);  //写到磁盘
	Block* ReadToBlock(string FileName,int bolcknumber);  //读到缓冲区
	int GetUsingSize(Block* BlockNode);  //获得一个块的使用大小
	int BlockNum(string FileName);  //获得一个文件有多少块
	void SetHead(Block* Temp); //每次更新Block里的变量时，调用此函数更新块头
	void WriteToMemory(Block* t,char* s, int length); //将一段内容写进块中
	bool IsFull(Block* t,int length); //判断块是否满了,若满了则返回ture
	bool IsLast(Block* temp); //判断块是否是文件中的最后一个
	bool IsLeaf(Block* temp); //判断这个块中的数据是否为B+树叶子结点
};


//#endif

