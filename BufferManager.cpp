
#include "stdafx.h"
#include "BufferManager.h"

BufferManager::BufferManager()
{
	int i;
	for (i = 0; i < MaxBlock; i++)
	{
		BufferBlock[i] = new Block;
		if (NULL == BufferBlock[i])
			cout << "out of memory" << endl;
	}
	for (i = 0; i < MaxBlock; i++)
	{
		SetPin(BufferBlock[i], false);
		InitalBlock(BufferBlock[i]);
	}

	LRUHead = new LRUNode;
	LRUHead->BlockNode = NULL;
	LRUHead->pre = NULL;
	LRUHead->aft = NULL;
}
//���캯��

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
	LRUNode * temp;
	temp = LRUHead;
	while (temp->aft != NULL)
	{
		temp = temp->aft;
		delete temp->pre;
	}
	delete temp;
}
//��������

void BufferManager::InitalBlock(Block* Resource)
{
	if (false == Resource->pin)
	{
		//��ʼ��������
		Resource->Filename = "";
		Resource->BlockNum = -1;
		Resource->Size = BlockHeadSize;
		Resource->RecordLength = -1;
		Resource->IsLeaf = false;
		Resource->pin = false;
		Resource->IsWritten = false;
		Resource->FirstDelete = BlockSize + 1;
		Resource->memory = new char[BlockSize];
		if (NULL == Resource->memory)
		{
			cout << "out of memory" << endl;
			exit(1);
		}
		Resource->last = true;

		//��ʼ��memory
		memset(Resource->memory, 0, BlockSize);
		memset(Resource->memory, ' ', BlockHeadSize);
		//���ÿ�ͷ��Ϣ
		SetHead(Resource);
	}
	else
		cout << "the block is pinned" << endl;
}
/******************************************************************
��������void InitalBlock(Block* Resource)
���������һ�����ָ��
����ֵ����
�������ܣ���һ�����ʼ��Ϊ�տ�
*******************************************************************/


Block* BufferManager::GetBlock(string FileName,int blocknumber)

{
	fstream file;
	file.open(FileName, ios::in);
	if (!file)
	{
		cout << "no such file" << endl;
		return NULL;
	}
	if (0 == blocknumber)  //�ò���ȱʡ�����һ���µĿ飬λ�����ļ����һ�����һ��λ��
	{
		int i;
		//�ڻ��������ҵ�һ��û��ʹ�ù��Ŀ飬�����ÿ����һЩ��ʼ��Ϣ
		for (i = 0; i < MaxBlock; i++)
			if (BufferBlock[i]->Filename == "")
			{
				BufferBlock[i]->BlockNum = BlockNum(FileName)+1;
				BufferBlock[i]->Filename = FileName;
				BufferBlock[i]->FirstDelete = BlockSize+1;
				BufferBlock[i]->IsLeaf = false;
				BufferBlock[i]->IsWritten = false;
				BufferBlock[i]->last = IsLast(BufferBlock[i]);
				BufferBlock[i]->pin = false;
				BufferBlock[i]->RecordLength = -1;
				BufferBlock[i]->Size = BlockHeadSize;
				SetHead(BufferBlock[i]);

				LRUNode * temp = new LRUNode;
				temp->pre = LRUHead;
				temp->aft = LRUHead->aft;
				temp->BlockNode = BufferBlock[i];
				if (NULL != LRUHead->aft)
				    LRUHead->aft->pre = temp;
				LRUHead->aft = temp;

				return BufferBlock[i];
			}
		//���������п鶼��ʹ�ã�����LRU�㷨����¿�
		LRUNode * temp;
		temp = LRUHead;
		//�ҵ����һ��û�������Ŀ�
		while (NULL != temp->aft)
			temp = temp->aft;
		while (true == temp->BlockNode->pin)
			temp = temp->pre;
		//���е���Ϣ���޸Ĺ�����д�����
		if (true == temp->BlockNode->IsWritten)
		    WriteToDisk(temp->BlockNode->Filename,temp->BlockNode);
		//�����е��������
		InitalBlock(temp->BlockNode);
		//�ع�����
		temp->pre->aft = temp->aft;
		if (NULL != temp->aft)
			temp->aft->pre = temp->pre;
		temp->pre = LRUHead;
		temp->aft = LRUHead->aft;
		if (NULL != LRUHead->aft)
			LRUHead->aft->pre = temp;
		LRUHead->aft = temp;
		return temp->BlockNode;
	}
	else
	{
		int i;
		LRUNode* temp;
		temp = LRUHead;
		//�ڻ����������Ƿ���ڸÿ�
		for (i = 0; i < MaxBlock; i++)
			if (BufferBlock[i]->Filename == FileName && BufferBlock[i]->BlockNum == blocknumber)
			{
				BufferBlock[i]->last = IsLast(BufferBlock[i]);
				//�ҵ��ÿ��Ӧ��LRUNode,��ΪLRU�㷨�ع�����
				while (NULL != temp->aft)
				{
					temp = temp->aft;
					if (temp->BlockNode == BufferBlock[i])
						break;
				}
				if (temp->BlockNode == BufferBlock[i])
				{
					temp->pre->aft = temp->aft;
					if (NULL != temp->aft)
					    temp->aft->pre = temp->pre;
					temp->pre = LRUHead;
					temp->aft = LRUHead->aft;
					if (NULL != LRUHead->aft)
					    LRUHead->aft->pre = temp;
					LRUHead->aft = temp;
					return BufferBlock[i];
				}
				else
				{
					cout << "no such LRUNode" << endl;
					return NULL;
				}
			}
		//����������û������ļ��ж����ÿ�
		return ReadToBlock(FileName, blocknumber);
	}
}
/*******************************************************************
��������Block* GetBlock(string FileName,int blocknumber)
����������ÿ��Ӧ���ļ������ÿ����ļ��еĵڼ����飨ȱʡΪ0��
����ֵ��һ�����ָ��
�������ܣ����һ��ָ���Ŀ����һ��ȫ�µĿ�
********************************************************************/

void BufferManager::SetPin(Block * BlockNode, bool IfPin)
{
	BlockNode->pin = IfPin;
}
//��������������

void BufferManager::WriteToDisk(string FileName, Block * BlockNode)
{
	ifstream file;
	ofstream file2;
	char temp[6];
	int num = 1;
	int size;
	int big = BlockNode->Size;
	int begin = 5;

	//�ҵ��������д���ļ��е�λ��
	file.open(FileName);
	file.seekg(begin, ios::beg);
	temp[5] = 0;
	while (file.read(temp, 5))
	{
		if (BlockNode->BlockNum == num)
			break;
		sscanf_s(temp, "%d", &size);
		begin += size;
		file.seekg(begin, ios::beg);
		num++;
	}
	file.close();
	file.clear();
	//�����е���Ϣд���ļ���
	if (BlockNode->BlockNum == num)
	{
		file2.open(FileName,ios::in);
		file2.seekp(begin - 5, ios::beg);
		file2.write(BlockNode->memory,big);
		file2.close();
		file2.clear();
		//д���ļ��󣬸ÿ��Ƿ��޸Ĺ���Ϊ��
		BlockNode->IsWritten = false;
	}
	else
		cout << "no such block" << endl;
}
/*********************************************************************
��������void WriteToDisk(string FileName, Block * BlockNode)
����������ļ�����һ�����ָ��
����ֵ����
�������ܣ���һ����д���ļ��е�ָ��λ�ã��Ǹ��ǲ�����д���ļ��в�����
          �����档
**********************************************************************/

Block * BufferManager::ReadToBlock(string FileName,int blocknumber)
{
	int i,t;		
	Block* Result;
	ifstream file;
	char temp[6];
	int size;
	int begin = 5;
	//����һ�����size����һ���飨size���ڿ�ͷ��ƫ����Ϊ5��
	file.open(FileName);
	file.seekg(begin, ios::beg);
	temp[5] = 0;
	for (i = 0; i < blocknumber; i++)
	{
		if (file.read(temp, 5))
		{
			sscanf_s(temp, "%d", &size);
			begin += size;
			file.seekg(begin, ios::beg);
		}
		else
		{
			cout << "no such block" << endl;
			file.close();
			file.clear();
			return NULL;
		}
	}
	//���ҵ��Ŀ���������У������ݿ�ͷ�����ͺ��������Է��ؿ���г�ʼ��
	begin = begin - 5 - size;
	file.seekg(begin, ios::beg);
	if (file.read(temp, 5))
	{
		Result = GetBlock(FileName);
		Result->BlockNum = blocknumber;
		Result->Filename = FileName;
		file.seekg(begin + 15, ios::beg);
		file.read(temp, 5);
		sscanf_s(temp, "%d", &t);
		Result->FirstDelete = t;
		Result->IsLeaf = false;
		Result->IsWritten = false;
		Result->last = IsLast(Result);
		Result->pin = false;
		file.seekg(begin + 10, ios::beg);
		file.read(temp , 5);
		sscanf_s(temp, "%d", &t);
		Result->RecordLength = t;
		Result->Size = size;
		file.seekg(begin , ios::beg);
		file.read(Result->memory, size);
		file.close();
		file.clear();
		return Result;
	}
	else
	{
		cout << "no such block" << endl;
		file.close();
		file.clear();
		return NULL;
	}
}
/********************************************************************
������:Block* ReadToBlock(string FileName,int blocknumber)
����������ļ������ļ��еĵڼ�����
����ֵ���ļ���ָ�����ָ��
�������ܣ����ָ���ļ��е�ָ��λ�õĿ�
*********************************************************************/

int BufferManager::GetUsingSize(Block * BlockNode)
{
	return BlockNode->Size;
}
//���ؿ��ʹ�ô�С

int BufferManager::BlockNum(string FileName)
{
	ifstream file;
	char temp[6];
	int num = 0;
	int size;
	int begin = 5;

	file.open(FileName);
	file.seekg(begin,ios::beg);	
	temp[5] = 0;
	//���ݿ�ͷ�е�size�ҿ飬ֱ���Ҳ���λ�ã�ͳ�ƿ������
	while (file.read(temp, 5))
	{
			sscanf_s(temp, "%d", &size);
			num++;
			begin += size;
			file.seekg(begin, ios::beg);
	}
	file.close();
	file.clear();

	return num;
}
/***************************************************************
��������int BlockNum(string FileName)
����������ļ���
����ֵ���ļ��п�ĸ���
�������ܣ������ļ��п�ĸ���
****************************************************************/

void BufferManager::SetHead(Block* Temp)
{
	//��ͷ�������ļ��е�λ�ã���Ĵ�С��һ����¼�Ĵ�С����һ����ɾ����¼��λ�ã���ռ5���ַ�������1���ո�
	char offset[5], size[5], record[5], firstdelete[5];
	//memset(offset, 0, 5);
	//memset(size, 0, 5);
	//memset(record, 0, 5);
	//memset(firstdelete, 0, 5);

	//����룬�ұ߲��ո�
	sprintf_s(offset, 5 , "%-4d", Temp->BlockNum);
	offset[strlen(offset)] = ' ';
	sprintf_s(size, 5 , "%-4d", Temp->Size);
	size[strlen(size)] = ' ';
	sprintf_s(record, 5 ,"%-4d", Temp->RecordLength);
	record[strlen(record)] = ' ';
	sprintf_s(firstdelete, 5 , "%-4d", Temp->FirstDelete);
	firstdelete[strlen(firstdelete)] = ' ';
	//�������Ҫ��Ϣд����ͷ��
	memcpy(Temp->memory, offset, 5);
	memcpy(Temp->memory + 5, size, 5);
	memcpy(Temp->memory + 10, record, 5);
	memcpy(Temp->memory + 15, firstdelete, 5);
}
/****************************************************************************
��������void SetHead(Block* Temp)
���������һ�����ָ��
����ֵ����
�������ܣ�����һ����Ŀ�ͷ��Ϣ��֮�����д���ļ�
*****************************************************************************/

void BufferManager::WriteToMemory(Block* t,char * s, int length,int recordnumber)
{
	//����ȱʡ��Ĭ��׷�ӵ������󣬲���ʱʹ�úܷ���
	if (0 == recordnumber)
	{
		//�����˲���д���������ļ������һ���飬����д���ı���Сд���ļ�ʱ���Ḳ�ǵ���������ݣ�����Ĵ�С�ı䣬����������ʱ�ļ���
		if (!IsFull(t, length) && IsLast(t))
		{
			//����������
			memcpy(t->memory + t->Size, s, length);
			//���¿����Ϣ
			t->Size += length;
			t->RecordLength = length;
			t->IsWritten = true;
			//�����ͷ
			SetHead(t);
		}
		else
			cout << "the block can not be wrote" << endl;
	}
	//д�����ָ��λ�ã����ڲ��ж��Ƿ�Ϊ���һ���飬�ú�������ȫ����Ҫ��֤�˲������ı��Ĵ�С
	else
	{
		if ((recordnumber*length + BlockHeadSize) <= t->Size)
		{
			//����������
			memcpy(t->memory + (recordnumber - 1)*length + BlockHeadSize, s, length);
			//���¿���µ�
			t->RecordLength = length;
			t->IsWritten = true;
			//�����ͷ
			SetHead(t);
		}
		else
			cout << "the block is too small" << endl;
	}
}
/********************************************************************************
��������void WriteToMemory(Block* t,char * s, int length,int recordnumber)
���������һ�����ָ�룬Ҫд�������ݣ������ݳ��ȣ�д�����е�λ�ã�ȱʡĬ��׷
          �ӵ����
����ֵ����
��������
*********************************************************************************/

char* BufferManager::GetRecordByNum(Block * t, int recordnumber,int length)
{
	char* s;
	s = new char[length + 1];
	s[length] = 0;
	memcpy(s,t->memory+BlockHeadSize+(recordnumber-1)*length,length);
	return s;
}
//��ȡ�ļ���ָ������i������¼

bool BufferManager::IsFull(Block * t,int length)
{
	if (t->Size + length < BlockSize)
		return false;
	else
		return true;
}
//�жϿ��Ƿ�����

bool BufferManager::IsLast(Block * temp)
{
	if (temp->BlockNum >= BlockNum(temp->Filename))
		return true;
	else
		return false;
}
//�жϿ��Ƿ����ļ��е����һ����

bool BufferManager::IsLeaf(Block * temp)
{
	char s[11];
	int t;
	s[10] = 0;
	memcpy(s,temp->memory+BlockHeadSize,10);
	sscanf_s(s, "%d", &t);
	if (0 < t)
		return true;
	else
		return false;
}
//�жϸÿ��Ƿ�ΪҶ�ڵ�

int BufferManager::GetRecordNum(Block * temp, int length)
{
	return (temp->Size-BlockHeadSize) / length;
}
//��øÿ����ж�������¼
