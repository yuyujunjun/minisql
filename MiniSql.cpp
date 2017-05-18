// MiniSql.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include"all.h"
#include<string>
#include<iostream>
#include<vector>
using namespace std;
BufferManager BM;
Btree_node<string> *queue[100];
int index=0;
int front = 0;
/*
void Print() {
	while (front != index) {
		Btree_node<int>* temp = queue[front];
		front++;
		if (!temp->isleaf) {
			//cout << "next :" << endl;
			for (int i = 0; i <= temp->keynum; i++) {
				queue[index++] = temp->child[i];
			}
		}
		//cout << "level: " << endl;
		for (int i = 0; i < temp->keynum; i++) {
			if (temp->parent);
			//	cout << temp->parent->min << " ";
		}
	//	cout << endl;

	}
	//cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;
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
		//
		//
		//
		//cout << "level: " << endl;
		for (int i = 0; i < temp->keynum; i++) {
			//cout << temp->attr[i] << " ";
		}
		//cout << endl;

	}
	cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;
}
*/

//BufferManager BM;






//*
int main()
{
	string command;
	int status = -1;
	Interpreter inter;
	string a = "id";
	Bplus<string> bp(a, CHAR, 9);
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
	Attribute aa("a",INT, true, true, 4);
	Attribute b("b", CHAR, true, true, 9);
	Attribute c("c", FLOAT, true, true, 4);
	Attribute attr[3];
	//attr.push_back(a);

	attr[0] = aa;
	attr[1] = b;
	attr[2] = c;
	Table table("a", 3, 0, attr);
	for (int i = 0; i < table.num_of_attribute; i++) {
		cout << table.attribute[i].attr_name << endl;
	}
	string __indexname__ = "TNT";
	//string tyr = " ";
	index_create_index(table, b, &bp, __indexname__);
	cout<<query_on_index_from_file(table,b,"BBAAAAAAA", __indexname__)<<endl;
	insert_into_index(table, b, "CC", 32, __indexname__);
	cout << query_on_index_from_file(table, b, "CC", __indexname__)<<endl;
	delete_from_index(table, b, "CC", __indexname__);
	if (query_on_index_from_file(table, b, "CCCCCCCC&", __indexname__) == NULL)
		cout << " no result" << endl;
	//queue[index++] = bp.root;
	//Print1();
	char s[maxlength];
	float aaaa = -1;
//	sprintf_s(s, 12, "%-11f", aaaa);
	//cout << s << endl;
	//size_t convert;
	//convert = GetAttributeLength(CHAR, 8);
	//char tmp[10];
	//sprintf_s(tmp, "%d", convert);
	//string tmp2 = tmp;
	//string convert_type;
	//convert_type = convert_type + tmp2 + "s";
	//sprintf_s(s + 10, convert + 1, convert_type.data(), "2222");
	//cout << s;
//	cout << "s";
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

/*
void main()
{
	Block* B;
	B = BM.GetBlock("test.txt",7);
	BM.WriteToMemory(B,"         9CDBFJFLIN1.111111111",30);
	BM.WriteToMemory(B, "         9CDBFJFLIN1.111111111", 30,15);
	BM.WriteToDisk("test.txt", B);
}
*/