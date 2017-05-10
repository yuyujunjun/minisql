#pragma once
#include<string>
#include<iostream>
using namespace std;
#define HELLO "hello, user"
#define ENTER "->"
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

