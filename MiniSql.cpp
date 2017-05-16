// MiniSql.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include"all.h"
#include<string>
#include<iostream>
#include<vector>
using namespace std;
BufferManager BM;
Btree_node<int> *queue[100];
int index=0;
int front = 0;

void Print() {
	while (front!=index) {
		Btree_node<int>* temp = queue[front];
		front++;
		if (!temp->isleaf) {
			//cout << "next :" << endl;
			for (int i = 0; i <= temp->keynum; i++) {
				queue[index++] = temp->child[i];
			}
		}
		cout << "level: " << endl;
		for (int i = 0; i < temp->keynum; i++) {
			if(temp->parent)
			cout << temp->parent->min << " ";
		}
		cout << endl;

	}
	cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;
}
void Print1() {
	while (front != index) {
		Btree_node<int> * temp = queue[front];
		front++;
		if (!temp->isleaf) {
			//cout << "next :" << endl;
			for (int i = 0; i <= temp->keynum; i++) {
				queue[index++] = temp->child[i];
			}
		}
		cout << "level: " << endl;
		for (int i = 0; i < temp->keynum; i++) {
			cout << temp->attr[i]<<" ";
		}
		cout << endl;

	}
	cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;
}


//BufferManager BM;






//*
int main()
{
	string command;
	int status=-1;
	Interpreter inter;
	string a = "id";
	Bplus<int> bp(a, 1, 4);
	/*//queue[index++] = bp.root;
	bp.insert_into_btree("9",20);
	//Print();
	//queue[index++] = bp.root;
	bp.insert_into_btree("3", 20);
	//queue[index++] = bp.root;
	Print();
	bp.insert_into_btree("2", 20);
	//queue[index++] = bp.root;
	Print();
	bp.insert_into_btree("4", 20);
	//queue[index++] = bp.root;
	Print();
	bp.insert_into_btree("8", 20);
	//queue[index++] = bp.root;
	Print();
	
	bp.insert_into_btree("6", 20);
	//queue[index++] = bp.root;
	Print();
	bp.insert_into_btree("7", 20);
	//queue[index++] = bp.root;
	
	Print();
	bp.insert_into_btree("5", 20);
	//queue[index++] = bp.root;
	Print();
	bp.insert_into_btree("1", 20);
	//queue[index++] = bp.root;
	Print();
	queue[index++] = bp.root;
	Print1();
	queue[index++] = bp.root;

	Print();
	bp.insert_into_btree("10", 20);
	//queue[index++] = bp.root;
	Print();

	bp.insert_into_btree("11", 25);
	//queue[index++] = bp.root;
	Print();
	bp.delete_from_btree("10");
	//queue[index++] = bp.root;
	Print();

	bp.insert_into_btree("12", 20);	
	bp.insert_into_btree("15", 20);
	bp.insert_into_btree("13", 20);
	
	bp.insert_into_btree("14", 20);

	//bp.delete_from_btree(2);
	bp.insert_into_btree("16", 20);
	bp.insert_into_btree("17", 20);
	
	bp.insert_into_btree("18", 20);

	bp.insert_into_btree("19", 20);
	bp.insert_into_btree("20", 20);
	bp.insert_into_btree("22", 20);
	bp.insert_into_btree("21", 20);
	bp.insert_into_btree("23", 20);
	bp.insert_into_btree("24", 20); 
	queue[index++] = bp.root;
	Print1();
	//bp.insert_into_btree(7, 20);
	bp.delete_from_btree("1");
	bp.delete_from_btree("3");
	bp.delete_from_btree("4");
	bp.delete_from_btree("7");
	//cout << bp.query_on_btree(5);
	bp.delete_from_btree("5");
	bp.delete_from_btree("16");
	bp.delete_from_btree("6");
	bp.delete_from_btree("15");
	bp.delete_from_btree("17");
	bp.delete_from_btree("14");
	bp.delete_from_btree("8");
	bp.delete_from_btree("13");
	bp.delete_from_btree("9");
	bp.delete_from_btree("12");

	bp.delete_from_btree("18");
	bp.delete_from_btree("19");
	bp.delete_from_btree("20");
	bp.delete_from_btree("22");
	bp.delete_from_btree("21");
	bp.delete_from_btree("23");
	bp.delete_from_btree("24");
	bp.delete_from_btree("2");
	bp.insert_into_btree("16", 20);
	bp.insert_into_btree("17", 20);

	bp.insert_into_btree("18", 22);

	bp.insert_into_btree("19", 20);
	bp.insert_into_btree("20", 20);
	cout << "result: " << bp.insert_into_btree("18", 23) << endl;
	queue[index++] = bp.root;

	Print();
	queue[index++] = bp.root;
	Print1();*/
	Attribute aa("a",INT,true,true,4);
	Attribute b("b", CHAR, true, true, 9);
	Attribute c("c", FLOAT, true, true, 4);
	Attribute attr[3];
	//attr.push_back(a);

		attr[0] = aa;
		attr[1] = b;
		attr[2] = c;
	Table table("a",3,0,attr);
	for (int i = 0; i < table.num_of_attribute; i++) {
		cout<<table.attribute[i].attr_name<<endl;
	}
	index_create_index(table,aa,1,&bp);
	queue[index++] = bp.root;
	Print1(); 
	//create_index();
	//bp.Print_leaf();
/*	b\
	while (true) {
		cout << ENTER;
		getline(cin, command, ';');
		status = inter.interpreter(command);
		if (status == quit)break;
		
	}**/
	//cout << bp.query_on_btree("18")<<" "<<bp.query_on_btree("11");
	return 0;
}
//*/

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