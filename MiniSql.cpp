// MiniSql.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"all.h"
#include<string>
#include<iostream>
#include"Bplus.h"

using namespace std;
Btree_node<string> *queue[100];
int index=0;
int front = 0;

void Print() {
	while (front!=index) {
		Btree_node<string>* temp = queue[front];
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
		Btree_node<string> * temp = queue[front];
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

int main()
{
	string command;
	int status=-1;
	Interpreter inter;
	string a = "id";
	Bplus<string> bp(a,1,4);
	//queue[index++] = bp.root;
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
	Print1();
	//bp.Print_leaf();
/*	b\
	while (true) {
		cout << ENTER;
		getline(cin, command, ';');
		status = inter.interpreter(command);
		if (status == quit)break;
		
	}**/
	cout << bp.query_on_btree("18")<<" "<<bp.query_on_btree("11");
	return 0;
}

