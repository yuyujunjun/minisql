#include"stdafx.h"
#include"index.h"
extern BufferManager BM;
void save_index(Bplus<string>* btree, Attribute attribute) {
	int front, behind;
	front = behind = 0;
	int length = GetAttributeLength(INT, 4);
	length += GetAttributeLength(attribute.attr_type, attribute.attr_len);//index�ļ���ÿ����¼�ĳ���
	Btree_node<string>* queue[100];
	queue[behind++] = btree->root;
	while (front != behind) {
		Btree_node<string> * temp = queue[front];
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
		Block* tmp_block = BM.GetBlock("index_name");
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

					cout << "s:" << s[k];
				}
				for (k; k < attribute.attr_len + 10; k++) {
					s[k] = tmp[ir++];
					cout << "s:" << s[k];
				}
				s[k] = 0;
				/*sprintf_s(s + 10, sizeof(space)+ 1, "%s", space);
				sprintf_s(s + 10+sizeof(space), sizeof(tmp)+ 1, "%s", temp->attr[i]);*/
			}
			BM.WriteToMemory(tmp_block, s, length);
			BM.WriteToDisk("index_name", tmp_block);
			//memset(s, 0, 20);
		}
	}

}
void save_index(Bplus<int>* btree, Attribute attribute) {
	int front, behind;
	front = behind = 0;
	int length = GetAttributeLength(INT, 4);
	length += GetAttributeLength(attribute.attr_type, attribute.attr_len);//index�ļ���ÿ����¼�ĳ���
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
		Block* tmp_block = BM.GetBlock("index_name");
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
			BM.WriteToDisk("index_name", tmp_block);
			//memset(s, 0, 20);
		}
	}

}
void save_index(Bplus<float>* btree, Attribute attribute) {
	int front, behind;
	front = behind = 0;
	int length = GetAttributeLength(INT, 4);
	length += GetAttributeLength(attribute.attr_type, attribute.attr_len);//index�ļ���ÿ����¼�ĳ���
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
		Block* tmp_block = BM.GetBlock("index_name");
		for (int i = 0; i < temp->keynum; i++) {
			//cout << temp->attr[i] << " ";
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
			BM.WriteToDisk("index_name", tmp_block);
			//memset(s, 0, 20);
		}
	}

}
void  index_create_index(Table table, Attribute attribute, Bplus<string>* btree) {
	int each_length = 30;//ÿ����¼�ĳ���
	int attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//�����Եĳ���
	Block* temp[maxblock];//��ȡ�����¼�Ŀ鲢�洢
	int i = 0;
	int attribute_position = 0;//��������ÿ����¼��λ��
							   //int blocknumber = BM.BlockNum(table.table_name + RECORD);//�ļ����м�����
	int blocknumber = 7;
	for (i = 0; i < table.num_of_attribute; i++) {
		if (attribute.attr_name == table.attribute[i].attr_name)break;
		else {
			attribute_position += GetAttributeLength(table.attribute[i].attr_type, table.attribute[i].attr_len);
		}
	}
	if (i == table.num_of_attribute)return;//û���������

	for (int j = 1; j <= blocknumber; j++) {
		temp[j] = BM.GetBlock("1.txt", j);
		int delet = temp[j]->FirstDelete;//��ʼ����һ����ɾ����λ��
		BM.SetPin(temp[j], true);
		int recordnumber = (temp[j]->Size - BlockHeadSize) / each_length;//����bm�ĺ���
		for (int i = 0; i < recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp[j]->memory + BlockHeadSize + i*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				//cout << "delete: " << delet;
			}
			else {
				char* record = new char[100];
				memset(record, 0, 100);
				memcpy(record, temp[j]->memory + BlockHeadSize + i*each_length, each_length);
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
					//cout << value << endl;
				}

			}

		}
	}
	save_index(btree, attribute);
	return;
}
void  index_create_index(Table table, Attribute attribute, Bplus<int>* btree) {
	int each_length = 30;//ÿ����¼�ĳ���
	int attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//�����Եĳ���
	Block* temp[maxblock];//��ȡ�����¼�Ŀ鲢�洢
	int i = 0;
	int attribute_position = 0;//��������ÿ����¼��λ��
							   //int blocknumber = BM.BlockNum(table.table_name + RECORD);//�ļ����м�����
	int blocknumber = 7;
	for (i = 0; i < table.num_of_attribute; i++) {
		if (attribute.attr_name == table.attribute[i].attr_name)break;
		else {
			attribute_position += GetAttributeLength(table.attribute[i].attr_type, table.attribute[i].attr_len);
		}
	}
	if (i == table.num_of_attribute)return;//û���������

	for (int j = 1; j <= blocknumber; j++) {
		temp[j] = BM.GetBlock("1.txt", j);
		int delet = temp[j]->FirstDelete;//��ʼ����һ����ɾ����λ��
		BM.SetPin(temp[j], true);
		int recordnumber = (temp[j]->Size - BlockHeadSize) / each_length;//����bm�ĺ���
		for (int i = 0; i < recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp[j]->memory + BlockHeadSize + i*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				//cout << "delete: " << delet;
			}
			else {
				char* record = new char[100];
				memset(record, 0, 100);
				memcpy(record, temp[j]->memory + BlockHeadSize + i*each_length, each_length);
				int offset = j;
				char* char_value = new char[100];
				memset(char_value, 0, 100);
				int value;
				if (attribute.attr_type == INT) {
					memcpy(char_value, record + attribute_position, attri_length);
					sscanf_s(char_value, "%d", &value);
					int t = 0;
					btree->insert_into_btree(value, INT, offset);
					//cout << value << endl;

				}
			}

		}
	}
	save_index(btree, attribute);
	return;
}
void  index_create_index(Table table, Attribute attribute, Bplus<float>* btree) {
	int each_length = 30;//ÿ����¼�ĳ���
	int attri_length = GetAttributeLength(attribute.attr_type, attribute.attr_len);//�����Եĳ���
	Block* temp[maxblock];//��ȡ�����¼�Ŀ鲢�洢
	int i = 0;
	int attribute_position = 0;//��������ÿ����¼��λ��
							   //int blocknumber = BM.BlockNum(table.table_name + RECORD);//�ļ����м�����
	int blocknumber = 7;
	for (i = 0; i < table.num_of_attribute; i++) {
		if (attribute.attr_name == table.attribute[i].attr_name)break;
		else {
			attribute_position += GetAttributeLength(table.attribute[i].attr_type, table.attribute[i].attr_len);
		}
	}
	if (i == table.num_of_attribute)return;//û���������

	for (int j = 1; j <= blocknumber; j++) {
		temp[j] = BM.GetBlock("1.txt", j);
		int delet = temp[j]->FirstDelete;//��ʼ����һ����ɾ����λ��
		BM.SetPin(temp[j], true);
		int recordnumber = (temp[j]->Size - BlockHeadSize) / each_length;//����bm�ĺ���
		for (int i = 0; i < recordnumber; i++) {
			if (i == delet) {
				char* record = new char[100];
				memcpy(record, temp[j]->memory + BlockHeadSize + i*each_length, each_length);
				sscanf_s(record, "%d", &delet);
				//cout << "delete: " << delet;
			}
			else {
				char* record = new char[100];
				memset(record, 0, 100);
				memcpy(record, temp[j]->memory + BlockHeadSize + i*each_length, each_length);
				int offset = j;
				char* char_value = new char[100];
				memset(char_value, 0, 100);
				int value;

				if (attribute.attr_type == FLOAT) {


					memcpy(char_value, record + attribute_position, attri_length);
					sscanf_s(char_value, "%f", &value);
					float t = (float)1;
					btree->insert_into_btree(value, FLOAT, offset);
					//cout << value << endl;
					//btree_float->insert_into_btree(value, offset);
				}
			}

		}
	}
	save_index(btree, attribute);
	return;
}


/*
void drop_index_record(Attribute index) {//��bufferɾ��index�ļ�

}
int query_on_index(Attribute index) {//��ȡ��Ӧ��index�Ŀ飬��ȡÿ�������Ӧ������ֵ�Ͷ�Ӧ�Ŀ��λ�ã��ؽ�b+����Ȼ�������ҵ���index���ܳ��ֵĿ飬���Ǹ���������ң�����ֵ�Ǹ��������ļ��еĿ�λ��
return 0;
}
bool insert_into_index(Table table, Attribute attribute) {//�����ؽ�b+����Ȼ�����ֵ����д�ؿ�
return true;
}
bool delete_from_index(Table table,Attribute attribute){//�����ؽ�b+����Ȼ��ɾ��ֵ����д�ؿ�
return true;
}*/