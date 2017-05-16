#include "stdafx.h"
#include "Interpreter.h"
#include<vector>
#include<string>
#include<sstream>
using namespace std;
//if input is wrong, we return 0, else we call the funcation from api and return 1

int op_for_sure(string word,int &op) {
	if (strcmp(word.c_str(), "<") == 0)op = LESS;
	else if (strcmp(word.c_str(), ">") == 0)op = MORE;
	else if (strcmp(word.c_str(), ">=") == 0)op = MORE_EQUAL;
	else if (strcmp(word.c_str(), "<=") == 0)op = LESS_EQUAL;
	else if (strcmp(word.c_str(), "=") == 0)op = EQUAL;
	else if (strcmp(word.c_str(), "<>") == 0)op = NOT_EQUAL;
	else { cout << "Syntax Error!" << endl; return 0; }
}
bool isCoverKey(string s) {
	if (strcmp(s.c_str(), "primary") == 0 || strcmp(s.c_str(), "unique") == 0 || strcmp(s.c_str(), "null") == 0 || strcmp(s.c_str(), "key")==0)
		return true;
	return false;
}
int Interpreter::interpreter(string command) {
	//cout << command << endl;
	int index = 0;
	string word;
	word = get_word(command, index);
	if (strcmp(word.c_str(), "create") == 0) {//create 
		word = get_word(command, index);
		if (strcmp(word.c_str(), "table") == 0) {
			//prepare table
			string primary = "";
			string table_name = "";
			word = get_word(command, index);//create table A
			if (!word.empty())table_name = word;
			else {
				cout << "illeagal table name in table" << endl;
				return 0;
			}
			word = get_word(command, index);//create table A(
			if (word.empty() || strcmp(word.c_str(), "(") != 0)
			{
				cout << "Error in syntax" << endl;
				return 0;
			}
			else {
				//prepare attribute array
				vector<Attribute> attr_array;
				word = get_word(command, index);
				while (!word.empty() && !isCoverKey(word) && strcmp(word.c_str(), ")") != 0) {
					string attribute_name = word;
					int type;
					bool unique = false;
					bool notnull = false;
					int attri_length;
					word = get_word(command, index);//create table a(id,int
					if (strcmp(word.c_str(), "int") == 0)
					{
						type = INT;
						attri_length = sizeof(int);

					}
					else if (strcmp(word.c_str(), "float") == 0)
					{
						type = FLOAT;
						attri_length = sizeof(float);
					}
					else if (strcmp(word.c_str(), "char") == 0)
					{
						type = CHAR;
						word = get_word(command, index);
						if (strcmp(word.c_str(), "("))
						{
							cout << "Syntax Error: unknown data type" << endl;
							return 0;
						}
						word = get_word(command, index);
						istringstream convert(word.c_str());
						if (!(convert >> attri_length))
						{
							cout << "Syntax error : illegal number in char()" << endl;
							return 0;
						}
						word = get_word(command, index);
						if (strcmp(word.c_str(), ")"))
						{
							cout << "Syntax Error: unknown data type" << endl;
							return 0;
						}
					}
					else {
						cout << "Syntax Error: unknown" << endl;
						return 0;
					}
					word = get_word(command, index);

					if (strcmp(word.c_str(), "unique") == 0) {
						unique = true;
						word = get_word(command, index);
					}
					if (strcmp(word.c_str(), "not") == 0) {
						word = get_word(command, index);
						if (strcmp(word.c_str(), "null") == 0) {
							notnull = true;
							word = get_word(command, index);
						}
						else {
							cout << "Syntax Error: extra not" << endl;
						}
					}
					Attribute temp(attribute_name, type, notnull, unique, attri_length);
					attr_array.push_back(temp);
					if (strcmp(word.c_str(), ",") != 0)
					{
						if (strcmp(word.c_str(), ")") != 0) {
							cout << "Syntax Error for ',' !" << endl;
							return 0;
						}
						else
							break;
					}
					word = get_word(command, index);
				}
					int primary_position = 0;
					if (strcmp(word.c_str(), "primary") == 0) {
						word = get_word(command, index);
						if (strcmp(word.c_str(), "key") != 0) {
							cout << "Syntax Error: illeagel definitioin primary key" << endl;
						}
						else {
							word = get_word(command, index);
							if (strcmp(word.c_str(), "(") == 0)
							{
								word = get_word(command, index);
								primary = word;
								int i;
								for ( i = 0; i < attr_array.size(); i++) {
									if (primary == attr_array[i].attr_name) {
										attr_array[i].UNIQUE = true;
										attr_array[i].NOTNULL = true;
										break;
									}
								}
								if (i >= attr_array.size()) {
									cout << "Syntax Error : illeagel definitioin primary key"<<endl;
									return 0;
								}
								primary_position = i;
								word = get_word(command, index);
								if (strcmp(word.c_str(), ")") != 0)
								{
									cout << "Error in syntax!" << endl;
									return 0;
								}
							}
							else {
								cout << "Error in syntax!" << endl;
								return 0;
							}
							word = get_word(command, index);
							if (strcmp(word.c_str(), ")") != 0)
							{
								cout << "Error in syntax!" << endl;
								return 0;
							}
						}
					}
					else  {
						cout << "Syntax Error: unknown error" << endl;
						return 0;
					}
					//这里调用api建表
					int i = 0;
					for (i = 0; i < attr_array.size(); i++) {
						cout << "name: " << attr_array[i].attr_name << " type:" << attr_array[i].attr_type << " unique:" << attr_array[i].UNIQUE << " notnull:" << attr_array[i].NOTNULL<<endl;
					}
					cout <<"primary key:"<< attr_array[primary_position].attr_name<<endl;
					return 1;
				}


			}
			else if (strcmp(word.c_str(), "index") == 0) {
				string index_name = "";
				string table_name = "";
				string attr_name = "";
				word = get_word(command, index);
				if (!word.empty()&&strcmp(word.c_str(),")")!=0) { index_name = word; }
				else {
					cout << "Synate Error" << endl;
					return 0;
				}
				word = get_word(command, index);
				if (strcmp(word.c_str(), "on") != 0) { cout << "Syntax Error!" << endl; return 0; }
				word = get_word(command, index);
				if(word.empty()) { cout << "Syntax Error!" << endl; return 0; }
				table_name = word;
				word = get_word(command, index);
				if(strcmp(word.c_str(),"(")!=0) { cout << "Syntax Error!" << endl; return 0; }
				word = get_word(command, index);
				if (word.empty() || strcmp(word.c_str(), ")")==0) { cout << "Syntax Error!" << endl; return 0; }
				attr_name = word;
				word = get_word(command, index);
				if(strcmp(word.c_str(),")")!=0) { cout << "Syntax Error!" << endl; return 0; }
				//这里调用api的新建索引
				cout << "index name:" << index_name << " table name:" << table_name << " attr_name:" << attr_name << endl;
				return 1;
			}
		}
		else if (strcmp(word.c_str(), "select") == 0) {
			word = get_word(command, index);
			vector<string> attr_name;
			string table_name = "";
			if (strcmp(word.c_str(), "*") == 0) {
				word = get_word(command, index);
			}
			else {
				while (strcmp(word.c_str(), "from") != 0) {
					if(strcmp(word.c_str(),",")!=0)
					attr_name.push_back(word);
					word = get_word(command, index);
				}
			}
			if(strcmp(word.c_str(),"from")!=0) { cout << "Syntax Error!" << endl; return 0; }
			word = get_word(command, index);
			if (!word.empty())table_name = word;
			else { cout << "Syntax Error!" << endl; return 0; }
			word = get_word(command, index);
			if (word.empty()) {
				if (attr_name.size() == 0)//调用select * from table_name
					cout << "table_name:" << table_name << "no condition" << endl;
				else {
					cout << "table_name:" << table_name << "no condition" << endl;
					for (int i = 0; i < attr_name.size(); i++) {
						cout <<" attr_name:"<< attr_name[i] << endl;
					}
				}
			}
			else if(strcmp(word.c_str(),"where")==0)
			{
				string attribute_left = "";
				string attribute_right = "";
				vector<Condition> condition_array;
				int op;
				word = get_word(command, index);
				while (true) {
					if (!word.empty()) {
						attribute_left = word;
						word = get_word(command, index);
						if (op_for_sure(word, op) == 0)return 0;
						word = get_word(command, index);
						if(word.empty()) { cout << "Syntax Error!" << endl; return 0; }
						else attribute_right = word;
						Condition temp(attribute_left, attribute_right, op);
						condition_array.push_back(temp);
						word = get_word(command, index);
						if (word.empty()) { break; }
						else if(strcmp(word.c_str(),"and")!=0) { cout << "Syntax Error!" << endl; return 0; }
						word = get_word(command, index);
					}else { cout << "Syntax Error!" << endl; return 0; }
				}
				if (attr_name.size() == 0)//有情况的查询select * from where
				{
					cout << "table_name:" << table_name  << endl;
					for (int i = 0; i < condition_array.size(); i++) {
						cout << "left:" << condition_array[i].Left << " " << condition_array[i].op << " " << condition_array[i].Right << endl;
					}
				}
				else {
					for (int i = 0; i < attr_name.size(); i++) {
						cout << "table_name:" << table_name << endl;
						for (int j = 0; j < condition_array.size(); j++) {
							cout << "left:" << condition_array[j].Left << " " << condition_array[j].op << " " << condition_array[j].Right << endl;
						}
					}

				}
				return 1;
			}
		}
		else if (strcmp(word.c_str(), "delete") == 0)
		{
			string table_name = "";
			word = get_word(command, index);
			if (strcmp(word.c_str(), "from") != 0) { cout << "Syntax Error!" << endl; return 0; }
			word = get_word(command, index);
			if(word.empty()) { cout << "Syntax Error!" << endl; return 0; }
			else table_name = word;
			word = get_word(command,index);
			if (word.empty()) {
				//调用api的delete from A
				return 1;
			}
			else if (strcmp(word.c_str(), "where") == 0) {
				string attribute_left = "";
				string attribute_right = "";
				vector<Condition> condition_array;
				int op;
				word = get_word(command, index);
				while (true) {
					if (!word.empty()) {
						attribute_left = word;
						word = get_word(command, index);
						if (op_for_sure(word, op) == 0)return 0;
						word = get_word(command, index);
						if (word.empty()) { cout << "Syntax Error!" << endl; return 0; }
						else attribute_right = word;
						Condition temp(attribute_left, attribute_right, op);
						condition_array.push_back(temp);
						word = get_word(command, index);
						if (word.empty()) { break; }
						else if (strcmp(word.c_str(), "and") != 0) { cout << "Syntax Error!" << endl; return 0; }
						word = get_word(command, index);
					}
					else { cout << "Syntax Error!" << endl; return 0; }
				}//调用delete from a where condition
				return 1;
			}
			
		}
		else if (strcmp(word.c_str(), "drop") == 0)
		{
			word = get_word(command, index);
			if (strcmp(word.c_str(), "table") == 0) {
				word = get_word(command, index);
				if (!word.empty()) {
					//调用api的drop table
					cout << "you just called the drop table:" << word << endl;
					return 1;
				}
				else { cout << "Syntax Error!" << endl; return 0; }
			}
			else if (strcmp(word.c_str(), "index") == 0) {
				word = get_word(command, index);
				if (!word.empty()) {
					//调用drop index
					cout << "you just called the drop index: " << word << endl;
					return 1;
				}
				else { cout << "Syntax Error!" << endl; return 0; }
			}
			else { cout << "Syntax Error!" << endl; return 0; }
		}
		else if (strcmp(word.c_str(), "quit") == 0)return quit;
		else if (strcmp(word.c_str(), "commit") == 0)return 1;
		else if (strcmp(word.c_str(), "execfile") == 0) {
			file = get_word(command, index);
			cout << "opening: " << file << endl;
			return 1;
		}
		else {
			if(!word.empty()) { cout << "Syntax Error!" << endl; return 0; }
			return 0;
		}
		
		return 0;
}
string Interpreter::get_word(string s, int &index) {
	string w;
	while ((s[index] == ' ' || s[index] == 10 || s[index] == '\t') && s[index] != 0)
	{
		index++;
	}
	int beginword = index;
	int lastword = beginword;
	if (s[index] == '(' || s[index] == ',' || s[index] == ')') {
		index++;
		lastword = index;
		return s.substr(beginword, lastword - beginword);
	}
	else if (s[index] == '\'') {
		index++;
		while (s[index] != '\''&&s[index] != 0)index++;
		if (s[index] == '\'') {
			beginword++;
			lastword = index;
			index++;
			return s.substr(beginword, lastword - beginword);
		}
		else {
			return "";
		}
	}
	else {
		while (s[index] != ' '&&s[index] != '('&&s[index] != ','&&s[index] != ')'&&s[index] != 10 && s[index] != 0) {
			index++;
		}
		lastword = index;
		if (beginword != lastword)return s.substr(beginword, lastword - beginword);
		else return "";
	}
}
Interpreter::~Interpreter()
{
}
