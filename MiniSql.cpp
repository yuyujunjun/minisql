// MiniSql.cpp : Defines the entry point for the console application.
//

#include"all.h"
#include<string>
#include<iostream>

using namespace std;
BufferManager BM;

/*
int main()
{
	string command;
	int status=-1;
	Interpreter inter;

	while (true) {
		cout << ENTER;
		getline(cin, command, ';');
		status = inter.interpreter(command);
		if (status == quit)break;
		
	}
	return 0;
}
*/

/* WriteToMemory怎么用?
void main()
{
	char* s;
	s = new char[4096];
	BM.WriteToMemory(BM.BufferBlock[0],"abc",3);
	BM.WriteToMemory(BM.BufferBlock[0], "abc", 3);
	memcpy(s, BM.BufferBlock[0]->memory, 4096);
	cout << s;
	getchar();
}
*/

/*检查BlockNum
void main()
{
	int result;
	result = BM.BlockNum("test.txt");
	cout << result;
	getchar();
}
//*/

/*
void main()
{
	for (int i = 0; i < 3; i++)
	{
		BM.BufferBlock[i]->BlockNum = i+1;
		BM.BufferBlock[i]->Filename = "1.txt";
		BM.BufferBlock[i]->FirstDelete = 4097;
		BM.BufferBlock[i]->RecordLength = 1;
		BM.BufferBlock[i]->Size = 65;
		memcpy(BM.BufferBlock[i]->memory + 64, "a", 1);
		BM.SetHead(BM.BufferBlock[i]);
	}
	//BM.BufferBlock[3]->BlockNum = 2;
	//BM.BufferBlock[3]->Filename = "1.txt";
	//BM.BufferBlock[3]->FirstDelete = 65; //为什么写成65了。。。
	//BM.BufferBlock[3]->RecordLength = 1;
	//BM.BufferBlock[3]->Size = 65;
	//memcpy(BM.BufferBlock[3]->memory + 64, "b", 1);
	//BM.SetHead(BM.BufferBlock[3]);
	BM.WriteToDisk("1.txt",BM.BufferBlock[0]);
	BM.WriteToDisk("1.txt", BM.BufferBlock[1]);
	BM.WriteToDisk("1.txt", BM.BufferBlock[2]);
	//BM.WriteToDisk("1.txt",BM.BufferBlock[3]);
	getchar();
}
*/

/*
void main()
{
	Block* T;
	T = BM.ReadToBlock("1.txt", 2);
}
*/

/*
void main()
{
	Block* B;
	B = BM.GetBlock("2.txt",2);
    B->IsLeaf = BM.IsLeaf(B);
	cout << B->IsLeaf << endl;
	getchar();
}
*/

/*
int main()
{
	int i = 0;
	if (0 == i)
	{
		BufferManager BM;
		i++;
	}
	return i;
}
*/

/*
void main()
{
	Block* B;
	BM.GetBlock("im0.txt");
	B = BM.GetBlock("im1.txt");
	B->IsWritten = true;
	BM.GetBlock("im0.txt",1);
	BM.GetBlock("im2.txt");
	BM.GetBlock("im3.txt");
	BM.GetBlock("im4.txt");
}
*/


/*void main()
{
	Block* B;
	string s;
	B = BM.GetBlock("2.txt", 2);
	BM.WriteToMemory(B, "c", 1);
	BM.WriteToMemory(B, "c", 1, 2);
	s = BM.GetRecordByNum(B, 2, 1);
	getchar();
}*/

/*
void main()
{
	Block* B;
	string s;
	int n = BM.BlockNum("test.txt");
	int m;
	for (int i = 1; i <= n; i++)
	{
		B = BM.GetBlock("test.txt", i);
		BM.SetHead(B);
		BM.WriteToDisk("test.txt",B);
	}
	B = BM.GetBlock("test.txt", 4);
	m = BM.GetRecordNum(B,30);
	s = BM.GetRecordByNum(B, 5,30);
	cout << "blocknum = " << n << "recordnum = " << m << endl;
	cout << s << endl;
	getchar();
}
*/

void main()
{
	Block* B;
	B = BM.GetBlock("test.txt",7);
	BM.WriteToMemory(B,"         9CDBFJFLIN1.111111111",30);
	BM.WriteToMemory(B, "         9CDBFJFLIN1.111111111", 30,15);
	BM.WriteToDisk("test.txt", B);
}
