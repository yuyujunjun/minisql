// MiniSql.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"minisql.h"
#include<string>
#include<iostream>
#include"Interpreter.h"
using namespace std;




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

