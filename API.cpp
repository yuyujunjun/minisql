#include"stdafx.h"
#include "API.h"
#include <string>

using namespace std;
extern BufferManager BM;

//根据interpreter提供信息，创建表
void API::CreateTableAPI(const string TableName, const vector<Attribute> AttriArray, const int PrimKey)
{
	if (IsTableExist(TableName)){
		cout << "The table already exists." << endl;
	}
	else {
		int AttriNum = AttriArray.size();
		Attribute *tmp = new Attribute[AttriNum];
		for (int i = 0; i < AttriNum; i++) {
			tmp[i].attr_len = AttriArray[i].attr_len;
			tmp[i].attr_name = AttriArray[i].attr_name;
			tmp[i].attr_type = AttriArray[i].attr_type;
			tmp[i].NOTNULL = AttriArray[i].NOTNULL;
			tmp[i].UNIQUE = AttriArray[i].UNIQUE;
		}
		Table NewTable = Table(TableName, AttriNum, PrimKey, tmp);
		CreateTableCatalog(NewTable, TableName);
		if (!IsTableExist(TableName))
			cout << "Error occurred." << endl;
		else
			cout << "Create table " << TableName << " successfully." << endl;
		delete[]tmp;
	}

}

//根据interpreter提供信息，删除表
void API::DropTableAPI(const string TableName)
{
	if (!IsTableExist(TableName)) {
		cout << "The table doesn't exist." << endl;
	}
	else {
		DropTableCatalog(TableName);
		if (IsTableExist(TableName))
			cout << "Error occurred" << endl;
		else
			cout << "Drop table " << TableName << " successfully." << endl;
	}
}

//根据interpreter提供信息，建立索引
void API::CreateIndexAPI(string IndexName, const string AttriName, const string TableName)
{
	if (IsIndexExist(IndexName, TableName)) {
		cout << "The index already exists." << endl;
	}
	else {
		Table TableStruct = FindTableCatalog(TableName);
		for (int i = 0; i < TableStruct.num_of_attribute; i++) {
			if (AttriName == TableStruct.attribute[i].attr_name) {
				if (TableStruct.attribute[i].UNIQUE) {
					Attribute attri_name(TableStruct.attribute[i].attr_name, TableStruct.attribute[i].attr_type, TableStruct.attribute[i].NOTNULL, TableStruct.attribute[i].UNIQUE, TableStruct.attribute[i].attr_len);
					CreateIndexCatalog(attri_name, IndexName, TableName);
					if (TableStruct.attribute[i].attr_type == CHAR) {
						Bplus<string> bp(IndexName, CHAR, TableStruct.attribute[i].attr_len);
						index_create_index(TableStruct, attri_name, &bp, IndexName);
					}
					else if (TableStruct.attribute[i].attr_type == FLOAT) {
						Bplus<float> bp(IndexName, FLOAT, TableStruct.attribute[i].attr_len);
						index_create_index(TableStruct, attri_name, &bp, IndexName);
					}
					else {
						Bplus<int> bp(IndexName, INT, TableStruct.attribute[i].attr_len);
						index_create_index(TableStruct, attri_name, &bp, IndexName);
					}
					break;
				}
				else {
					cout << "The value of attribute " << AttriName << " is not UNIQUE." << endl;
					return;
				}
			}
		}
		if (!IsIndexExist(IndexName, TableName))
			cout << "Error occurred." << endl;
		else
			cout << "Create index " << IndexName << " successfully." << endl;
	}
}

//根据interpreter提供信息，删除索引
void API::DropIndexAPI(const string IndexName, const string TableName)
{
	string index_name = TableName + IndexName + INDEX;
	if (!IsIndexExist(IndexName, TableName)) {
		cout << "The index already exists." << endl;
	}
	else {
		DropIndexCatalog(IndexName, TableName);
		if (IsIndexExist(IndexName, TableName))
			cout << "Error occurred" << endl;
		else
			cout << "Drop index " << IndexName << " successfully." << endl;
	}
}

//根据interpreter提供信息， 查询记录 
void API::SelectRecordAPI(const string TableName, vector<string> AttrName)
{
	if (!IsTableExist(TableName)) {
		cout << "The table doesn't exist." << endl;
		return;
	}
	else {
		cout << TableName << endl;
		Table TableStruct = FindTableCatalog(TableName);
		int AttrNum = TableStruct.num_of_attribute;
		if (!AttrNum)
			return;
		if (AttrName.size() == 0) {
			for (int i = 0; i < AttrNum; i++) {
				cout << setw(10) << TableStruct.attribute[i].attr_name;
			}
			cout << endl;
		}
		else {
			for (int i = 0; i < AttrName.size(); i++) {
				cout << setw(10) << AttrName[i];
			}
			cout << endl;
		}
		if (!SelectRecord(TableName, TableStruct, AttrNum, AttrName))
			cout << "Error occurred." << endl;
		else {
			cout << "Select records from " << TableName << " successfully." << endl;
		}
	}
}

void API::SelectRecordAPI(const string TableName, vector<Condition> condition, const vector<string> AttrName)
{
	if (!IsTableExist(TableName)) {
		cout << "The table doesn't exist." << endl;
		return;
	}
	else {
		cout << TableName << endl;
		Table TableStruct = FindTableCatalog(TableName);
		int AttrNum = TableStruct.num_of_attribute;
		if (!AttrNum)
			return;
		for (int i = 0; i < AttrName.size(); i++) {
			int flag = 0;
			for (int j = 0; j < AttrNum; j++) {
				if (strcmp(AttrName[i].c_str(), TableStruct.attribute[j].attr_name.c_str()) == 0) {
					flag = 1;
					break;
				}
			}
			if (!flag) {
				cout << AttrName[i] << " isn't an attribute in table " << TableName << "." << endl;
				return;
			}
		}

		vector<int> CondiNum;
		for (int i = 0; i < condition.size(); i++) {
			int flag = 0;
			for (int j = 0; j < TableStruct.num_of_attribute; j++) {
				if (condition[i].Left == TableStruct.attribute[j].attr_name) {
					flag = 1;
					CondiNum.push_back(j + 1);
					if (condition[i].Right.size() > TableStruct.attribute[j].attr_len) {
						cout << "The value of Condition " << condition[i].Left << " is over space." << endl;
						return;
					}
					else {
						if (TableStruct.attribute[j].attr_type == CHAR) {
							int diff = TableStruct.attribute[j].attr_len - condition[i].Right.size();
							condition[i].Right.append(diff, '*');
						}
					}
					break;
				}

			}
			if(!flag){
				cout << "Condition " << condition[i].Left << " isn't compatible with any attribute in Table " << TableName << "." << endl;
				return;
			}
		}

		if (AttrName.size() == 0) {
			for (int i = 0; i < AttrNum; i++) {
				cout << setw(10) << TableStruct.attribute[i].attr_name;
			}
			cout << endl;
		}
		else {
			for (int i = 0; i < AttrName.size(); i++) {
				cout << setw(10) << AttrName[i];
			}
			cout << endl;
		}
		
		vector<vector<string> > tmpRecords;
		for (int i = 0; i < condition.size(); i++) {
			string IndexName = GetAttributeOfIndexByName(TableName, condition[i].Left);
			if (IndexName == "") {
				if (!SelectRecord(TableName, TableStruct, AttrNum, condition.size(),i+1, condition, tmpRecords))
					cout << "Error occurred." << endl;
			}
			else {
				if (!SelectFromIndex(TableName, TableStruct, AttrNum, condition.size(), i + 1, condition, CondiNum, tmpRecords)) {
					cout << "Error occurred." << endl;
				}
			}
		}

		if (AttrName.size() == 0) {
			for (int i = 0; i < tmpRecords.size(); i++) {
				if (strcmp(tmpRecords[i][0].c_str(), "true") == 0) {
					for (int j = 1; j <= AttrNum; j++) {
						char *value = new char[TableStruct.attribute[j - 1].attr_len + 1];
						char *dest = new char[TableStruct.attribute[j - 1].attr_len + 1];
						strncpy_s(value, TableStruct.attribute[j - 1].attr_len + 1, tmpRecords[i][j].c_str(), TableStruct.attribute[j - 1].attr_len);
						value[TableStruct.attribute[j - 1].attr_len] = '\0';
						//tmpRecords[i][j].copy(value, tmpRecords[i][j].size(), 0);
						int n = 0;
						for (; n < TableStruct.attribute[j-1].attr_len; n++) {
							if ( value[n]== '*')
								break;
						}
						strncpy_s(dest, TableStruct.attribute[j - 1].attr_len + 1, value, n);
						dest[n] = '\0';
						cout << setw(10) << dest;
						delete[]value;
						delete[]dest;
					}
				}
				cout << endl;
			}
		}
		else {
			for (int i = 0; i < tmpRecords.size(); i++) {
				if (strcmp(tmpRecords[i][0].c_str(), "true") == 0) {
					for (int j = 0; j < AttrName.size(); j++) {
						for (int k = 0; k < AttrNum; k++) {
							if (strcmp(TableStruct.attribute[k].attr_name.c_str(), AttrName[j].c_str()) == 0) {
								char *value = new char[TableStruct.attribute[j - 1].attr_len + 1];
								char *dest = new char[TableStruct.attribute[j - 1].attr_len + 1];
								strncpy_s(value, TableStruct.attribute[j - 1].attr_len + 1, tmpRecords[i][k].c_str(), TableStruct.attribute[j - 1].attr_len);
								value[tmpRecords[i][k].size()] = '\0';
								//tmpRecords[i][k].copy(value, tmpRecords[i][k].size(), 0);
								int n = 0;
								for (; n < TableStruct.attribute[k].attr_len; n++) {
									if (value[n] == '*')
										break;
								}
								strncpy_s(dest, TableStruct.attribute[k].attr_len + 1, value, n);
								dest[n] = '\0';
								cout << setw(10) << dest;
								delete[]dest;delete[]value;
							}
						}
					}
				}
				cout << endl;
			}
		}
		cout << "Select records from " << TableName << " successfully." << endl;
	}
}

//根据interpreter提供信息，插入记录
void API::InsertRecordAPI(const string TableName, vector<string> Value)
{
	bool judge = IsTableExist(TableName);
	if (!judge) {
		cout << "The table " << TableName << " doesn't exist." << endl;
		return;
	}
	int value_size = Value.size();
	Table table_struct = FindTableCatalog(TableName);
	if (value_size != table_struct.num_of_attribute) {
		cout << "The number of attribute is incompatible." << endl;
		return;
	}
	int attri_size = 0;
	int i = 0;
	for (; i < table_struct.num_of_attribute; i++) {
		attri_size += table_struct.attribute[i].attr_len;
	}
	int BlockNum = BM.BlockNum(TableName + RECORD);
	if (BlockNum) {
		for (int j = 0; j < table_struct.num_of_attribute; j++) {
			if (table_struct.attribute[j].UNIQUE) {
				int offset = 0;
				for (int i = 0; i < j; i++)
					offset += table_struct.attribute[i].attr_len;
				for (int i = 1; i <= BlockNum; i++) {
					Block *tmp = BM.GetBlock(TableName + RECORD, i);
					char* value = tmp->memory + BlockHeadSize + offset;
					int RecordNum = BM.GetRecordNum(tmp, tmp->RecordLength);
					for (int k = 0; k < RecordNum; k++) {
						if (Value[j].size() > table_struct.attribute[j].attr_len) {
							cout << "The value of " << table_struct.attribute[j].attr_name << " is over space." << endl;
							return;
						}
						else {
							int diff = table_struct.attribute[j].attr_len - Value[j].size();
							Value[j].append(diff, '*');
						}
						char *attr_value = new char[table_struct.attribute[j].attr_len + 2];
						strncpy(attr_value, value, table_struct.attribute[j].attr_len);
						attr_value[table_struct.attribute[j].attr_len] = '\0';
						if (strcmp(attr_value, Value[j].c_str()) == 0) {
							cout << "Duplicate value of the attribute " << table_struct.attribute[j].attr_name << " on table " << TableName << "." << endl;
							return;
						}
						delete[] attr_value;
						value += tmp->RecordLength;
					}
				}
			}
		}
	}
	char *add_info = new char[attri_size*2];
	for (int i = 0; i < table_struct.num_of_attribute; i++) {
		if (Value[i].size() > table_struct.attribute[i].attr_len) {
			cout << "The value of " << table_struct.attribute[i].attr_name << " is over space." << endl;
			return;
		}
		else {
			if (Value[i] == "NULL") {
				if (table_struct.attribute[i].NOTNULL == 1) {
					cout << "Attribute " << table_struct.attribute[i].attr_name << " cannot be NULL." << endl;
					return;
				}
			}
			int diff = table_struct.attribute[i].attr_len - Value[i].size();
			Value[i].append(diff, '*');
		}
		Value[i].copy(add_info, Value[i].size(), 0);
		add_info += Value[i].size();
	}
	*add_info = '\0';
	add_info -= attri_size;
	for (int i = 0; i < attri_size; i++)
		cout << add_info[i];
	cout << endl;

	if (!InsertRecord(TableName, attri_size, Value, add_info)) {
		cout << "Error occurred." << endl;
	}
	else {
		cout << "The record is inserted into " << TableName << " successfully." << endl;
	}
	delete[]add_info;
	return;
}

//根据interpreter提供信息，删除记录
void API::DeleteRecordAPI(const string TableName)
{
	if (!IsTableExist(TableName)) {
		cout << "The table doesn't exist" << endl;
		return;
	}
	else {
		Table TableStruct = FindTableCatalog(TableName);
		if (!DeleteRecords(TableName, TableStruct))
			cout << "Error occurred." << endl;
		else
			cout << "Delete all the records from table " << TableName << " successfully." << endl;
	}
}

void API::DeleteRecordAPI(const string TableName, const vector<Condition> condition)
{
	if (!IsTableExist(TableName)) {
		cout << "The table doesn't exist" << endl;
		return;
	}
	else {
		Table TableStruct = FindTableCatalog(TableName);
		int AttrNum = TableStruct.num_of_attribute;
		int SelectNum = condition.size();

		vector<int> attriSelected(SelectNum); //存储条件中属性所对应的位置，即第几个属性

		for (int i = 0; i < SelectNum; i++) {
			int flag = 0;
			for (int j = 1; j <= AttrNum; j++) {
				if (strcmp(TableStruct.attribute[j-1].attr_name.c_str(), condition[i].Left.c_str()) == 0) {
					attriSelected[i] = j;
					flag = 1;
				}
			}
			if (!flag) { //select属性中包含不存在于该table的属性
				cout << "The value of attribute isn't compatible with the table." << endl;
				return;
			}
		}
		if (!DeleteRecord(TableName, TableStruct, AttrNum, SelectNum, attriSelected, condition)) {
			cout << "Error occurred." << endl;
		}
		else {
			cout << "Delete records required from table " << TableName << " successfully." << endl;
		}
	}
}