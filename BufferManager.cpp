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

Block* BufferManager::GetBlock(string FileName,int blocknumber)

{
	fstream file;
	file.open(FileName, ios::in);
	if (!file)
	{
		cout << "no such file" << endl;
		return NULL;
	}
	if (0 == blocknumber)
	{
		int i;
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
		//LRU
		LRUNode * temp;
		temp = LRUHead;
		while (NULL != temp->aft)
			temp = temp->aft;
		while (true == temp->BlockNode->pin)
			temp = temp->pre;
		if (true == temp->BlockNode->IsWritten)
		    WriteToDisk(temp->BlockNode->Filename,temp->BlockNode);
		InitalBlock(temp->BlockNode);

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
		for (i = 0; i < MaxBlock; i++)
			if (BufferBlock[i]->Filename == FileName && BufferBlock[i]->BlockNum == blocknumber)
			{
				BufferBlock[i]->last = IsLast(BufferBlock[i]);
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
		return ReadToBlock(FileName, blocknumber);
	}
}

void BufferManager::SetPin(Block * BlockNode, bool IfPin)
{
	BlockNode->pin = IfPin;
}

void BufferManager::WriteToDisk(string FileName, Block * BlockNode)
{
	ifstream file;
	ofstream file2;
	char temp[6];
	int num = 1;
	int size;
	int big = BlockNode->Size;
	int begin = 5;

	file.open(FileName);
	file.seekg(begin, ios::beg);
	temp[5] = 0;
	while (file.read(temp, 5))
	{
		sscanf_s(temp, "%d", &size);
		begin += size;
		file.seekg(begin, ios::beg);
		num++;
		if (BlockNode->BlockNum == num)
			break;
	}
	file.close();
	file.clear();
	if (BlockNode->BlockNum == num)
	{
		file2.open(FileName,ios::in);
		file2.seekp(begin - 5, ios::beg);
		file2.write(BlockNode->memory,big);
		file2.close();
		file2.clear();
		BlockNode->IsWritten = false;
	}
	else
		cout << "no such block" << endl;
}

Block * BufferManager::ReadToBlock(string FileName,int blocknumber)
{
	int i,t;		
	Block* Result;
	ifstream file;
	char temp[6];
	int size;
	int begin = 5;
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

int BufferManager::GetUsingSize(Block * BlockNode)
{
	return BlockNode->Size;
}

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


void BufferManager::WriteToMemory(Block* t,char * s, int length,int recordnumber)
{
	if (0 == recordnumber)
	{
		if (!IsFull(t, length) && IsLast(t))
		{
			memcpy(t->memory + t->Size, s, length);
			t->Size += length;
			t->RecordLength = length;
			t->IsWritten = true;
			SetHead(t);
		}
		else
			cout << "the block can not be wrote" << endl;
	}
	else
	{
		if ((recordnumber*length + BlockHeadSize) <= t->Size)
		{
			memcpy(t->memory + (recordnumber - 1)*length + BlockHeadSize, s, length);
			t->RecordLength = length;
			t->IsWritten = true;
			SetHead(t);
		}
		else
			cout << "the block is too small" << endl;
	}
}

char* BufferManager::GetRecordByNum(Block * t, int recordnumber,int length)
{
	char* s;
	s = new char[length + 1];
	s[length] = 0;
	memcpy(s,t->memory+BlockHeadSize+(recordnumber-1)*length,length);
	return s;
}

bool BufferManager::IsFull(Block * t,int length)
{
	if (t->Size + length < BlockSize)
		return false;
	else
		return true;
}

bool BufferManager::IsLast(Block * temp)
{
	if (temp->BlockNum >= BlockNum(temp->Filename))
		return true;
	else
		return false;
}

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

int BufferManager::GetRecordNum(Block * temp, int length)
{
	return (temp->Size-BlockHeadSize) / length;
}

