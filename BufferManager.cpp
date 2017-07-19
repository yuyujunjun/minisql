
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
//构造函数

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
//析构函数

void BufferManager::InitalBlock(Block* Resource)
{
	if (false == Resource->pin)
	{
		//初始化各参数
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

		//初始化memory
		memset(Resource->memory, 0, BlockSize);
		memset(Resource->memory, ' ', BlockHeadSize);
		//设置块头信息
		SetHead(Resource);
	}
	else
		cout << "the block is pinned" << endl;
}
/******************************************************************
函数名：void InitalBlock(Block* Resource)
传入参数：一个块的指针
返回值：无
函数功能：将一个块初始化为空块
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
	if (0 == blocknumber)  //该参数缺省，获得一个新的块，位置是文件最后一块的下一个位置
	{
		int i;
		//在缓冲区中找到一个没被使用过的块，并给该块添加一些初始信息
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
		//若缓冲区中块都被使用，则用LRU算法获得新块
		LRUNode * temp;
		temp = LRUHead;
		//找到最后一个没被锁定的块
		while (NULL != temp->aft)
			temp = temp->aft;
		while (true == temp->BlockNode->pin)
			temp = temp->pre;
		//块中的信息被修改过，则写入磁盘
		if (true == temp->BlockNode->IsWritten)
		    WriteToDisk(temp->BlockNode->Filename,temp->BlockNode);
		//将块中的内容清除
		InitalBlock(temp->BlockNode);
		//重构链表
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
		//在缓冲区中找是否存在该块
		for (i = 0; i < MaxBlock; i++)
			if (BufferBlock[i]->Filename == FileName && BufferBlock[i]->BlockNum == blocknumber)
			{
				BufferBlock[i]->last = IsLast(BufferBlock[i]);
				//找到该块对应的LRUNode,并为LRU算法重构链表
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
		//若缓冲区中没有则从文件中读出该块
		return ReadToBlock(FileName, blocknumber);
	}
}
/*******************************************************************
函数名：Block* GetBlock(string FileName,int blocknumber)
传入参数：该块对应的文件名，该块是文件中的第几个块（缺省为0）
返回值：一个块的指针
函数功能：获得一个指定的块或者一个全新的块
********************************************************************/

void BufferManager::SetPin(Block * BlockNode, bool IfPin)
{
	BlockNode->pin = IfPin;
}
//给块上锁，解锁

void BufferManager::WriteToDisk(string FileName, Block * BlockNode)
{
	ifstream file;
	ofstream file2;
	char temp[6];
	int num = 1;
	int size;
	int big = BlockNode->Size;
	int begin = 5;

	//找到给定块该写到文件中的位置
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
	//将块中的信息写到文件中
	if (BlockNode->BlockNum == num)
	{
		file2.open(FileName,ios::in);
		file2.seekp(begin - 5, ios::beg);
		file2.write(BlockNode->memory,big);
		file2.close();
		file2.clear();
		//写到文件后，该块是否被修改过设为否
		BlockNode->IsWritten = false;
	}
	else
		cout << "no such block" << endl;
}
/*********************************************************************
函数名：void WriteToDisk(string FileName, Block * BlockNode)
传入参数：文件名，一个块的指针
返回值：无
函数功能：将一个块写到文件中的指定位置，是覆盖操作，写到文件中不会清
          除缓存。
**********************************************************************/

Block * BufferManager::ReadToBlock(string FileName,int blocknumber)
{
	int i,t;		
	Block* Result;
	ifstream file;
	char temp[6];
	int size;
	int begin = 5;
	//根据一个块的size找下一个块（size存在块头，偏移量为5）
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
	//把找到的块读到缓存中，并根据块头参数和函数参数对返回块进行初始化
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
函数名:Block* ReadToBlock(string FileName,int blocknumber)
传入参数：文件名，文件中的第几个块
返回值：文件中指定块的指针
函数功能：获得指定文件中的指定位置的块
*********************************************************************/

int BufferManager::GetUsingSize(Block * BlockNode)
{
	return BlockNode->Size;
}
//返回块的使用大小

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
	//根据块头中的size找块，直到找不到位置，统计块的数量
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
函数名：int BlockNum(string FileName)
传入参数：文件名
返回值：文件中块的个数
函数功能：计算文件中块的个数
****************************************************************/

void BufferManager::SetHead(Block* Temp)
{
	//块头：块在文件中的位置，块的大小，一条记录的大小，第一条被删除记录的位置，各占5个字符（包括1个空格）
	char offset[5], size[5], record[5], firstdelete[5];
	//memset(offset, 0, 5);
	//memset(size, 0, 5);
	//memset(record, 0, 5);
	//memset(firstdelete, 0, 5);

	//左对齐，右边补空格
	sprintf_s(offset, 5 , "%-4d", Temp->BlockNum);
	offset[strlen(offset)] = ' ';
	sprintf_s(size, 5 , "%-4d", Temp->Size);
	size[strlen(size)] = ' ';
	sprintf_s(record, 5 ,"%-4d", Temp->RecordLength);
	record[strlen(record)] = ' ';
	sprintf_s(firstdelete, 5 , "%-4d", Temp->FirstDelete);
	firstdelete[strlen(firstdelete)] = ' ';
	//将块的重要信息写到块头中
	memcpy(Temp->memory, offset, 5);
	memcpy(Temp->memory + 5, size, 5);
	memcpy(Temp->memory + 10, record, 5);
	memcpy(Temp->memory + 15, firstdelete, 5);
}
/****************************************************************************
函数名：void SetHead(Block* Temp)
传入参数：一个块的指针
返回值：无
函数功能：设置一个块的块头信息，之后可以写入文件
*****************************************************************************/

void BufferManager::WriteToMemory(Block* t,char * s, int length,int recordnumber)
{
	//参数缺省，默认追加到块的最后，插入时使用很方便
	if (0 == recordnumber)
	{
		//块满了不能写，若不是文件中最后一个块，则不能写（改变块大小写回文件时，会覆盖到后面的内容，若块的大小改变，建议设置临时文件）
		if (!IsFull(t, length) && IsLast(t))
		{
			//拷贝到块中
			memcpy(t->memory + t->Size, s, length);
			//更新块的信息
			t->Size += length;
			t->RecordLength = length;
			t->IsWritten = true;
			//重设块头
			SetHead(t);
		}
		else
			cout << "the block can not be wrote" << endl;
	}
	//写到块的指定位置，由于不判断是否为最后一个块，该函数不安全，需要保证此操作不改变块的大小
	else
	{
		if ((recordnumber*length + BlockHeadSize) <= t->Size)
		{
			//拷贝到块中
			memcpy(t->memory + (recordnumber - 1)*length + BlockHeadSize, s, length);
			//更新块的新的
			t->RecordLength = length;
			t->IsWritten = true;
			//重设块头
			SetHead(t);
		}
		else
			cout << "the block is too small" << endl;
	}
}
/********************************************************************************
函数名：void WriteToMemory(Block* t,char * s, int length,int recordnumber)
传入参数：一个块的指针，要写入块的内容，该内容长度，写到块中的位置（缺省默认追
          加到最后）
返回值：无
函数功能
*********************************************************************************/

char* BufferManager::GetRecordByNum(Block * t, int recordnumber,int length)
{
	char* s;
	s = new char[length + 1];
	s[length] = 0;
	memcpy(s,t->memory+BlockHeadSize+(recordnumber-1)*length,length);
	return s;
}
//读取文件中指定（第i条）记录

bool BufferManager::IsFull(Block * t,int length)
{
	if (t->Size + length < BlockSize)
		return false;
	else
		return true;
}
//判断块是否满了

bool BufferManager::IsLast(Block * temp)
{
	if (temp->BlockNum >= BlockNum(temp->Filename))
		return true;
	else
		return false;
}
//判断块是否是文件中的最后一个块

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
//判断该块是否为叶节点

int BufferManager::GetRecordNum(Block * temp, int length)
{
	return (temp->Size-BlockHeadSize) / length;
}
//获得该块中有多少条记录
