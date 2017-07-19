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

	void InitalBlock(Block* Resource); //��ʼ����ṹ
	Block* GetBlock(string FileName,int blocknumber = 0);  //���һ����	 ȱʡ�����õ��¿飬����õ��ļ��е�i��
	Block* ReadToBlock(string FileName,int bolcknumber);  //�����������Ŀ���
	void WriteToDisk(string FileName,Block* BlockNode);  //д������	
	void SetPin(Block* BlockNode, bool IfPin);  //������������
	void SetHead(Block* Temp); //���¿�ͷ��Ϣ ����Block�ṹ�ڱ���ʱҪ���¿�ͷ��Ϣ

	void WriteToMemory(Block* t,char* s, int length,int recordnumber=0); //��һ������д��������(�ļ���ָ��λ��) ������Ӧ������ļ������������м�¼�ȳ������㲿�ֲ��ո�
	char* GetRecordByNum(Block* t, int recordnumber,int length); //��ȡ���е�i����¼

	int GetUsingSize(Block* BlockNode);  //���һ�����ʹ�ô�С
	int BlockNum(string FileName);  //���һ���ļ��ж��ٿ�	
	int GetRecordNum(Block* temp, int length); //������������ж�������¼

	bool IsFull(Block* t,int length); //�жϿ��Ƿ�����,�������򷵻�ture
	bool IsLast(Block* temp); //�жϿ��Ƿ����ļ��е����һ��
	bool IsLeaf(Block* temp); //�ж�������е������Ƿ�ΪB+��Ҷ�ӽ��

};


//#endif

