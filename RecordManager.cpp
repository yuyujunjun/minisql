#include"stdafx.h"
#include "RecordManager.h"

using namespace std;

extern BufferManager BM;

bool comparison_s(string left, int op, string right) {
	if (op == LESS) {
		if (strcmp(left.c_str(), right.c_str()) < 0) {
			cout << strcmp(left.c_str(), right.c_str()) << endl;
			return true;
		}
		else
			return false;
	}
	else if (op == MORE) {
		if (strcmp(left.c_str(), right.c_str()) > 0)
			return true;
		else
			return false;
	}
	else if (op == EQUAL) {
		if (strcmp(left.c_str(), right.c_str()) == 0)
			return true;
		else
			return false;
	}
	else if (op == MORE_EQUAL) {
		if (strcmp(left.c_str(), right.c_str()) >= 0)
			return true;
		else
			return false;
	}
	else if (op == LESS_EQUAL) {
		if (strcmp(left.c_str(), right.c_str()) <= 0)
			return true;
		else
			return false;
	}
	else if (op == NOT_EQUAL) {
		if (strcmp(left.c_str(), right.c_str()) != 0)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool comparison_i(int left, int op, int right) {
	if (op == LESS) {
		if (left < right)
			return true;
		else
			return false;
	}
	else if (op == MORE) {
		if (left > right)
			return true;
		else
			return false;
	}
	else if (op == EQUAL) {
		if (left == right)
			return true;
		else
			return false;
	}
	else if (op == MORE_EQUAL) {
		if(left >= right)
			return true;
		else
			return false;
	}
	else if (op == LESS_EQUAL) {
		if (left <= right)
			return true;
		else
			return false;
	}
	else if (op == NOT_EQUAL) {
		if (left != right)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool comparison_f(float left, int op, float right) {
	if (op == LESS) {
		if (left < right)
			return true;
		else
			false;
	}
	else if (op == MORE) {
		if (left > right)
			return true;
		else
			return false;
	}
	else if (op == EQUAL) {
		if (left == right)
			return true;
		else
			return false;
	}
	else if (op == MORE_EQUAL) {
		if (left >= right)
			return true;
		else
			return false;
	}
	else if (op == LESS_EQUAL) {
		if (left <= right)
			return true;
		else
			return false;
	}
	else if (op == NOT_EQUAL) {
		if (left != right)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool InsertRecord(const string TableName, const int RecordLength, const vector<string> &value, char* AddInfo)
{
	int BlockNum = BM.BlockNum(TableName + RECORD);

	Block *tail;
	if (!BlockNum) {
		tail = BM.GetBlock(TableName + RECORD);
	}
	else {
		tail = BM.GetBlock(TableName + RECORD, BlockNum);
	}
		
	int offset = 0;
	if (!BM.IsFull(tail, RecordLength)) {
		BM.WriteToMemory(tail, AddInfo, RecordLength);
		cout << "Write to memory successfully." << endl;
		BM.WriteToDisk(TableName + RECORD, tail);
		cout << "Write to disk successfully." << endl;
	}
	else{
		Block *NewBlock = BM.GetBlock(TableName + RECORD);
		if (!NewBlock)
			return false;
		BM.WriteToMemory(NewBlock, AddInfo, RecordLength);
		cout << "Write to memory successfully." << endl;
		BM.WriteToDisk(TableName + RECORD, NewBlock);
		cout << "Write to disk successfully." << endl;
	}
	Table TableStruct = FindTableCatalog(TableName);
	BlockNum = BM.BlockNum(TableName + RECORD);
	for (int i = 0; i < TableStruct.num_of_attribute; i++) {
		if (TableStruct.attribute[i].UNIQUE) {
			string IndexName = GetAttributeOfIndexByName(TableName, TableStruct.attribute[i].attr_name);
			if (IndexName == "")
				continue;
			bool judge = IsIndexExist(IndexName, TableName);
			if (judge) {
				if (TableStruct.attribute[i].attr_type == CHAR) {
					if (!insert_into_index(TableStruct, TableStruct.attribute[i], value[i], BlockNum, IndexName)) {
						cout << "Error occurred." << endl;
						return false;
					}
				}
				else if (TableStruct.attribute[i].attr_type == FLOAT) {
					float key = atof(value[i].c_str());
					if (!insert_into_index(TableStruct, TableStruct.attribute[i], key, BlockNum, IndexName)) {
						cout << "Error occured." << endl;
						return false;
					}
				}
				else {
					int key = atoi(value[i].c_str());
					if (!insert_into_index(TableStruct, TableStruct.attribute[i], key, BlockNum, IndexName)) {
						cout << "Error occured." << endl;
						return false;
					}
				}
			}
		}
	}
	return true;
}

bool SelectRecord(const string TableName, Table TableStruct, int AttrNum, vector<string> AttrName) 
{
	int BlockNum = BM.BlockNum(TableName+RECORD);
	if (!BlockNum)
		return true;
	for (int i = 1; i <= BlockNum; i++) {
		Block *tmp = BM.GetBlock(TableName+RECORD, i);
		char *records1 = tmp->memory + BlockHeadSize;
		char *records2 = tmp->memory + BlockHeadSize;
		int RecordNum = BM.GetRecordNum(tmp, tmp->RecordLength);

		if (!RecordNum)
			return false;

		vector<int> RecordDel;
		int delet = tmp->FirstDelete;
		if (delet != BlockSize + 1) {
			RecordDel.push_back(delet);
			while (true) {
				char *del_record = new char[tmp->RecordLength];
				memcpy(del_record, tmp->memory + BlockHeadSize + (delet - 1)*tmp->RecordLength, tmp->RecordLength);
				if (*del_record == NULL)
					break;
				else {
					sscanf_s(del_record, "%d", &delet);
					RecordDel.push_back(delet);
				}
				delete[]del_record;
			}
		}

		for (int j = 1; j <= RecordNum; j++) {
			int tmpLength = 0;
			int flag = 0;
			for (int k = 0; k < RecordDel.size(); k++) {
				if (RecordDel[k] == j) {
					flag = 1;
					break;
				}
			}
			if (flag == 1)
				continue;
			if (AttrName.size() == 0) {
				for (int k = 0; k < AttrNum; k++) {
					char *value = new char[tmp->RecordLength + 1];
				    char *dest = new char[tmp->RecordLength + 1];
					memcpy(value, records1,TableStruct.attribute[k].attr_len);
					records1 += TableStruct.attribute[k].attr_len;
					int m = 0;
					for (; m < TableStruct.attribute[k].attr_len; m++) {
						if (value[m] == '*')
							break;
					}
					strncpy_s(dest, tmp->RecordLength+1, value, m);
					cout << setw(10) << dest;
					delete[]value;
					delete[]dest;
				}
			}
			else {
				for (int k = 0; k < AttrName.size(); k++) {
					char *value = new char[tmp->RecordLength + 1];
					char *dest = new char[tmp->RecordLength + 1];
					int offset = 0;
					int m = 0;
					for (; m < TableStruct.num_of_attribute; m++) {
						if (TableStruct.attribute[m].attr_name != AttrName[k]) {
							offset += TableStruct.attribute[m].attr_len;
						}
						else
							break;
					}
					memcpy(value, records1 + offset,TableStruct.attribute[m].attr_len);
					int n = 0;
					for (; n < TableStruct.attribute[m].attr_len; n++) {
						if (value[n] == '*')
							break;
					}
					strncpy_s(dest,tmp->RecordLength + 1, value, n);
					cout << setw(10) << dest;
					delete[]value;
					delete[]dest;
				}
			}
			cout << endl;
			records2 += tmp->RecordLength;
			records1 = records2;
		}
	}
	return true;
}

bool SelectRecord(const string TableName, const Table TableStruct, const int AttrNum, const int SelectNum, const int ConNum, vector<Condition> condition, vector<vector<string> > &tmpRecords)
{
	vector<int> attriSelected(SelectNum);
	int BlockNum = BM.BlockNum(TableName + RECORD);
	if (!BlockNum)
		return false;

	for (int i = 0; i < SelectNum; i++) {
		for (int j = 0; j < AttrNum; j++) {
			if (strcmp(TableStruct.attribute[j].attr_name.c_str(), condition[i].Left.c_str()) == 0) {
				attriSelected[i] = j+1;
				break;
			}
		}
	}

	//用condition中的第一个条件初始化容器tmpRecords
	if (ConNum == 1) {
		for (int i = 1; i <= BlockNum; i++) {
			Block *tmp = BM.GetBlock(TableName + RECORD, i);
			char *records1 = tmp->memory + BlockHeadSize;
			char *records2 = tmp->memory + BlockHeadSize;
			int RecordNum = BM.GetRecordNum(tmp, tmp->RecordLength);
			if (!RecordNum)
				return false;

			vector<int> RecordDel;
			int delet = tmp->FirstDelete;
			if (delet != BlockSize + 1) {
				RecordDel.push_back(delet);
				while (true) {
					char *del_record = new char[tmp->RecordLength];
					memcpy(del_record, tmp->memory + BlockHeadSize + (delet - 1)*tmp->RecordLength, tmp->RecordLength);
					if (!del_record)
						break;
					else {
						sscanf_s(del_record, "%d", &delet);
						RecordDel.push_back(delet);
					}
					delete[]del_record;
				}
			}
			bool bSelected;
			for (int j = 1; j <= RecordNum; j++) {
				int offset = 0;
				int flag = 0;
				for (int k = 0; k < RecordDel.size(); k++) {
					if (RecordDel[k] == j) {
						flag = 1;
						break;
					}
				}
				if (flag == 1)
					continue;

				for (int k = 0; k < attriSelected[0]-1; k++)
					offset += TableStruct.attribute[k].attr_len;
				char *left = new char[TableStruct.attribute[attriSelected[0]-1].attr_len + 1];
				strncpy_s(left, TableStruct.attribute[attriSelected[0] - 1].attr_len + 1, records1 + offset, TableStruct.attribute[attriSelected[0] - 1].attr_len);
				left[TableStruct.attribute[attriSelected[0] - 1].attr_len] = '\0';
				char *left_ = new char[TableStruct.attribute[attriSelected[0] - 1].attr_len + 1];
				int n = 0;
				for (; n < TableStruct.attribute[attriSelected[0] - 1].attr_len; n++) {
					if (left[n] == '*')
						break;
				}
				strncpy_s(left_, TableStruct.attribute[attriSelected[0] - 1].attr_len + 1, left, n);
				left_[n] = '\0';
				if (strcmp(left_, "NULL") == 0)
					continue;
				
				bSelected = false;
				if(TableStruct.attribute[attriSelected[0]-1].attr_type == CHAR)
					bSelected = comparison_s(left, condition[0].op, condition[0].Right);
				else if (TableStruct.attribute[attriSelected[0] - 1].attr_type == INT)
					bSelected = comparison_i(atoi(left), condition[0].op, atoi(condition[0].Right.c_str()));
				else
					bSelected = comparison_f(atof(left), condition[0].op, atof(condition[0].Right.c_str()));
				if (bSelected) {
					vector<string> tmpRecord;
					tmpRecord.push_back("true"); //记录被选择标记
					for (int k = 0; k < AttrNum; k++) {
						char* value = new char[TableStruct.attribute[k].attr_len + 1];
						string s_value;
						strncpy_s(value, TableStruct.attribute[k].attr_len + 1, records1, TableStruct.attribute[k].attr_len);
						value[TableStruct.attribute[k].attr_len] = '\0';
						s_value = string(value);
						tmpRecord.push_back(s_value);
						records1 += TableStruct.attribute[k].attr_len;
						delete[]value;
					}
					tmpRecords.push_back(tmpRecord);
				}
				records2 += tmp->RecordLength;
				records1 = records2;
				delete[]left;
			}
		}
	}
	else {
		int size = tmpRecords.size();
		if (!size)
			return false;
		int i = ConNum - 1;
		bool bSelected;
		for (int j = 0; j < size; j++) {
			char *left = new char[TableStruct.attribute[attriSelected[i] - 1].attr_len + 1];
			memcpy(left, tmpRecords[j][attriSelected[i] - 1].c_str(), TableStruct.attribute[attriSelected[0] - 1].attr_len);
			char *left_ = new char[TableStruct.attribute[attriSelected[i] - 1].attr_len + 1];
			int n = 0;
			for (; n < TableStruct.attribute[attriSelected[i] - 1].attr_len; n++) {
				if (left[n] == '*')
					break;
			}
			strncpy_s(left_, sizeof(left_), left, n);
			left_[n] = '\0';
			bool bSelected = false;
			if (strcmp(left_, "NULL") == 0)
				continue;

		    bSelected = false;
			if (TableStruct.attribute[attriSelected[i] - 1].attr_type == CHAR)
				bSelected = comparison_s(tmpRecords[j][attriSelected[i] - 1], condition[i].op, condition[i].Right);
			else if (TableStruct.attribute[attriSelected[0] - 1].attr_type == INT)
			    bSelected = comparison_i(atoi(tmpRecords[j][attriSelected[i] - 1].c_str()), condition[0].op, atoi(condition[0].Right.c_str()));
			else
				bSelected = comparison_f(atof(tmpRecords[j][attriSelected[i] - 1].c_str()), condition[0].op, atof(condition[0].Right.c_str()));
			if (!bSelected) {
				if (strcmp(tmpRecords[j][0].c_str(), "true") == 0)
					tmpRecords[j][0] = "false";
			}
		}
	}
	return true;
}

bool SelectFromIndex(const string TableName, const Table TableStruct, const int AttrNum, const int SelectNum, const int ConNum, vector<Condition> condition, vector<int> condiNum, vector<vector<string> > &tmpRecords)
{
	int BlockNum = BM.BlockNum(TableName + RECORD);
	if (!BlockNum)
		return false;
	vector<int> tmpSelected;
	vector<int> curNum(BlockNum, 1);
	string IndexName = GetAttributeOfIndexByName(TableName, condition[0].Left);
	Attribute AttrIndex = GetAttributeOfIndex(IndexName, TableName);
	//用condition中的第一个条件初始化容器tmpRecords
	if (ConNum == 1) {
		int operation = condition[0].op;
		if (operation == -1)
			return false;
		else {
			if (operation == MORE_EQUAL || operation == MORE) {
				if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR) {
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, condition[0].Right, maxQwQ_s, IndexName);
				}
				else if (TableStruct.attribute[condiNum[0] - 1].attr_type == FLOAT) {
					float right = atof(condition[0].Right.c_str());
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, right, maxQwQ_f, IndexName);
				}
				else {
					int right = atoi(condition[0].Right.c_str());
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, right, maxQwQ_i, IndexName);
				}
				if (!tmpSelected.size()) {
					cout << "There is no records selected by Index " << IndexName << "." << endl;
					return false;
				}
				else {
					if (operation == MORE_EQUAL) {
						for (int i = 0; i < tmpSelected.size(); i++) {
							Block *block = BM.GetBlock(TableName+RECORD, tmpSelected[i]);
							int recordNum = BM.GetRecordNum(block, block->RecordLength);
							int j = 1;
							if (curNum[tmpSelected[i] - 1] != 1)
								j = curNum[tmpSelected[i] - 1];
							for (; j <= recordNum; j++) {
								char *record = BM.GetRecordByNum(block, j, block->RecordLength);
								int offset = 0;
								for (int k = 0; k < condiNum[0] - 1; k++)
									offset += TableStruct.attribute[k].attr_len;
								char *left = new char[TableStruct.attribute[condiNum[0] - 1].attr_len + 1];
								strncpy_s(left, TableStruct.attribute[condiNum[0] - 1].attr_len + 1, record + offset, TableStruct.attribute[condiNum[0] - 1].attr_len);
								left[TableStruct.attribute[condiNum[0] - 1].attr_len] = '\0';
								bool bSelected = false;
								if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR)
									bSelected = comparison_s(left, condition[0].op, condition[0].Right);
								else if (TableStruct.attribute[condiNum[0] - 1].attr_type == INT)
									bSelected = comparison_i(atoi(left), condition[0].op, atoi(condition[0].Right.c_str()));
								else
									bSelected = comparison_f(atof(left), condition[0].op, atof(condition[0].Right.c_str()));
								delete[]left;
								if (bSelected) {
									curNum[tmpSelected[i] - 1] = j + 1;
									vector<string> tmpRecord;
									tmpRecord.push_back("true"); //记录被选择标记
									for (int k = 0; k < AttrNum; k++) {
										char* value = new char[TableStruct.attribute[k].attr_len+1];
										string s_value;
										memcpy(value, record, TableStruct.attribute[k].attr_len);
										s_value = string(value);
										tmpRecord.push_back(s_value);
										record += TableStruct.attribute[k].attr_len;
										delete[]value;
									}
									tmpRecords.push_back(tmpRecord);
									break;
								}
							}
						}
					}
					if (operation == MORE) {
						for (int i = 1; i < tmpSelected.size(); i++) {
							Block *block = BM.GetBlock(TableName+RECORD, tmpSelected[i]);
							int recordNum = BM.GetRecordNum(block, block->RecordLength);
							int j = 1;
							if (curNum[tmpSelected[i] - 1] != 1)
								j = curNum[tmpSelected[i] - 1];
							for (; j <= recordNum; j++) {
								char *record = BM.GetRecordByNum(block, j, block->RecordLength);
								int offset = 0;
								for (int k = 0; k < condiNum[0] - 1; k++)
									offset += TableStruct.attribute[k].attr_len;
								char *left = new char[TableStruct.attribute[condiNum[0] - 1].attr_len + 1];
								strncpy_s(left, TableStruct.attribute[condiNum[0] - 1].attr_len + 1, record + offset, TableStruct.attribute[condiNum[0] - 1].attr_len);
								bool bSelected = false;
								if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR)
									bSelected = comparison_s(left, condition[0].op, condition[0].Right);
								else if (TableStruct.attribute[condiNum[0] - 1].attr_type == INT)
									bSelected = comparison_i(atoi(left), condition[0].op, atoi(condition[0].Right.c_str()));
								else
									bSelected = comparison_f(atof(left), condition[0].op, atof(condition[0].Right.c_str()));
								delete[]left;
								if (bSelected) {
									curNum[tmpSelected[i] - 1] = j + 1;
									vector<string> tmpRecord;
									tmpRecord.push_back("true"); //记录被选择标记
									for (int k = 0; k < AttrNum; k++) {
										char* value = new char[TableStruct.attribute[k].attr_len];
										string s_value;
										memcpy(value, record, TableStruct.attribute[k].attr_len);
										s_value = string(value);
										tmpRecord.push_back(s_value);
										record += TableStruct.attribute[k].attr_len;
										delete[]value;
									}
									tmpRecords.push_back(tmpRecord);
									break;
								}
							}
						}
					}
				}
			}
			else if (operation == LESS_EQUAL || operation == LESS) {
				if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR) {
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, minQAQ_s, condition[0].Right, IndexName);
				}
				else if (TableStruct.attribute[condiNum[0] - 1].attr_type == FLOAT) {
					float right = atof(condition[0].Right.c_str());
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, minQAQ_f, right, IndexName);
				}
				else {
					int right = atoi(condition[0].Right.c_str());
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, minQAQ_i, right, IndexName);
				}
				if (!tmpSelected.size()) {
					cout << "There is no records selected by Index " << IndexName << "." << endl;
					return false;
				}
				else {
					if (operation == LESS_EQUAL) {
						for (int i = 0; i < tmpSelected.size(); i++) {
							Block *block = BM.GetBlock(TableName, tmpSelected[i]);
							int recordNum = BM.GetRecordNum(block, block->RecordLength);
							int j = 1;
							if (curNum[tmpSelected[i] - 1] != 1)
								j = curNum[tmpSelected[i] - 1];
							for (; j <= recordNum; j++) {
								char *record = BM.GetRecordByNum(block, j, block->RecordLength);
								int offset = 0;
								for (int k = 0; k < condiNum[0] - 1; k++)
									offset += TableStruct.attribute[k].attr_len;
								char *left = new char[TableStruct.attribute[condiNum[0] - 1].attr_len + 1];
								strncpy_s(left, TableStruct.attribute[condiNum[0] - 1].attr_len + 1, record + offset, TableStruct.attribute[condiNum[0] - 1].attr_len);
								bool bSelected = false;
								if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR)
									bSelected = comparison_s(left, condition[0].op, condition[0].Right);
								else if (TableStruct.attribute[condiNum[0] - 1].attr_type == INT)
									bSelected = comparison_i(atoi(left), condition[0].op, atoi(condition[0].Right.c_str()));
								else
									bSelected = comparison_f(atof(left), condition[0].op, atof(condition[0].Right.c_str()));
								delete[]left;
								if (bSelected) {
									curNum[tmpSelected[i] - 1] = j + 1;
									vector<string> tmpRecord;
									tmpRecord.push_back("true"); //记录被选择标记
									for (int k = 0; k < AttrNum; k++) {
										char* value = new char[TableStruct.attribute[k].attr_len];
										string s_value;
										memcpy(value, record, TableStruct.attribute[k].attr_len);
										s_value = string(value);
										tmpRecord.push_back(s_value);
										record += TableStruct.attribute[k].attr_len;
										delete[]value;
									}
									tmpRecords.push_back(tmpRecord);
									break;
								}
							}
						}
					}
					if (operation == LESS) {
						for (int i = 1; i < tmpSelected.size(); i++) {
							Block *block = BM.GetBlock(TableName, tmpSelected[i]);
							int recordNum = BM.GetRecordNum(block, block->RecordLength);
							int j = 1;
							if (curNum[tmpSelected[i] - 1] != 1)
								j = curNum[tmpSelected[i] - 1];
							for (; j <= recordNum; j++) {
								char *record = BM.GetRecordByNum(block, j, block->RecordLength);
								int offset = 0;
								for (int k = 0; k < condiNum[0] - 1; k++)
									offset += TableStruct.attribute[k].attr_len;
								char *left = new char[TableStruct.attribute[condiNum[0] - 1].attr_len + 1];
								strncpy_s(left, TableStruct.attribute[condiNum[0] - 1].attr_len + 1, record + offset, TableStruct.attribute[condiNum[0] - 1].attr_len);
								bool bSelected = false;
								if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR)
									bSelected = comparison_s(left, condition[0].op, condition[0].Right);
								else if (TableStruct.attribute[condiNum[0] - 1].attr_type == INT)
									bSelected = comparison_i(atoi(left), condition[0].op, atoi(condition[0].Right.c_str()));
								else
									bSelected = comparison_f(atof(left), condition[0].op, atof(condition[0].Right.c_str()));
								delete[]left;
								if (bSelected) {
									curNum[tmpSelected[i] - 1] = j + 1;
									vector<string> tmpRecord;
									tmpRecord.push_back("true"); //记录被选择标记
									for (int k = 0; k < AttrNum; k++) {
										char* value = new char[TableStruct.attribute[k].attr_len];
										string s_value;
										memcpy(value, record, TableStruct.attribute[k].attr_len);
										s_value = string(value);
										tmpRecord.push_back(s_value);
										record += TableStruct.attribute[k].attr_len;
										delete[]value;
									}
									tmpRecords.push_back(tmpRecord);
									break;
								}
							}
						}
					}
				}
			}
			else if (operation == EQUAL) {
				if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR) {
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, condition[0].Right, condition[0].Right, IndexName);
				}
				else if (TableStruct.attribute[condiNum[0] - 1].attr_type == FLOAT) {
					float right = atof(condition[0].Right.c_str());
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, right, right, IndexName);
				}
				else {
					int right = atoi(condition[0].Right.c_str());
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, right, right, IndexName);
				}
				if (!tmpSelected.size()) {
					cout << "There is no records selected by Index " << IndexName << "." << endl;
					return false;
				}
				else {
					Block *block = BM.GetBlock(TableName, tmpSelected[0]);
					int recordNum = BM.GetRecordNum(block, block->RecordLength);
					for (int j = 1; j <= recordNum; j++) {
						char *record = BM.GetRecordByNum(block, j, block->RecordLength);
						int offset = 0;
						for (int k = 0; k < condiNum[0] - 1; k++)
							offset += TableStruct.attribute[k].attr_len;
						char *left = new char[TableStruct.attribute[condiNum[0] - 1].attr_len + 1];
						strncpy_s(left, TableStruct.attribute[condiNum[0] - 1].attr_len + 1, record + offset, TableStruct.attribute[condiNum[0] - 1].attr_len);
						bool bSelected = false;
						if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR)
							bSelected = comparison_s(left, condition[0].op, condition[0].Right);
						else if (TableStruct.attribute[condiNum[0] - 1].attr_type == INT)
							bSelected = comparison_i(atoi(left), condition[0].op, atoi(condition[0].Right.c_str()));
						else
							bSelected = comparison_f(atof(left), condition[0].op, atof(condition[0].Right.c_str()));
						delete[]left;
						if (bSelected) {
							vector<string> tmpRecord;
							tmpRecord.push_back("true"); //记录被选择标记
							for (int k = 0; k < AttrNum; k++) {
								char* value = new char[TableStruct.attribute[k].attr_len];
								string s_value;
								memcpy(value, record, TableStruct.attribute[k].attr_len);
								s_value = string(value);
								tmpRecord.push_back(s_value);
								record += TableStruct.attribute[k].attr_len;
								delete[]value;
							}
							tmpRecords.push_back(tmpRecord);
							break;
						}
					}
				}
			}
			else {
				if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR) {
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, condition[0].Right, condition[0].Right, IndexName);
				}
				else if (TableStruct.attribute[condiNum[0] - 1].attr_type == FLOAT) {
					float right = atof(condition[0].Right.c_str());
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, right, right, IndexName);
				}
				else {
					int right = atoi(condition[0].Right.c_str());
					tmpSelected = query_on_index_from_file(TableStruct, AttrIndex, right, right, IndexName);
				}
				if (tmpRecords.size()) {
					Block *block = BM.GetBlock(TableName, tmpSelected[0]);
					for (int i = 1; i <= BlockNum; i++) {
						Block *tmp = BM.GetBlock(TableName, i);
						int recordNum = BM.GetRecordNum(tmp, tmp->RecordLength);
						int flg = 0;
						for (int n = 0; n < tmpRecords.size(); n++) {
							if (tmpSelected[n] == i) {
								flg = 1;
								break;
							}
						}
						if (flg == 1) {
							for (int j = 1; j <= recordNum; j++) {
								char *record = BM.GetRecordByNum(tmp, j, tmp->RecordLength);
								int offset = 0;
								for (int k = 0; k < condiNum[0] - 1; k++)
									offset += TableStruct.attribute[k].attr_len;
								char *left = new char[TableStruct.attribute[condiNum[0] - 1].attr_len + 1];
								strncpy_s(left, TableStruct.attribute[condiNum[0] - 1].attr_len + 1, record + offset, TableStruct.attribute[condiNum[0] - 1].attr_len);
								bool bSelected = false;
								if (TableStruct.attribute[condiNum[0] - 1].attr_type == CHAR)
									bSelected = comparison_s(left, NOT_EQUAL, condition[0].Right);
								else if (TableStruct.attribute[condiNum[0] - 1].attr_type == INT)
									bSelected = comparison_i(atoi(left), NOT_EQUAL, atoi(condition[0].Right.c_str()));
								else
									bSelected = comparison_f(atof(left), NOT_EQUAL, atof(condition[0].Right.c_str()));
								delete[]left;
								if (bSelected) {
									vector<string> tmpRecord;
									tmpRecord.push_back("true"); //记录被选择标记
									for (int k = 0; k < AttrNum; k++) {
										char* value = new char[TableStruct.attribute[k].attr_len];
										string s_value;
										memcpy(value, record, TableStruct.attribute[k].attr_len);
										s_value = string(value);
										tmpRecord.push_back(s_value);
										record += TableStruct.attribute[k].attr_len;
										delete[]value;
									}
									tmpRecords.push_back(tmpRecord);
								}
							}
						}
						else {
							for (int j = 1; j <= recordNum; j++) {
								char *record = BM.GetRecordByNum(tmp, j, tmp->RecordLength);
								vector<string> tmpRecord;
								tmpRecord.push_back("true"); //记录被选择标记
								for (int k = 0; k < AttrNum; k++) {
									char* value = new char[TableStruct.attribute[k].attr_len];
									string s_value;
									memcpy(value, record, TableStruct.attribute[k].attr_len);
									s_value = string(value);
									tmpRecord.push_back(s_value);
									record += TableStruct.attribute[k].attr_len;
									delete[]value;
								}
								tmpRecords.push_back(tmpRecord);
							}
						}
					}
				}
				else {
					for (int i = 0; i < BlockNum; i++) {
						Block *tmp = BM.GetBlock(TableName, i);
						int recordNum = BM.GetRecordNum(tmp, tmp->RecordLength);
						for (int j = 1; j <= recordNum; j++) {
							char *record = BM.GetRecordByNum(tmp, j, tmp->RecordLength);
							vector<string> tmpRecord;
							tmpRecord.push_back("true"); //记录被选择标记
							for (int k = 0; k < AttrNum; k++) {
								char* value = new char[TableStruct.attribute[k].attr_len];
								string s_value;
								memcpy(value, record, TableStruct.attribute[k].attr_len);
								s_value = string(value);
								tmpRecord.push_back(s_value);
								record += TableStruct.attribute[k].attr_len;
								delete[]value;
							}
							tmpRecords.push_back(tmpRecord);
						}
					}
				}
			}
		}
	}
	else {
		int operation = condition[ConNum - 1].op;
		int size = tmpRecords.size();
		if (operation == -1)
			return false;
		else {
			int i = ConNum - 1;
			for (int j = 0; j < size; j++) {
				bool bSelected = false;
				if (TableStruct.attribute[condiNum[i]].attr_type == CHAR)
					bSelected = comparison_s(tmpRecords[j][condiNum[i]], condition[i].op, condition[i].Right);
				else if (TableStruct.attribute[condiNum[i]].attr_type == INT)
					bSelected = comparison_i(atoi(tmpRecords[j][condiNum[i]].c_str()), condition[i].op, atoi(condition[i].Right.c_str()));
				else
					bSelected = comparison_f(atof(tmpRecords[j][condiNum[i]].c_str()), condition[i].op, atof(condition[i].Right.c_str()));
				if (!bSelected) {
					if (strcmp(tmpRecords[j][0].c_str(), "true") == 0)
						tmpRecords[j][0] = "false";
				}
			}
		}
	}
	return true;
}

bool DeleteRecord(const string TableName, const Table TableStruct,const int AttrNum, const int SelectNum , vector<int> attriSelected, const vector<Condition> condition)
{
	int BlockNum = BM.BlockNum(TableName + RECORD);
	if (!BlockNum) {
		cout << "No records to delete." << endl;
		return false;
	}
	int flag = 0; //判断最终交集是否为空
	for (int i = 1; i <= BlockNum; i++) {
		vector<vector<string> > tmpRecords; //存储被删除记录信息，求交更新
		vector<int> bDeleted;
		vector<int> tmpRecord_num; //存储被删除记录的位置，即第几条记录
		Block *tmp = BM.GetBlock(TableName + RECORD, i);
		char *records1 = tmp->memory + BlockHeadSize;
		char *records2 = tmp->memory + BlockHeadSize;
		int RecordNum = BM.GetRecordNum(tmp, tmp->RecordLength);
		if (!RecordNum)
			break;
		vector<int> RecordDel;
		int delet = tmp->FirstDelete;
		if (delet != BlockSize + 1) {
			RecordDel.push_back(delet);
			while (true) {
				char *del_record = new char[tmp->RecordLength];
				memcpy(del_record, tmp->memory + BlockHeadSize + (delet - 1)*tmp->RecordLength, tmp->RecordLength);
				if (!del_record)
					break;
				else {
					sscanf_s(del_record, "%d", &delet);
					RecordDel.push_back(delet);
				}
				delete[]del_record;
			}
		}
		for (int j = 1; j <= RecordNum; j++) {
			int offset = 0;
			int flagg = 0;
			for (int k = 0; k < RecordDel.size(); k++) {
				if (RecordDel[k] == j) {
					flagg = 1;
					break;
				}
			}
			if (flagg == 1)
				continue;
			for (int k = 0; k < attriSelected[0]-1; k++)
				offset += TableStruct.attribute[k].attr_len;
			char *left = new char[tmp->RecordLength];
			char *left_ = new char[tmp->RecordLength];
			memcpy(left, records1 + offset, TableStruct.attribute[attriSelected[0]-1].attr_len);
			int m = 0;
			for (; m < TableStruct.attribute[attriSelected[0]-1].attr_len; m++) {
				if (left[m] == '*')
					break;
			}
			left_[m] = '\0';
			strncpy_s(left_, tmp->RecordLength, left, m);
			if (strcmp(left_, "NULL") == 0)
				continue;
			
			bool bSelected = false;
			if (TableStruct.attribute[attriSelected[0] - 1].attr_type == CHAR)
				bSelected = comparison_s(left_, condition[0].op, condition[0].Right);
			else if (TableStruct.attribute[attriSelected[0] - 1].attr_type == INT)
				bSelected = comparison_i(atoi(left_), condition[0].op, atoi(condition[0].Right.c_str()));
			else
				bSelected = comparison_f(atof(left_), condition[0].op, atof(condition[0].Right.c_str()));
			if (bSelected) {
				bDeleted.push_back(1);
				tmpRecord_num.push_back(j);
				vector<string> tmpRecord;
				for (int k = 0; k < AttrNum; k++) {
					char* value = new char[tmp->RecordLength];
					memcpy(value, records1, TableStruct.attribute[k].attr_len);
					string s_value = string(value);
					tmpRecord.push_back(s_value);
					records1 += TableStruct.attribute[k].attr_len;
					delete[]value;
				}
				tmpRecords.push_back(tmpRecord);
			}
			records2 += tmp->RecordLength;
			records1 = records2;
			delete[]left;
			delete[]left_;
		}
		//继续读取condition与原tmpRecords求交
		int ori_size = tmpRecords.size();
		for (int i = 1; i < SelectNum; i++) {
			for (int j = 0; j < ori_size; j++) {
				char *left = new char[tmp->RecordLength];
				char *left_ = new char[tmp->RecordLength];
				memcpy(left, tmpRecords[j][attriSelected[i] - 1].c_str(), tmpRecords[j][attriSelected[i] - 1].size());
				int m = 0;
				for (; m < TableStruct.attribute[attriSelected[i] - 1].attr_len; m++) {
					if (left[m] == '*')
						break;
				}
				if (strcmp(left_, "NULL") == 0)
					continue;
				strncpy_s(left_, tmp->RecordLength, left, m);
				bool bSelected = false;
				if (TableStruct.attribute[attriSelected[i] - 1].attr_type == CHAR)
					bSelected = comparison_s(tmpRecords[j][attriSelected[i] - 1], condition[i].op, condition[i].Right);
				else if (TableStruct.attribute[attriSelected[i] - 1].attr_type == INT)
					bSelected = comparison_i(atoi(tmpRecords[j][attriSelected[i] - 1].c_str()), condition[0].op, atoi(condition[0].Right.c_str()));
				else
					bSelected = comparison_f(atof(tmpRecords[j][attriSelected[i] - 1].c_str()), condition[0].op, atof(condition[0].Right.c_str()));
				if (!bSelected) {
					if (bDeleted[j] == 1)
						bDeleted[j] = 0;
				}
			}
		}
		for (int i = 0; i < ori_size; i++) {
			if (bDeleted[i] == 1) {
				if (flag == 0)
					flag = 1;
				if (delet == BlockSize + 1) {
					string record_num = to_string(tmpRecord_num[i]);
					int del_num = atoi(record_num.c_str());
					tmp->FirstDelete = del_num;
					BM.SetHead(tmp);
					delet = del_num;
					memset(tmp->memory + BlockHeadSize + (delet - 1)*tmp->RecordLength, NULL, tmp->RecordLength);
				}
				else {
					string record_num = to_string(tmpRecord_num[i]);
					memcpy(tmp->memory + BlockHeadSize + (delet - 1)*tmp->RecordLength, record_num.c_str(), strlen(record_num.c_str()));
					sscanf_s(record_num.c_str(), "%d", &delet);
					memset(tmp->memory + BlockHeadSize + (delet - 1)*tmp->RecordLength, NULL, tmp->RecordLength);
				}
				for (int j = 0; j < TableStruct.num_of_attribute; j++) {
					if (TableStruct.attribute[j].UNIQUE) {
						string IndexName = GetAttributeOfIndexByName(TableName, TableStruct.attribute[j].attr_name);
						if (IndexName == "")
							continue;
						if (IsIndexExist(IndexName, TableName)) {
							bool judge;
							if (TableStruct.attribute[j].attr_type == CHAR) {
								judge = delete_from_index(TableStruct, TableStruct.attribute[j], tmpRecords[i][j], IndexName);
								if (!judge)
									cout << "Error occurred." << endl;
							}
							else if (TableStruct.attribute[j].attr_type == FLOAT) {
								float key = atof(tmpRecords[i][j].c_str());
								judge = delete_from_index(TableStruct, TableStruct.attribute[j], key, IndexName);
								if (!judge)
									cout << "Error occured." << endl;
							}
							else {
								int key = atoi(tmpRecords[i][j].c_str());
								judge = delete_from_index(TableStruct, TableStruct.attribute[j], key, IndexName);
								if (!judge)
									cout << "Error occured." << endl;
							}
						}
					}
				}
			}
			BM.WriteToDisk(TableName + RECORD, tmp);
			BM.SetHead(tmp);
		}
	}
	if (!flag)
		cout << "No records selected to delete." << endl;	
	return true;
}

bool DeleteRecords(const string TableName, Table TableStruct)
{
	/*int BlockNum = BM.BlockNum(TableName + RECORD);
	if (!BlockNum)
		return false;
	for (int i = 1; i <= BlockNum; i++) {
		Block *tmp = BM.GetBlock(TableName + RECORD, i);
		int RecordNum = BM.GetRecordNum(tmp, tmp->RecordLength);
		char *record = tmp->memory + BlockHeadSize;
		for (int j = 1; j <= RecordNum; j++) {
			memset(record, NULL, tmp->RecordLength);
			record += tmp->RecordLength;
		}
		BM.SetHead(tmp);
	}*/
	for (int i = 0; i < TableStruct.num_of_attribute; i++) {
		if (TableStruct.attribute[i].UNIQUE) {
			string IndexName = GetAttributeOfIndexByName(TableName, TableStruct.attribute[i].attr_name);
			if (IsIndexExist(IndexName, TableName)) {
				DropIndexCatalog(IndexName, TableName);
			}
		}
	}
	DropTableCatalog(TableName);
	CreateTableCatalog(TableStruct, TableName);
	return true;
}
