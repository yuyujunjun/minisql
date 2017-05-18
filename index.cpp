#include"stdafx.h"
#include"index.h"
extern BufferManager BM;

//需要修改的地方： table.table_name+"_"+__indexname__+INDEX:储存index信息的文件
//rrrecord_filename储存记录的地方
//每条记录的长度
/*
void save_index(Bplus<string>* btree, Attribute attribute) {
	int front, behind;
	front = behind = 0;
	int length = GetAttributeLength(INT, 4);
	length += GetAttributeLength(attribute.attr_type, attribute.attr_len);//index文件中每条记录的长度
	Btree_node<string>* queue[100];
	queue[behind++] = btree->root;
	while (front != behind) {
		Btree_node<string> * temp = queue[front];
		front++;
		int offset;
		////cout << "next :" << endl;
		if (!temp->isleaf) {
			for (int i = 0; i <= temp->keynum; i++) {
				queue[behind++] = temp->child[i];
			}
		}
		if (!temp->isleaf) {
			offset = -1;
		}
		else {
			offset = 1;
		}
		Block* tmp_block = BM.GetBlock(table.table_name+"_"+__indexname__+INDEX);
		for (int i = 0; i < temp->keynum; i++) {
			////cout << temp->attr[i] << " ";
			char *s;
			s = new char[maxlength];
			memset(s, 0, maxlength);
			int convert;
			if (offset == -1)sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", -1);
			else sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", temp->blocknum[i]);

			if (attribute.attr_type == INT) {
				convert = GetAttributeLength(INT);
				sprintf_s(s + 10, convert + 1, "%-10d", temp->attr[i]);
			}
			else if (attribute.attr_type == FLOAT) {
				sprintf_s(s + 10, GetAttributeLength(FLOAT) + 1, "%-11f", temp->attr[i]);
			}
			else if (attribute.attr_type == CHAR) {
				string tmp = temp->attr[i];
				string space = " ";
				int len = tmp.size();//markmarkmakrmakrmarkmarkmarkmarkmakrmakrmarkmarkmarkmarkmakrmakrmarkmarkmarkmarkmakrmakrmarkmarkmarkmarkmakrmakrmarkmarkmarkmarkmakrmakrmarkmarkmarkmarkmakrmakrmarkmark
				int k = 10;
				int ir = 0;
				for (k; k < attribute.attr_len - len + 10; k++) {
					s[k] = ' ';

					////cout << "s:" << s[k];
				}
				for (k; k < attribute.attr_len + 10; k++) {
					s[k] = tmp[ir++];
					////cout << "s:" << s[k];
				}
				s[k] = 0;
				//sprintf_s(s + 10, sizeof(space)+ 1, "%s", space);
				//sprintf_s(s + 10+sizeof(space), sizeof(tmp)+ 1, "%s", temp->attr[i]);
			}
			BM.WriteToMemory(tmp_block, s, length);
			BM.WriteToDisk(table.table_name+"_"+__indexname__+INDEX, tmp_block);
			//memset(s, 0, 20);
		}
	}

}
void save_index(Bplus<int>* btree, Attribute attribute) {
	int front, behind;
	front = behind = 0;
	int length = GetAttributeLength(INT, 4);
	length += GetAttributeLength(attribute.attr_type, attribute.attr_len);//index文件中每条记录的长度
	Btree_node<int>* queue[100];
	queue[behind++] = btree->root;
	while (front != behind) {
		Btree_node<int> * temp = queue[front];
		front++;
		int offset;
		//cout << "next :" << endl;
		if (!temp->isleaf) {
			for (int i = 0; i <= temp->keynum; i++) {
				queue[behind++] = temp->child[i];
			}
		}
		if (!temp->isleaf) {
			offset = -1;
		}
		else {
			offset = 1;
		}
		Block* tmp_block = BM.GetBlock(table.table_name+"_"+__indexname__+INDEX);
		for (int i = 0; i < temp->keynum; i++) {
			//cout << temp->attr[i] << " ";
			char *s;
			s = new char[maxlength];
			memset(s, 0, maxlength);
			int convert;
			if (offset == -1)sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", -1);
			else sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", temp->blocknum[i]);

			if (attribute.attr_type == INT) {
				convert = GetAttributeLength(INT);
				sprintf_s(s + 10, convert + 1, "%-10d", temp->attr[i]);
			}

			BM.WriteToMemory(tmp_block, s, length);
			BM.WriteToDisk(table.table_name+"_"+__indexname__+INDEX, tmp_block);
			//memset(s, 0, 20);
		}
	}

}
void save_index(Bplus<float>* btree, Attribute attribute) {
	int front, behind;
	front = behind = 0;
	int length = GetAttributeLength(INT, 4);
	length += GetAttributeLength(attribute.attr_type, attribute.attr_len);//index文件中每条记录的长度
	Btree_node<float>* queue[100];
	queue[behind++] = btree->root;
	while (front != behind) {
		Btree_node<float> * temp = queue[front];
		front++;
		int offset;
		//cout << "next :" << endl;
		if (!temp->isleaf) {
			for (int i = 0; i <= temp->keynum; i++) {
				queue[behind++] = temp->child[i];
			}
		}
		if (!temp->isleaf) {
			offset = -1;
		}
		else {
			offset = 1;
		}
		Block* tmp_block = BM.GetBlock(table.table_name+"_"+__indexname__+INDEX);
		for (int i = 0; i < temp->keynum; i++) {
			////cout << temp->attr[i] << " ";
			char *s;
			s = new char[maxlength];
			memset(s, 0, maxlength);
			int convert;
			if (offset == -1)sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", -1);
			else sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", temp->blocknum[i]);

			if (attribute.attr_type == FLOAT) {
				sprintf_s(s + 10, GetAttributeLength(FLOAT) + 1, "%-11f", temp->attr[i]);
			}

			BM.WriteToMemory(tmp_block, s, length);
			BM.WriteToDisk(table.table_name+"_"+__indexname__+INDEX, tmp_block);
			//memset(s, 0, 20);
		}
	}

}*/
void rewrite(string oldname) {
	for (int i = 0; i < BM.BlockNum(oldname); i++) {
		Block* temp = BM.GetBlock(oldname, i + 1);
		BM.SetPin(temp, false);
		BM.InitalBlock(temp);
	}
	remove(oldname.c_str());
	for (int i = 0; i < BM.BlockNum(tempfile); i++) {
		Block* temp = BM.GetBlock(tempfile, i + 1);
		BM.SetPin(temp, false);
		BM.InitalBlock(temp);
	}
	rename(tempfile, oldname.c_str());
}

void saveindex(Btree_node<int>* root, Attribute attribute,int &index, string filename) {
	int length = GetAttributeLength(INT, 4);
	length += GetAttributeLength(attribute.attr_type, attribute.attr_len);//index文件中每条记录的长度
	Block* tmp_block;
	tmp_block = BM.GetBlock(tempfile);
	if (root->isleaf) {
		for (int i = 0; i < root->keynum; i++) {
			////cout << temp->attr[i] << " ";
			char *s;
			s = new char[maxlength];
			memset(s, 0, maxlength);
			int convert;
			sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", root->blocknum[i]);
			sprintf_s(s + 10, GetAttributeLength(INT) + 1, "%-10d", root->attr[i]);
			BM.WriteToMemory(tmp_block, s, length);
			
			delete[]s;
		}
		BM.WriteToDisk(tempfile, tmp_block);
	}else {
		//Block* tmp_block = BM.GetBlock(table.table_name+"_"+__indexname__+INDEX);
		for (int i = 0; i < root->keynum; i++) {
			////cout << temp->attr[i] << " ";
			char *s;
			s = new char[maxlength];
			memset(s, 0, maxlength);
			int convert;
			sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", -1);
			sprintf_s(s + 10, GetAttributeLength(INT) + 1, "%-10d", root->attr[i]);
			BM.WriteToMemory(tmp_block, s, length);
			
			delete[]s;	
		}
		BM.WriteToDisk(tempfile, tmp_block); 
		for (int i = 0; i <= root->keynum; i++) {
			saveindex(root->child[i], attribute,index,filename);
		}
	}
}
void saveindex(Btree_node<float>* root, Attribute attribute,int &index,string filename) {
	int length = GetAttributeLength(INT, 4);
	length += GetAttributeLength(attribute.attr_type, attribute.attr_len);//index文件中每条记录的长度
	Block* tmp_block;
	tmp_block = BM.GetBlock(tempfile);

	if (root->isleaf) {
		//Block* tmp_block = BM.GetBlock(table.table_name+"_"+__indexname__+INDEX);
		for (int i = 0; i < root->keynum; i++) {
			////cout << temp->attr[i] << " ";
			char *s;
			s = new char[maxlength];
			memset(s, 0, maxlength);
			int convert;
			sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", root->blocknum[i]);
			sprintf_s(s + 10, GetAttributeLength(FLOAT) + 1, "%-11f", root->attr[i]);
			BM.WriteToMemory(tmp_block, s, length);
			
			delete[]s;
		}
		BM.WriteToDisk(tempfile, tmp_block);
	}
	else {
		//Block* tmp_block = BM.GetBlock(table.table_name+"_"+__indexname__+INDEX);
		for (int i = 0; i < root->keynum; i++) {
			////cout << temp->attr[i] << " ";
			char *s;
			s = new char[maxlength];
			memset(s, 0, maxlength);
			int convert;
			sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", -1);
			sprintf_s(s + 10, GetAttributeLength(FLOAT) + 1, "%-11f", root->attr[i]);
			BM.WriteToMemory(tmp_block, s, length);
			
			delete[]s;
		}
		BM.WriteToDisk(tempfile, tmp_block);
		for (int i = 0; i <= root->keynum; i++) {
			saveindex(root->child[i], attribute,index,filename);
		}
	}
}
void saveindex(Btree_node<string>* root, Attribute attribute,int &index, string filename) {
	int length = GetAttributeLength(INT, 4);
	length += GetAttributeLength(attribute.attr_type, attribute.attr_len);//index文件中每条记录的长度
	Block* tmp_block;
	tmp_block = BM.GetBlock(tempfile);

	if (root->isleaf) {
	//	Block* tmp_block = BM.GetBlock(table.table_name+"_"+__indexname__+INDEX);
		for (int i = 0; i < root->keynum; i++) {
			////cout << temp->attr[i] << " ";
			char *s;
			s = new char[maxlength];
			memset(s, 0, maxlength);
			int convert;
			sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", root->blocknum[i]);
			string tmp = root->attr[i];
			string space = " ";
			int len = tmp.size();
			int k = 10;
			int ir = 0;
			for (k; k < attribute.attr_len - len + 10; k++) {
				s[k] = '~';
			}
			for (k; k < attribute.attr_len + 10; k++) {
				s[k] = tmp[ir++];
			}
			s[k] = 0;
			//sprintf_s(s + 10, GetAttributeLength(INT) + 1, "%-10d", root->attr[i]);
			BM.WriteToMemory(tmp_block, s, length);
			
			delete[]s;
		}
		BM.WriteToDisk(tempfile, tmp_block);
	}
	else {
		//Block* tmp_block = BM.GetBlock(table.table_name+"_"+__indexname__+INDEX);
		for (int i = 0; i < root->keynum; i++) {
			////cout << temp->attr[i] << " ";
			char *s;
			s = new char[maxlength];
			memset(s, 0, maxlength);
			int convert;
			sprintf_s(s, GetAttributeLength(INT) + 1, "%-10d", -1);
			string tmp = root->attr[i];
			string space = " ";
			int len = tmp.size();
			int k = 10;
			int ir = 0;
			for (k; k < attribute.attr_len - len + 10; k++) {
				s[k] = '~';
			}
			for (k; k < attribute.attr_len + 10; k++) {
				s[k] = tmp[ir++];
			}
			s[k] = 0;
			//sprintf_s(s + 10, GetAttributeLength(INT) + 1, "%-10d", root->attr[i]);
			BM.WriteToMemory(tmp_block, s, length);
			
			delete[]s;
		}
		BM.WriteToDisk(tempfile, tmp_block);
		for (int i = 0; i <= root->keynum; i++) {
			saveindex(root->child[i], attribute,index,filename);
		}
	}
}
void  index_create_index(Table table, Attribute attribute, Bplus<string>* btree, string __indexname__) {
	int each_length = 30;//每条记录的长度
	int attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
	Block* temp[maxblock];//获取储存记录的块并存储
	int i = 0;
	int attribute_position = 0;//该属性在每个记录的位置
	int blocknumber = BM.BlockNum(rrrecord_filename);//文件中有几个块
	//int blocknumber = 7;
	for (i = 0; i < table.num_of_attribute; i++) {
		if (attribute.attr_name == table.attribute[i].attr_name)break;
		else {
			attribute_position += GetAttributeLength(table.attribute[i].attr_type, table.attribute[i].attr_len);
		}
	}
	if (i == table.num_of_attribute)return;//没有这个属性

	for (int j = 1; j <= blocknumber; j++) {
		temp[j] = BM.GetBlock(rrrecord_filename, j);
		int delet = temp[j]->FirstDelete;//初始化第一个被删除的位置
		BM.SetPin(temp[j], true);
		int recordnumber = (temp[j]->Size - BlockHeadSize) / each_length;//调用bm的函数
		for (int i = 1; i <= recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp[j]->memory + BlockHeadSize + (i-1)*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				delete[]record;
				////cout << "delete: " << delet;
			}
			else {
				char* record = new char[100];
				memset(record, 0, 100);
				memcpy(record, temp[j]->memory + BlockHeadSize + (i-1)*each_length, each_length);
				int offset = j;
				char* char_value = new char[100];
				memset(char_value, 0, 100);
				int value;

				if (attribute.attr_type == CHAR) {
					memcpy(char_value, record + attribute_position, attri_length);
					//	value=char_value;
					string t = " ";
					btree->insert_into_btree(char_value, CHAR, offset);
					//sscanf_s(char_value, "%s", &value);
					//btree_string->insert_into_btree(value, offset);
					////cout << value << endl;
				}
				delete[]record;
				delete[]char_value;
			}

		}
	}
	int index = 0;/////////////////////////////////////////////////////////////////////////////////////////
	ofstream tempout;
	tempout.open(tempfile);
	tempout.close();
	tempout.clear();
	string filename = table.table_name+"_"+__indexname__+INDEX;
	
	saveindex(btree->root, attribute,index, filename);
	rewrite(table.table_name+"_"+__indexname__+INDEX);
	return;
}
void  index_create_index(Table table, Attribute attribute, Bplus<int>* btree, string __indexname__) {
	int each_length = 30;//每条记录的长度
	int attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
	Block* temp[maxblock];//获取储存记录的块并存储
	int i = 0;
	int attribute_position = 0;//该属性在每个记录的位置
	int blocknumber = BM.BlockNum(rrrecord_filename);//文件中有几个块
	//int blocknumber = 7;
	for (i = 0; i < table.num_of_attribute; i++) {
		if (attribute.attr_name == table.attribute[i].attr_name)break;
		else {
			attribute_position += GetAttributeLength(table.attribute[i].attr_type, table.attribute[i].attr_len);
		}
	}
	if (i == table.num_of_attribute)return;//没有这个属性

	for (int j = 1; j <= blocknumber; j++) {
		temp[j] = BM.GetBlock(rrrecord_filename, j);
		int delet = temp[j]->FirstDelete;//初始化第一个被删除的位置
		BM.SetPin(temp[j], true);
		int recordnumber = (temp[j]->Size - BlockHeadSize) / each_length;//调用bm的函数
		for (int i = 1; i <= recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp[j]->memory + BlockHeadSize + (i-1)*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				////cout << "delete: " << delet;
				delete[]record;
		
			}
			else {
				char* record = new char[100];
				memset(record, 0, 100);
				memcpy(record, temp[j]->memory + BlockHeadSize + (i-1)*each_length, each_length);
				int offset = j;
				char* char_value = new char[100];
				memset(char_value, 0, 100);
				int value;
				if (attribute.attr_type == INT) {
					memcpy(char_value, record + attribute_position, attri_length);
					sscanf_s(char_value, "%d", &value);
					int t = 0;
					btree->insert_into_btree(value, INT, offset);
					////cout << value << endl;

				}
				delete[]record;
				delete[]char_value;
			}

		}
	}
	int index = 0;
	ofstream tempout;
	tempout.open(tempfile);
	tempout.close();
	tempout.clear();
	string filename = table.table_name+"_"+__indexname__+INDEX;
	saveindex(btree->root, attribute, index, filename);
	rewrite(table.table_name+"_"+__indexname__+INDEX);
	return;
}
void  index_create_index(Table table, Attribute attribute, Bplus<float>* btree, string __indexname__) {
	int each_length = 30;//每条记录的长度
	int attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
	Block* temp[maxblock];//获取储存记录的块并存储
	int i = 0;
	int attribute_position = 0;//该属性在每个记录的位置
	int blocknumber = BM.BlockNum(rrrecord_filename);//文件中有几个块
	//int blocknumber = 7;
	for (i = 0; i < table.num_of_attribute; i++) {
		if (attribute.attr_name == table.attribute[i].attr_name)break;
		else {
			attribute_position += GetAttributeLength(table.attribute[i].attr_type, table.attribute[i].attr_len);
		}
	}
	if (i == table.num_of_attribute)return;//没有这个属性

	for (int j = 1; j <= blocknumber; j++) {
		temp[j] = BM.GetBlock(rrrecord_filename, j);
		int delet = temp[j]->FirstDelete;//初始化第一个被删除的位置
		BM.SetPin(temp[j], true);
		int recordnumber = (temp[j]->Size - BlockHeadSize) / each_length;//调用bm的函数
		for (int i = 1; i <= recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp[j]->memory + BlockHeadSize + (i-1)*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				delete[]record;
				////cout << "delete: " << delet;
			}
			else {
				char* record = new char[100];
				memset(record, 0, 100);
				memcpy(record, temp[j]->memory + BlockHeadSize + (i-1)*each_length, each_length);
				int offset = j;
				char* char_value = new char[100];
				memset(char_value, 0, 100);
				float value;

				if (attribute.attr_type == FLOAT) {
					memcpy(char_value, record + attribute_position, attri_length);
					sscanf_s(char_value, "%f", &value);
					btree->insert_into_btree(value, FLOAT, offset);
					////cout << value << endl;
					//btree_float->insert_into_btree(value, offset);
					
				}
				delete[]record;
				delete[]char_value;
			}

		}
	}
	int index = 0;
	ofstream tempout;
	tempout.open(tempfile);
	tempout.close();
	tempout.clear();
	string filename = table.table_name+"_"+__indexname__+INDEX;
	saveindex(btree->root, attribute, index, filename);
	rewrite(table.table_name+"_"+__indexname__+INDEX);
	return;
}
int query_on_index_from_file(Table table, Attribute index,int QAQ, string __indexname__) {
		Bplus<int>* bp;
		int key = 0;
		bp=read_from_block(table, index, key, __indexname__);
		return bp->query_on_btree(QAQ);
	return 0;
}
int query_on_index_from_file(Table table, Attribute index, string QAQ, string __indexname__) {

		Bplus<string>*bp;
		string key = "";
		bp = read_from_block(table, index, key, __indexname__);
		int attrlen = GetAttributeLength(index.attr_type, index.attr_len);
		return bp->query_on_btree(QAQ);
		/*	int front, index;
		front = index = 0;
		Btree_node<string>* queue[100];
		queue[index++] = bp->root;
		while (front != index) {
		Btree_node<string> * temp = queue[front];
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
		cout << "level: " << endl;
		cout << "isroot: " << temp->isroot << endl;
		cout << "isleaf: " << temp->isleaf << endl;
		for (int i = 0; i < temp->keynum; i++) {

		cout << "attr: " << temp->attr[i] << " ";
		cout << "block: " << temp->blocknum[i] << " ";
		}
		//cout << endl;

		}
		cout << "<<<<<<<<<<<<<<<<<<<<<" << endl;*/

	return 0;
}
int query_on_index_from_file(Table table, Attribute index, float QAQ, string __indexname__) {
		Bplus<float>*bp;
		float key = 1.1;
		bp = read_from_block(table, index, key, __indexname__);
		return bp->query_on_btree(QAQ);
	return 0;
}
Btree_node<int>* read_index(int blocksum, int &blockid, string filename,int each_length,int attri_length,int key) {
	Btree_node<int>* bt = NULL;
	blockid++;
	if (blockid <= blocksum) {
		bt = new Btree_node<int>(filename);
		Block* temp;//获取储存记录的块并存储
		temp = BM.GetBlock(filename, blockid);
		int recordnumber = (temp->Size - BlockHeadSize) / each_length;//调用bm的函数
		int delet = temp->FirstDelete;
		int index = 0;
		for (int i = 1; i <= recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp->memory + BlockHeadSize + (i - 1)*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				delete[]record;
			}
			else {
				int off;
				int val;
				char* record = new char[100];
				char* offset = new char[11];
				char* value = new char[100];
				memset(record, 0, 100);
				memset(offset, 0, 11);
				memset(value, 0, 100);
				memcpy(record, temp->memory + BlockHeadSize + (i - 1)*each_length, each_length);//将一条记录读到record中
				memcpy(offset, record, GetAttributeLength(INT));//将offset从record读到offset中
				sscanf_s(offset, "%d", &off);//将offset读到int
				memcpy(value, record + GetAttributeLength(INT), attri_length);//将值读到value中
				sscanf_s(value, "%d", &val);
				delete[]record;
				delete[] offset;
				delete[]value;
				if (off == -1) {
					bt->isleaf = false;
					bt->attr[index] = val;
					bt->blocknum[index] = off;
					bt->keynum++;
					index++;
				}
				else {
					bt->isleaf = true;
					bt->attr[index] = val;
					bt->blocknum[index] = off;
					bt->keynum++;
					index++;
				}
				bt->min = bt->attr[0];
			}
		}
		if (!bt->isleaf) {
			for (int i = 0; i <= index; i++) {
				int key = 0;
				bt->child[i] = read_index(blocksum, blockid, filename, each_length, attri_length,key);
			}
		}
	}
	
	return bt;
}
Btree_node<float>* read_index(int blocksum, int &blockid, string filename, int each_length, int attri_length, float key) {
	Btree_node<float>* bt = NULL;
	blockid++;
	if (blockid <= blocksum) {
		bt = new Btree_node<float>(filename);
		Block* temp;//获取储存记录的块并存储
		temp = BM.GetBlock(filename, blockid);
		int recordnumber = (temp->Size - BlockHeadSize) / each_length;//调用bm的函数
		int delet = temp->FirstDelete;
		int index = 0;
		for (int i = 1; i <= recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp->memory + BlockHeadSize + (i - 1)*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				delete[]record;
			}
			else {
				int off;
				float val;
				char* record = new char[100];
				char* offset = new char[11];
				char* value = new char[100];
				memset(record, 0, 100);
				memset(offset, 0, 12);
				memset(value, 0, 100);
				memcpy(record, temp->memory + BlockHeadSize + (i - 1)*each_length, each_length);//将一条记录读到record中
				memcpy(offset, record, GetAttributeLength(INT));//将offset从record读到offset中
				sscanf_s(offset, "%d", &off);//将offset读到int
				memcpy(value, record + GetAttributeLength(INT), attri_length);//将值读到value中
				sscanf_s(value, "%f", &val);
				delete[]record;
				delete[] offset;
				delete[]value;
				if (off == -1) {
					bt->isleaf = false;
					bt->attr[index] = val;
					bt->blocknum[index] = off;
					bt->keynum++;
					index++;
				}
				else {
					bt->isleaf = true;
					bt->attr[index] = val;
					bt->blocknum[index] = off;
					bt->keynum++;
					index++;
				}
				bt->min = bt->attr[0];
			}
		}
		if (!bt->isleaf) {
			for (int i = 0; i <= index; i++) {
				float key = 0;
				bt->child[i] = read_index(blocksum, blockid, filename, each_length, attri_length, key);
			}
		}
	}

	return bt;
}
Btree_node<string>* read_index(int blocksum, int &blockid, string filename, int each_length, int attri_length, string key) {
	Btree_node<string>* bt = NULL;
	blockid++;
	if (blockid <= blocksum) {
		bt = new Btree_node<string>(filename);
		Block* temp;//获取储存记录的块并存储
		temp = BM.GetBlock(filename, blockid);
		int recordnumber = (temp->Size - BlockHeadSize) / each_length;//调用bm的函数
		int delet = temp->FirstDelete;
		int index = 0;
		for (int i = 1; i <= recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp->memory + BlockHeadSize + (i - 1)*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				delete[]record;
			}
			else {
				int off;
				string val;
				char* record = new char[100];
				char* offset = new char[11];
				char* value = new char[100];
				memset(record, 0, 100);
				memset(offset, 0, 11);
				memset(value, 0, 100);
				memcpy(record, temp->memory + BlockHeadSize + (i - 1)*each_length, each_length);//将一条记录读到record中
				memcpy(offset, record, GetAttributeLength(INT));//将offset从record读到offset中
				sscanf_s(offset, "%d", &off);//将offset读到int
				memcpy(value, record + GetAttributeLength(INT), attri_length);//将值读到value中
				string tttmp;
				tttmp = value;
				int pos = 0;
				pos=tttmp.rfind('~');
				
				//if (pos == -1)pos = -1;
				val.assign(tttmp, pos+1, tttmp.size()-pos);
				delete[]record;
				delete[] offset;
				delete[]value;
				if (off == -1) {
					bt->isleaf = false;
					bt->attr[index] = val;
					bt->blocknum[index] = off;
					bt->keynum++;
					index++;
				}
				else {
					bt->isleaf = true;
					bt->attr[index] = val;
					bt->blocknum[index] = off;
					bt->keynum++;
					index++;
				}
				bt->min = bt->attr[0];
			}
		}
		if (!bt->isleaf) {
			for (int i = 0; i <= index; i++) {
				string key = "";
				bt->child[i] = read_index(blocksum, blockid, filename, each_length, attri_length, key);
			}
		}
	}

	return bt;
}
Bplus<int>* read_from_block(Table table, Attribute attribute, int key, string __indexname__) {
	bool isroot = true;
	int each_length;//每条记录的长度
	int attri_length;
	//if (attribute.attr_type == INT) {
	each_length = GetAttributeLength(INT) + GetAttributeLength(attribute.attr_type, attribute.attr_len);//每条记录的长度
	attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
																	   //}
																	   /*else if (attribute.attr_type == FLOAT) {
																	   each_length = GetAttributeLength(INT) + GetAttributeLength(attribute.attr_type, attribute.attr_len);//每条记录的长度
																	   attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
																	   }
																	   else if (attribute.attr_type == CHAR) {
																	   each_length = GetAttributeLength(INT) + GetAttributeLength(attribute.attr_type, attribute.attr_len);//每条记录的长度
																	   attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
																	   }*/
	int blocknumber = BM.BlockNum(table.table_name+"_"+__indexname__+INDEX);//获取文件中的块的数量
	int attribute_position = 10;//该属性在每个记录的位置
	int blockid = 0;//到文件的第几个块了
	if (blocknumber == 0)return 0;
	else {
		string bt_name = "query";
		Bplus<int>*bp = new Bplus<int>(bt_name, attribute.attr_type, attribute.attr_len);
		//bp->root = new Btree_node<int>(table.table_name+"_"+__indexname__+INDEX);
		int key = 0;
		bp->root = read_index(blocknumber, blockid, table.table_name+"_"+__indexname__+INDEX, each_length, attri_length, key);
		bp->root->isroot = true;
		return bp;


	}
}
Bplus<string>* read_from_block(Table table, Attribute attribute, string key, string __indexname__) {
	bool isroot = true;
	int each_length;//每条记录的长度
	int attri_length;
	//if (attribute.attr_type == INT) {
	each_length = GetAttributeLength(INT) + GetAttributeLength(attribute.attr_type, attribute.attr_len);//每条记录的长度
	attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
																	   //}
																	   /*else if (attribute.attr_type == FLOAT) {
																	   each_length = GetAttributeLength(INT) + GetAttributeLength(attribute.attr_type, attribute.attr_len);//每条记录的长度
																	   attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
																	   }
																	   else if (attribute.attr_type == CHAR) {
																	   each_length = GetAttributeLength(INT) + GetAttributeLength(attribute.attr_type, attribute.attr_len);//每条记录的长度
																	   attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
																	   }*/
	int blocknumber = BM.BlockNum(table.table_name+"_"+__indexname__+INDEX);//获取文件中的块的数量
	int attribute_position = 10;//该属性在每个记录的位置
	int blockid = 0;//到文件的第几个块了
	if (blocknumber == 0)return 0;
	else {
			string bt_name = "query";
			Bplus<string>*bp = new Bplus<string>(bt_name, attribute.attr_type, attribute.attr_len);
			//bp->root = new Btree_node<int>(table.table_name+"_"+__indexname__+INDEX);
			string key = " ";
			bp->root = read_index(blocknumber, blockid, table.table_name+"_"+__indexname__+INDEX, each_length, attri_length, key);
			bp->root->isroot = true;
			return bp;

	}
}
Bplus<float>* read_from_block(Table table, Attribute attribute, float key, string __indexname__) {
	bool isroot = true;
	int each_length;//每条记录的长度
	int attri_length;
	//if (attribute.attr_type == INT) {
	each_length = GetAttributeLength(INT) + GetAttributeLength(attribute.attr_type, attribute.attr_len);//每条记录的长度
	attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
																	   //}
																	   /*else if (attribute.attr_type == FLOAT) {
																	   each_length = GetAttributeLength(INT) + GetAttributeLength(attribute.attr_type, attribute.attr_len);//每条记录的长度
																	   attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
																	   }
																	   else if (attribute.attr_type == CHAR) {
																	   each_length = GetAttributeLength(INT) + GetAttributeLength(attribute.attr_type, attribute.attr_len);//每条记录的长度
																	   attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//该属性的长度
																	   }*/
	int blocknumber = BM.BlockNum(table.table_name+"_"+__indexname__+INDEX);//获取文件中的块的数量
	int attribute_position = 10;//该属性在每个记录的位置
	int blockid = 0;//到文件的第几个块了
	if (blocknumber == 0)return 0;
	else {
		string bt_name = "query";
			Bplus<float>*bp = new Bplus<float>(bt_name, attribute.attr_type, attribute.attr_len);
			//bp->root = new Btree_node<int>(table.table_name+"_"+__indexname__+INDEX);
			float key = 0;
			bp->root = read_index(blocknumber, blockid, table.table_name+"_"+__indexname__+INDEX, each_length, attri_length, key);
			bp->root->isroot = true;
			return bp;
		
	}
}
bool insert_into_index(Table table, Attribute attribute, int QAQ,int offset, string __indexname__) {
	bool flag = true;
	Bplus<int>*bp;
	int key = 0;
	bp = read_from_block(table, attribute, key, __indexname__);
	flag=bp->insert_into_btree(QAQ,INT,offset);
	int index = 0;
	ofstream tempout;
	tempout.open(tempfile);
	tempout.close();
	tempout.clear();
	string filename = table.table_name+"_"+__indexname__+INDEX;
	saveindex(bp->root, attribute, index, filename);
	rewrite(table.table_name+"_"+__indexname__+INDEX);
	return flag;
}//如上重建b+树，然后插入值，再写回块
bool insert_into_index(Table table, Attribute attribute, string QAQ,int offset, string __indexname__) {
	bool flag=true;
	Bplus<string>*bp;
	string key = "";
	bp = read_from_block(table, attribute, key, __indexname__);
	flag=bp->insert_into_btree(QAQ, CHAR, offset);
	int index = 0;
	ofstream tempout;
	tempout.open(tempfile);
	tempout.close();
	tempout.clear();
	string filename = table.table_name+"_"+__indexname__+INDEX;
	saveindex(bp->root, attribute, index,filename);
	rewrite(table.table_name+"_"+__indexname__+INDEX);
	return flag;
}
bool insert_into_index(Table table, Attribute attribute, float QAQ,int offset,string __indexname__) {
	bool flag=true;
	Bplus<float>*bp;
	float key = 0;
	bp = read_from_block(table, attribute, key, __indexname__);
	flag=bp->insert_into_btree(QAQ, FLOAT, offset);
	int index = 0;
	ofstream tempout;
	tempout.open(tempfile);
	tempout.close();
	tempout.clear();
	string filename = table.table_name+"_"+__indexname__+INDEX;
	saveindex(bp->root, attribute, index, filename);
	rewrite(table.table_name+"_"+__indexname__+INDEX);
	return flag;
}//如上重建b+树，然后插入值，再写回块
bool delete_from_index(Table table, Attribute attribute, int QAQ, string __indexname__) {
	bool flag = true;
	Bplus<int>*bp;
	int key = 0;
	bp = read_from_block(table, attribute, key,  __indexname__);
	flag = bp->delete_from_btree(QAQ);
	int index = 0;
	ofstream tempout;
	tempout.open(tempfile);
	tempout.close();
	tempout.clear();
	string filename = table.table_name+"_"+__indexname__+INDEX;
	saveindex(bp->root, attribute, index, filename);
	rewrite(table.table_name+"_"+__indexname__+INDEX);
	return flag;
}//如上重建b+树，然后删除值，再写回块
bool delete_from_index(Table table, Attribute attribute, string QAQ, string __indexname__) {
	bool flag;
	Bplus<string>*bp;
	string key = "";
	bp = read_from_block(table, attribute, key, __indexname__);
	flag = bp->delete_from_btree(QAQ);
	int index = 0;
	ofstream tempout;
	tempout.open(tempfile);
	tempout.close();
	tempout.clear();
	string filename = table.table_name+"_"+__indexname__+INDEX;
	saveindex(bp->root, attribute, index, filename);
	rewrite(table.table_name+"_"+__indexname__+INDEX);
	return flag;
}
bool delete_from_index(Table table, Attribute attribute, float QAQ, string __indexname__) {
	bool flag = true;
	Bplus<float>*bp;
	float key = 0;
	bp = read_from_block(table, attribute, key, __indexname__);
	flag = bp->delete_from_btree(QAQ);
	int index = 0;
	ofstream tempout;
	tempout.open(tempfile);
	tempout.close();
	tempout.clear();
	string filename = table.table_name+"_"+__indexname__+INDEX;
	saveindex(bp->root, attribute, index, filename);
	rewrite(table.table_name+"_"+__indexname__+INDEX);
	return flag;
}
/*
void drop_index_record(Attribute index) {//叫buffer删掉index文件

}
int query_on_index(Attribute index) {//获取相应的index的块，获取每个块相对应的属性值和对应的块的位置，重建b+树，然后搜索找到此index可能出现的块，在那个块里面查找，返回值是该属性在文件中的块位置
return 0;
}
bool insert_into_index(Table table, Attribute attribute) {//如上重建b+树，然后插入值，再写回块
return true;
}
bool delete_from_index(Table table,Attribute attribute){//如上重建b+树，然后删除值，再写回块
return true;
}*/