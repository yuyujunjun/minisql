#pragma once

//#ifndef _BuferManager_H_
//#define _BuferManager_H_
#include "all.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

#define BlockSize 1024*4
#define MaxBlock 256
#define BlockHeadSize 64

class BufferManager
{
public:
	Block* BufferBlock[MaxBlock];
	LRUNode* LRUHead;

	BufferManager();
	~BufferManager();

	void InitalBlock(Block* Resource); //初始化块结构
	Block* GetBlock(string FileName,int blocknumber = 0);  //获得一个块	 缺省参数得到新块，否则得到文件中第i块
	Block* ReadToBlock(string FileName,int bolcknumber);  //读到缓冲区的块中
	void WriteToDisk(string FileName,Block* BlockNode);  //写到磁盘	
	void SetPin(Block* BlockNode, bool IfPin);  //上锁（解锁）
	void SetHead(Block* Temp); //更新块头信息 更新Block结构内变量时要更新块头信息

	void WriteToMemory(Block* t,char* s, int length,int recordnumber=0); //将一段内容写进块的最后(文件的指定位置) 该内容应该与该文件（表，索引）中记录等长，不足部分补空格
	char* GetRecordByNum(Block* t, int recordnumber,int length); //读取块中第i条记录

	int GetUsingSize(Block* BlockNode);  //获得一个块的使用大小
	int BlockNum(string FileName);  //获得一个文件有多少块	
	int GetRecordNum(Block* temp, int length); //计算这个块中有多少条记录

	bool IsFull(Block* t,int length); //判断块是否满了,若满了则返回ture
	bool IsLast(Block* temp); //判断块是否是文件中的最后一个
	bool IsLeaf(Block* temp); //判断这个块中的数据是否为B+树叶子结点

};


//#endif

