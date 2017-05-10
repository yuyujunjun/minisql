#pragma once

#ifndef _BuferManager_H_
#define _BuferManager_H_
#include "minisql.h"

#define BlockSize 1024*4
#define MaxBlock 8
#define BlockHeadSize 64

class BufferManager
{
public:
	Block* BufferBlock[MaxBlock];
	BufferManager();
	~BufferManager();
	void InitalBlock(); //初始化块结构
	Block* GetBlock(string FileName,int blocknumber = 0);  //获得一个块
	void SetPin(Block* BlockNode);  //上锁
	void WriteToDisk(string FileName,Block* BlockNode);  //写到磁盘
	Block* ReadToBlock(string FileName, int OffSet);  //读到缓冲区
	int GetUsingSize(Block* BlockNode);  //获得一个块的使用大小
	int BlockNum(string FileName);  //获得一个文件有多少块
	void SetHead(Block* Temp); //每次更新Block里的变量时，调用此函数更新块头
	void WriteToMemory(char* s, int length); //将一段内容写进块中
};


#endif