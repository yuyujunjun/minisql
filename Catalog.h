#pragma once

#include "all.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
using namespace std;

int GetRecordLength(Table T); //�õ�����һ����¼�ĳ���
int GetAttributeLength(int type, int typelength = 0); //�õ�һ�����Եĳ���

void CreateTableCatalog(Table TableNode, string TableName); //����һ�ű��catalog�ļ�
Table FindTableCatalog(string TableName); //����һ�ű�Ľṹ��������Ϣ��������Table�ͱ�����
void DropTableCatalog(string TableName); //ɾ��һ�ű�
bool IsTableExist(string TableName);  //�жϱ��Ƿ����
void AllTable();  //�鿴���������б�

void CreateIndexCatalog(Attribute AttributeNode, string IndexName, string TableName);//����һ��������catalog�ļ�
Attribute GetAttributeOfIndex(string IndexName,string TableName);//����һ�������Ľṹ������һ��Attribute���Ե�ֵ
void DropIndexCatalog(string IndexName , string TableName); //ɾ��һ������
bool IsIndexExist(string IndexName,string TableName); //�ж������Ƿ����
void AllIndex(); //�鿴�������������������ı�