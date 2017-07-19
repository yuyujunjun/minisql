#pragma once

#include"all.h"
#include<iostream>
using namespace std;
#define HELLO "Welcome to your database!"

#define ENTER "->"

#define QUIT "thx for using, hoping back!"
class Interpreter
{
public:
	Interpreter()
	{
		cout << HELLO << endl;
	}
	int interpreter(string s);
	string file;
	string get_word(string s, int &t);
	~Interpreter();
};

