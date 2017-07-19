#pragma once

#include "all.h"
#include <iomanip>
using namespace std;

#define BlockSize 1024*4
#define MaxBlock 256
#define BlockHeadSize 64

bool InsertRecord(const string TableName, const int RecordLength, const vector<string> &value, char* AddInfo);

bool SelectRecord(const string TableName, Table TableStruct, int AttrNum, vector<string> AttrName);
bool SelectRecord(const string TableName, const Table TableStruct, const int AttrNum, const int SelectNum, const int ConNum, vector<Condition> condition, vector<vector<string> > &tmpRecords);
bool SelectFromIndex(const string TableName, const Table TableStruct, const int AttrNum, const int SelectNum,const int ConNum, vector<Condition> condition, vector<int> condiNum, vector<vector<string> > &tmpRecords);

bool DeleteRecord(const string TableName, const Table TableStruct, const int AttrNum, const int SelectNum, vector<int> attriSelected, const vector<Condition> condition);
bool DeleteRecords(const string TableName, Table TableStruct);

