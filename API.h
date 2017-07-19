#pragma once

#include "all.h"
#include <stdio.h>

using namespace std;

class API {
public:
	API() {};
	~API() {};

	void CreateTableAPI(const string TableName, const vector<Attribute> AttriArray, const int PrimKey);
	void DropTableAPI(const string TableName);

	void CreateIndexAPI(string IndexName, const string AttriName, const string TableName);
	void DropIndexAPI(const string IndexName, const string TableName);

	void SelectRecordAPI(const string TableName, const vector<string> AttrName);
	void SelectRecordAPI(const string TableName, vector<Condition> condition, const vector<string> AttrName);

	void InsertRecordAPI(const string TableName, vector<string> Value);

	void DeleteRecordAPI(const string TableName);
	void DeleteRecordAPI(const string TableName, const vector<Condition> condition);
};