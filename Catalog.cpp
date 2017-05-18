#include"stdafx.h"
#include "Catalog.h"

int GetAttributeLength(int type , int typelength)
{
	//写入文件转换为char*类型，长度设置为10
	if (type == INT)
	{
		return 10;
	}
	//比int多了个小数点，长度11
	else if (type == FLOAT)
	{
		return 11;
	}
	else
	{
		return typelength;
	}
}
//计算一个属性的长度

int GetRecordLength(Table T)
{
	int num = T.num_of_attribute;
	int length=0;
	//把每个属性的长度相加
	for (int i = 0; i < num; i++)
	{
		length += GetAttributeLength(T.attribute[i].attr_type,T.attribute[i].attr_len);
	}
	return length;
}
/*********************************************************************
函数名：int GetRecordLength(string tablename)
传入参数：表结构信息
返回值：该表一条属性的长度
函数功能：计算表的记录的长度
**********************************************************************/

void CreateTableCatalog(Table TableNode, string TableName)
{
	int i;
	char* s;
	s = new char[256];
	ofstream out;
	fstream file;
	//判断该表名是否已经存在
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
		//将所有信息转换为字符串写入文件中
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
		//在所有表的记录文件中添加该表名
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
函数名：void CreateTableCatalog(Table TableNode, string TableName)
传入参数：表结构的变量，表名
返回值：无
函数功能：创建一张表的catalog文件，同时创建一个record文件可以写入该表
          的记录
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
	//将catalog文件中的字符串转为正确信息并初始化一个Table变量
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
函数名：Table FindTableCatalog(string TableName)
传入参数：表名
返回值：一张表的结构信息，存在一个Table型变量里
函数功能：将指定表的信息读入一个Table型变量中
*****************************************************************************/

void CreateIndexCatalog(Attribute AttributeNode, string IndexName, string TableName)
{
	int i;
	char* s;
	s = new char[256];
	ofstream out;
	fstream file;
	//一张表上没有同名索引时才能创建索引
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
		//将属性的信息和索引的信息写入索引的catalog文件中
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
传入参数：一个属性的结构变量，索引名，索引所建表名
返回值：无
函数功能：根据属性的信息，索引名，所建表名创建索引的catalog文件
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
	//将一个索引所建的属性信息转为正确的类型，并初始化一个属性的结构变量
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
函数名：Attribute GetAttributeOfIndex(string IndexName,string TableName)
传入参数：索引名，所建表名
返回值：一个储存了该索引所建的属性的信息的Attribute变量
函数功能：将索引所建属性的信息读出
****************************************************************************/

void DropTableCatalog(string TableName)
{
	ifstream in;
	ofstream out;
	//初始化s
	string s="";
	in.open("all_table.txt");
	//创建临时文件，将除了被删表之外的所有信息写入，再替换原文件，达到文件的删除一条记录的效果
	out.open("AllTable.txt",ios::app);
	while (!in.eof())
	{
		in >> s;
		if (TableName == s)
			continue;
		//过滤空格，转行符等
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
		//删除源文件
		remove("all_table.txt");
		//用临时文件替换源文件
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
函数名：void DropTableCatalog(string TableName)
传入参数：表名
返回值：无
函数功能：删除一张表（结构和记录），并删除其在所有表文件中的记录
*********************************************************************/

void DropIndexCatalog(string IndexName,string TableName)
{
	ifstream in;
	ofstream out;
	string s1 = "";
	string s2 = "";
	string s3 = "";
	in.open("all_index.txt");
	//创建零时文件
	out.open("AllIndex.txt", ios::app);
	while (!in.eof())
	{
		in >> s1;
		in >> s2;
		in >> s3;
		//过滤索引名和所属表与传入参数相同的记录
		if (TableName == s3 && IndexName == s1)
			continue;
		//过滤空格，转行符等
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
		//删除源文件
		remove("all_index.txt");
		//用临时文件替换源文件
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
函数名：void DropIndexCatalog(string IndexName,string TableName)
传入参数：表名，索引名
返回值：无
函数功能：删除一个索引（结构和记录），并删除其在所有索引文件中的记录
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
//判断一张表是否存在

bool IsIndexExist(string IndexName,string TableName)
{
	fstream file;
	//同一张表上有同名索引则创建失败
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
//判断一个索引是否存在

void AllTable()
{
	ifstream in;
	string s="";
	in.open("all_table.txt");
	while (!in.eof())
	{
		in >> s;
		//过滤空格，转行符
		if (s!="")
		    cout << s << endl;
		s = "";
	}
	in.close();
	in.clear();
}
//显示所有表

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
		//过滤空格，转行符
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
//显示所有索引
