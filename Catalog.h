#pragma once

#include "all.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
using namespace std;

int GetRecordLength(Table T); //得到表中一条记录的长度
int GetAttributeLength(int type, int typelength = 0); //得到一种属性的长度

void CreateTableCatalog(Table TableNode, string TableName); //创建一张表的catalog文件
Table FindTableCatalog(string TableName); //查找一张表的结构，属性信息，并放入Table型变量中
void DropTableCatalog(string TableName); //删除一张表
bool IsTableExist(string TableName);  //判断表是否存在
void AllTable();  //查看创建的所有表

void CreateIndexCatalog(Attribute AttributeNode, string IndexName, string TableName);//创建一个索引的catalog文件
Attribute GetAttributeOfIndex(string IndexName,string TableName);//查找一个索引的结构，返回一个Attribute属性的值
void DropIndexCatalog(string IndexName , string TableName); //删除一个索引
bool IsIndexExist(string IndexName,string TableName); //判断索引是否存在
void AllIndex(); //查看所有索引和他们所属的表