#include"stdafx.h"
#include "Catalog.h"

int GetAttributeLength(int type , int typelength)
{
	//д���ļ�ת��Ϊchar*���ͣ���������Ϊ10
	if (type == INT)
	{
		return 10;
	}
	//��int���˸�С���㣬����11
	else if (type == FLOAT)
	{
		return 11;
	}
	else
	{
		return typelength;
	}
}
//����һ�����Եĳ���

int GetRecordLength(Table T)
{
	int num = T.num_of_attribute;
	int length=0;
	//��ÿ�����Եĳ������
	for (int i = 0; i < num; i++)
	{
		length += GetAttributeLength(T.attribute[i].attr_type,T.attribute[i].attr_len);
	}
	return length;
}
/*********************************************************************
��������int GetRecordLength(string tablename)
�����������ṹ��Ϣ
����ֵ���ñ�һ�����Եĳ���
�������ܣ������ļ�¼�ĳ���
**********************************************************************/

void CreateTableCatalog(Table TableNode, string TableName)
{
	int i;
	char* s;
	s = new char[256];
	ofstream out;
	fstream file;
	//�жϸñ����Ƿ��Ѿ�����
	if (!IsTableExist(TableName))
	{
		out.open(TableName + RECORD, ios::app);
		out.close();
		out.clear();
		file.open(TableName + RECORD, ios::in);
		if (!file)
		{
			cout << "crate table failed" << endl;
			return;
		}
		file.close();
		file.clear();
		//��������Ϣת��Ϊ�ַ���д���ļ���
		out.open(TableName + CATA_REC,ios::app);
		out << TableNode.table_name + ' ';
		memset(s,256,0);
		sprintf_s(s, 255, "%d", TableNode.primary_position);
		out << s << ' ';
		memset(s, 256, 0);
		sprintf_s(s, 255, "%d", TableNode.num_of_attribute);
		out << s << ' ';
		for (i = 0; i < TableNode.num_of_attribute; i++)
		{
			out << TableNode.attribute[i].attr_name << ' ';
			memset(s, 256, 0);
			sprintf_s(s, 255, "%d", TableNode.attribute[i].attr_type);
			out << s << ' ';
			memset(s, 256, 0);
			sprintf_s(s, 255, "%d", TableNode.attribute[i].attr_len);
			out << s << ' ';
			if (true == TableNode.attribute[i].NOTNULL)
				out << "NOTNULL" << ' ';
			else
				out << "NULL" << ' ';
			if (true == TableNode.attribute[i].UNIQUE)
				out << "UNIQUE" << ' ';
			else
				out << "NOTUNIQUE" << ' ';
		}
		out.close();
		out.clear();
		//�����б�ļ�¼�ļ�����Ӹñ���
		out.open("all_table.txt", ios::app);
		out << TableName << endl;
		out.close();
		out.clear();
		cout << "successfully creat table: " << TableName << endl;
	}
	else
	{
		cout << "the table is exist" << endl;
	}
	delete[] s;
}
/************************************************************************
��������void CreateTableCatalog(Table TableNode, string TableName)
�����������ṹ�ı���������
����ֵ����
�������ܣ�����һ�ű��catalog�ļ���ͬʱ����һ��record�ļ�����д��ñ�
          �ļ�¼
*************************************************************************/

Table FindTableCatalog(string TableName)
{
	Table T;
	int temp;
	ifstream in;
	char* s = new char[256];
	string ss;
	in.open(TableName+CATA_REC);
	if (!in)
	{
		cout << "the table is not exist" << endl;
		in.close();
		in.clear();
		delete[] s;
		return T;
	}
	//��catalog�ļ��е��ַ���תΪ��ȷ��Ϣ����ʼ��һ��Table����
	in >> T.table_name;
	memset(s, 256, 0);
	in >> s;
	sscanf_s(s,"%d",&temp);
	T.primary_position = temp;
	memset(s, 256, 0);
	in >> s;
	sscanf_s(s, "%d", &temp);
	T.num_of_attribute = temp;
	for (int i = 0; i < T.num_of_attribute; i++)
	{
		in >> T.attribute[i].attr_name;
		memset(s, 256, 0);
		in >> s;
		sscanf_s(s, "%d", &temp);
		T.attribute[i].attr_type = temp;
		memset(s, 256, 0);
		in >> s;
		sscanf_s(s, "%d", &temp);
		T.attribute[i].attr_len = temp;
		in >> ss;
		if ("NOTNULL" == ss)
			T.attribute[i].NOTNULL = true;
		else
			T.attribute[i].NOTNULL = false;
		ss = "";
		in >> ss;
		if ("NOTUNIQUE" == ss)
			T.attribute[i].UNIQUE = false;
		else
			T.attribute[i].UNIQUE = true;
	}
	in.close();
	in.clear();
	delete[] s;
	return T;
}
/****************************************************************************
��������Table FindTableCatalog(string TableName)
�������������
����ֵ��һ�ű�Ľṹ��Ϣ������һ��Table�ͱ�����
�������ܣ���ָ�������Ϣ����һ��Table�ͱ�����
*****************************************************************************/

void CreateIndexCatalog(Attribute AttributeNode, string IndexName, string TableName)
{
	int i;
	char* s;
	s = new char[256];
	ofstream out;
	fstream file;
	//һ�ű���û��ͬ������ʱ���ܴ�������
	if (!IsIndexExist(IndexName,TableName))
	{
		out.open(TableName +"_" +IndexName + INDEX, ios::app);
		out.close();
		out.clear();
		file.open(TableName + "_" + IndexName + INDEX, ios::in);
		if (!file)
		{
			cout << "crate index failed" << endl;
			return;
		}
		file.close();
		file.clear();
		//�����Ե���Ϣ����������Ϣд��������catalog�ļ���
		out.open(TableName + "_" + IndexName + CATA_IND, ios::app);
		out << TableName << ' ';
		out << IndexName << ' ';
		out << AttributeNode.attr_name << ' ';
		sprintf_s(s, 255, "%d", AttributeNode.attr_type);
		out << s << ' ';
		memset(s, 256, 0);
		sprintf_s(s, 255, "%d", AttributeNode.attr_len);
		out << s << ' ';
		if (true == AttributeNode.NOTNULL)
			out << "NOTNULL" << ' ';
		else
			out << "NULL" << ' ';
		if (true == AttributeNode.UNIQUE)
			out << "UNIQUE" << ' ';
		else
			out << "NOTUNIQUE" << ' ';
		out.close();
		out.clear();
		out.open("all_index.txt", ios::app);
		out << IndexName << " ON " << TableName << endl;
		out.close();
		out.clear();
		cout << "successfully create index: " << IndexName << " on " << TableName << endl;
	}
	else
	{
		cout << "the index is exist" << endl;
	}
	delete[] s;
}
/**************************************************************************************
void CreateIndexCatalog(Attribute AttributeNode, string IndexName, string TableName)
���������һ�����ԵĽṹ��������������������������
����ֵ����
�������ܣ��������Ե���Ϣ����������������������������catalog�ļ�
***************************************************************************************/

Attribute GetAttributeOfIndex(string IndexName,string TableName)
{
	Attribute A;
	ifstream in;
	int temp;
	string s;
	in.open(TableName + "_"+IndexName+CATA_IND);
	if (!in)
	{
		cout << "the index is not exist" << endl;
		in.close();
		in.clear();
		return A;
	}
	//��һ������������������ϢתΪ��ȷ�����ͣ�����ʼ��һ�����ԵĽṹ����
	in >> s;
	in >> s;
	in >> A.attr_name;
	in >> s;
	sscanf_s(s.c_str(),"%d",&temp);
	A.attr_type = temp;
	in >> s;
	sscanf_s(s.c_str(), "%d", &temp);
	A.attr_len = temp;
	in >> s;
	if ("NOTNULL" == s)
		A.NOTNULL = true;
	else
		A.NOTNULL = false;
	in >> s;
	if ("UNIQUE" == s)
		A.UNIQUE = true;
	else
		A.UNIQUE = false;
	in.close();
	in.clear();
	return A;
}
/***************************************************************************
��������Attribute GetAttributeOfIndex(string IndexName,string TableName)
�������������������������
����ֵ��һ�������˸��������������Ե���Ϣ��Attribute����
�������ܣ��������������Ե���Ϣ����
****************************************************************************/

void DropTableCatalog(string TableName)
{
	ifstream in;
	ofstream out;
	//��ʼ��s
	string s="";
	in.open("all_table.txt");
	//������ʱ�ļ��������˱�ɾ��֮���������Ϣд�룬���滻ԭ�ļ����ﵽ�ļ���ɾ��һ����¼��Ч��
	out.open("AllTable.txt",ios::app);
	while (!in.eof())
	{
		in >> s;
		if (TableName == s)
			continue;
		//���˿ո�ת�з���
		if (s != "")
		    out << s << endl;
		s = "";
	}
	in.close();
	in.clear();
	out.close();
	out.clear();
	if (!remove((TableName + CATA_REC).c_str()) && !remove((TableName + RECORD).c_str()))
	{
		cout << "successfully drop the table" << endl;
		out.close();
		out.clear();
		//ɾ��Դ�ļ�
		remove("all_table.txt");
		//����ʱ�ļ��滻Դ�ļ�
		rename("AllTable.txt","all_table.txt");
	}
	else
	{
		cout << "drop table failed" << endl;
		out.close();
		out.clear();
		remove("AllTable.txt");
	}
	return;
}
/********************************************************************
��������void DropTableCatalog(string TableName)
�������������
����ֵ����
�������ܣ�ɾ��һ�ű��ṹ�ͼ�¼������ɾ���������б��ļ��еļ�¼
*********************************************************************/

void DropIndexCatalog(string IndexName,string TableName)
{
	ifstream in;
	ofstream out;
	string s1 = "";
	string s2 = "";
	string s3 = "";
	in.open("all_index.txt");
	//������ʱ�ļ�
	out.open("AllIndex.txt", ios::app);
	while (!in.eof())
	{
		in >> s1;
		in >> s2;
		in >> s3;
		//�������������������봫�������ͬ�ļ�¼
		if (TableName == s3 && IndexName == s1)
			continue;
		//���˿ո�ת�з���
		if (s1 != "" && s2 != "" && s3 != "")
		{
			out << s1 << " ";
			out << s2 << " ";
			out << s3 << endl;
		}
		s1 = "";
		s2 = "";
		s3 = "";
	}
	in.close();
	in.clear();
	out.close();
	out.clear();
	if (!remove((TableName +"_"+ IndexName + CATA_IND).c_str()) && !remove((TableName +"_"+ IndexName + INDEX).c_str()))
	{
		cout << "successfully drop the index" << endl;
		out.close();
		out.clear();
		//ɾ��Դ�ļ�
		remove("all_index.txt");
		//����ʱ�ļ��滻Դ�ļ�
		rename("AllIndex.txt", "all_index.txt");
	}
	else
	{
		cout << "drop index failed" << endl;
		out.close();
		out.clear();
		remove("AllIndex.txt");
	}
	return;
}
/*********************************************************************
��������void DropIndexCatalog(string IndexName,string TableName)
���������������������
����ֵ����
�������ܣ�ɾ��һ���������ṹ�ͼ�¼������ɾ���������������ļ��еļ�¼
**********************************************************************/

bool IsTableExist(string TableName)
{
	fstream file;
	file.open(TableName + CATA_REC, ios::in);
	if (file)
	{
		file.close();
		file.clear();
		return true;
	}
	else
	{
		file.close();
		file.clear();
		return false;
	}
}
//�ж�һ�ű��Ƿ����

bool IsIndexExist(string IndexName,string TableName)
{
	fstream file;
	//ͬһ�ű�����ͬ�������򴴽�ʧ��
	file.open(TableName + "_" +IndexName + CATA_IND, ios::in);
	if (file)
	{
		file.close();
		file.clear();
		return true;
	}
	else
	{
		file.close();
		file.clear();
		return false;
	}
}
//�ж�һ�������Ƿ����

void AllTable()
{
	ifstream in;
	string s="";
	in.open("all_table.txt");
	while (!in.eof())
	{
		in >> s;
		//���˿ո�ת�з�
		if (s!="")
		    cout << s << endl;
		s = "";
	}
	in.close();
	in.clear();
}
//��ʾ���б�

void AllIndex()
{
	ifstream in;
	char ch;
	string s1="",s2="",s3="";
	in.open("all_index.txt");
	while (!in.eof())
	{
		in >> s1;
		in >> s2;
		in >> s3;
		//���˿ո�ת�з�
		if (s1 != "" && s2 != "" && s3 != "")
		{
			cout << s1 << " ";
			cout << s2 << " ";
			cout << s3 << endl;
		}
		s1 = "";
		s2 = "";
		s3 = "";
	}
	in.close();
	in.clear();
}
//��ʾ��������
