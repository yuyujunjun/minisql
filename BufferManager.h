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
	void InitalBlock(); //��ʼ����ṹ
	Block* GetBlock(string FileName,int blocknumber = 0);  //���һ����
	void SetPin(Block* BlockNode);  //����
	void WriteToDisk(string FileName,Block* BlockNode);  //д������
	Block* ReadToBlock(string FileName, int OffSet);  //����������
	int GetUsingSize(Block* BlockNode);  //���һ�����ʹ�ô�С
	int BlockNum(string FileName);  //���һ���ļ��ж��ٿ�
	void SetHead(Block* Temp); //ÿ�θ���Block��ı���ʱ�����ô˺������¿�ͷ
	void WriteToMemory(char* s, int length); //��һ������д������
};


#endif