#include"stdafx.h"
#include"all.h"
#include<string>
#include<iostream>
#include<vector>

using namespace std;
/*
API api;
BufferManager BM;
Btree_node<string> *queue[100];
int index = 0;
int front = 0;

int main()
{
/*	vector<Attribute> AttriArray;
	string TableName = "Mini_Library";
	Attribute tmpAttr1;
	tmpAttr1.attr_name = "Name";
	tmpAttr1.attr_len = 15;
	tmpAttr1.attr_type = CHAR;
	tmpAttr1.NOTNULL = true;
	tmpAttr1.UNIQUE = false;
	AttriArray.push_back(tmpAttr1);
	Attribute tmpAttr2;
	tmpAttr2.attr_name = "Storage";
	tmpAttr2.attr_len = 10;
	tmpAttr2.attr_type = INT;
	tmpAttr2.NOTNULL = true;
	tmpAttr2.UNIQUE = true;
	AttriArray.push_back(tmpAttr2);
	Attribute tmpAttr3;
	tmpAttr3.attr_name = "Price";
	tmpAttr3.attr_len = 11;
	tmpAttr3.attr_type = FLOAT;
	tmpAttr3.NOTNULL = true;
	tmpAttr3.UNIQUE = true;
	AttriArray.push_back(tmpAttr3);

	api.CreateTableAPI(TableName, AttriArray, 0);

	vector<string> value;
	//string TableName = "Mini_Library";
	value.push_back("SpicyChicken");
	value.push_back("23");
	value.push_back("2.1");
	api.InsertRecordAPI(TableName, value);
	api.CreateIndexAPI("Price_Index", "Price", TableName);
	//api.CreateIndexAPI("Price_Index", "Price", TableName);

	value.clear();
	value.push_back("Spicyyy");
	value.push_back("13123");
	value.push_back("4.143");
	api.InsertRecordAPI(TableName, value);
	value.clear();
	value.push_back("Spicyyyccc");
	value.push_back("161234");
	value.push_back("1.1433");
	api.InsertRecordAPI(TableName, value);
	value.clear();
	value.push_back("Spicy");
	value.push_back("12");
	value.push_back("0.14");
	api.InsertRecordAPI(TableName, value);
	vector<Condition> condition;
	//Condition b("Storage", "25", LESS);
	//condition.push_back(b);
	Condition b("Price", "2.1", MORE_EQUAL);
	condition.push_back(b);

	//Condition a("Name", "Spicy", EQUAL);
	//condition.push_back(a);
	//api.DeleteRecordAPI(TableName, condition);

	vector<string> AttrSelected;
	//AttrSelected.push_back("");
	//api.SelectRecordAPI(TableName, AttrSelected);
	//vector<Condition> condition_s;
	//Condition a("Storage", "12", MORE);
	//condition.push_back(a);
	api.SelectRecordAPI(TableName, condition, AttrSelected);

	system("pause");*/




/*	Interpreter a;
	string command;

	while (true) {
		int q;
		getline(cin, command, ';');
		q=a.interpreter(command);
		if (q == quit)cout << QUIT << endl;
		else if (q == 1) {
			ifstream inter;
			inter.open(a.file);
			//getline(inter, command, ";");
		}
	}
	return 0;

}*/
API api;
BufferManager BM;
Btree_node<string> *queue[100];
int index = 0;
int front = 0;

int main()
{
	vector<Attribute> AttriArray;
	string TableName = "Mini_Library";
	/*Attribute tmpAttr1;
	tmpAttr1.attr_name = "Name";
	tmpAttr1.attr_len = 50;
	tmpAttr1.attr_type = CHAR;
	tmpAttr1.NOTNULL = true;
	tmpAttr1.UNIQUE = false;
	AttriArray.push_back(tmpAttr1);
	Attribute tmpAttr2;
	tmpAttr2.attr_name = "Storage";
	tmpAttr2.attr_len = 10;
	tmpAttr2.attr_type = INT;
	tmpAttr2.NOTNULL = true;
	tmpAttr2.UNIQUE = true;
	AttriArray.push_back(tmpAttr2);
	Attribute tmpAttr3;
	tmpAttr3.attr_name = "Price";
	tmpAttr3.attr_len = 11;
	tmpAttr3.attr_type = FLOAT;
	tmpAttr3.NOTNULL = true;
	tmpAttr3.UNIQUE = false;
	AttriArray.push_back(tmpAttr3);

	api.CreateTableAPI(TableName, AttriArray, 0);
	//string TableName = "Mini_Library";
	//value.push_back("SpicyChicken");
	//value.push_back("23");
	//value.push_back("2.1");
	//api.InsertRecordAPI(TableName, value);
	//api.CreateIndexAPI("Price_Index", "Price", TableName);

	/*value.clear();
	value.push_back("Spicyyy");
	value.push_back("13123");
	value.push_back("4.143");
	api.InsertRecordAPI(TableName, value);
	value.clear();
	value.push_back("Spicyyyccc");
	value.push_back("161234");
	value.push_back("1.1433");
	api.InsertRecordAPI(TableName, value);
	value.clear();
	value.push_back("Spicy");
	value.push_back("12");
	value.push_back("0.14");
	api.InsertRecordAPI(TableName, value);
	vector<Condition> condition;
	//Condition b("Storage", "25", LESS);
	//condition.push_back(b);
    Condition b("Price", "2.1", LESS_EQUAL);
	condition.push_back(b);

	//Condition a("Name", "Spicy", EQUAL);
	//condition.push_back(a);
	//api.DeleteRecordAPI(TableName, condition);*/

	vector<string> AttrSelected;
	//AttrSelected.push_back("");
	//api.SelectRecordAPI(TableName, AttrSelected);
	//vector<Condition> condition_s;
	vector<Condition> condition;
	Condition a("Storage", "12", MORE);
	condition.push_back(a);
	api.SelectRecordAPI(TableName,condition, AttrSelected);
	
	/*for (int i = 1; i <= 100; i++) {
		vector<string> value;
		if (i % 5 == 0)
			value.push_back("AAAA");
		else
			value.push_back("BBBB");
		stringstream s;
		s << i;
		string ss = s.str();
		value.push_back(ss);
		value.push_back("2.33");
		api.InsertRecordAPI(TableName, value);
	}
	api.CreateIndexAPI("Storage_Index", "Storage", TableName);*/
	system("pause");
	return 0;
}