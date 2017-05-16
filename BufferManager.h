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
	void InitalBlock(Block* Resource); //��ʼ����ṹ
	Block* GetBlock(string FileName,int blocknumber = 0);  //���һ����
	void SetPin(Block* BlockNode, bool IfPin);  //����
	void WriteToDisk(string FileName,Block* BlockNode);  //д������
	Block* ReadToBlock(string FileName,int bolcknumber);  //����������
	int GetUsingSize(Block* BlockNode);  //���һ�����ʹ�ô�С
	int BlockNum(string FileName);  //���һ���ļ��ж��ٿ�
	void SetHead(Block* Temp); //ÿ�θ���Block��ı���ʱ�����ô˺������¿�ͷ
	void WriteToMemory(Block* t,char* s, int length); //��һ������д������
	bool IsFull(Block* t,int length); //�жϿ��Ƿ�����,�������򷵻�ture
	bool IsLast(Block* temp); //�жϿ��Ƿ����ļ��е����һ��
	bool IsLeaf(Block* temp); //�ж�������е������Ƿ�ΪB+��Ҷ�ӽ��
};


//#endif

