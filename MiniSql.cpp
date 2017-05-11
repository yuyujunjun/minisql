// MiniSql.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"minisql.h"
#include<string>
#include<iostream>
#include"Interpreter.h"
#include"BufferManager.h"
using namespace std;
BufferManager BM;

//interpreter¼ì²é³ÌÐò
/*int Table::get_attri_id(string attri_name) {
	for (int i = 0; i < num_of_attribute; i++) {
		if (attribute[i].attr_name == attri_name)return i;
	}
	return -1;
}
int Table::get_table_length() {
	int len = 0;
	for (int i = 0; i < num_of_attribute; ++i)
	{
		len += attribute[i].attr_len;
	}
	return len;
}*/

int main()
{
	string command;
	int status=-1;
	Interpreter inter;
	while (true) {
		cout << ENTER;
		getline(cin, command, ';');
		status = inter.interpreter(command);
		if (status == quit)break;
		
	}
	return 0;
}



/*void main()
{
	BufferManager Buffer;
	Buffer.InitalBlock();
}*/

