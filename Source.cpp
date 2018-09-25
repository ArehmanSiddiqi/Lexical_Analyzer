#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<string>

using namespace std;

#define DATA 20

int isKeyword(char buffer[]){
	char keywords[35][9] = { "auto", "break", "case", "char", "const", "continue", "default",
		"do", "double", "else", "enum", "extern", "float", "for", "goto",
		"if", "int", "long", "register", "return", "short", "signed",
		"sizeof", "static", "struct", "switch", "typedef", "union",
		"unsigned", "void", "volatile", "while", "system", "pause", "cout" };
	int i, flag = 0;

	for (i = 0; i < 35; ++i){
		if (strcmp(keywords[i], buffer) == 0){
			flag = 1;
			break;
		}
	}

	return flag;
}

int isNumber(char buffer[])
{
	int dotFlag = 0;

	int string_len = strlen(buffer);
	for (int i = 0; i < string_len; ++i) {	
		if (buffer[i] == '.') dotFlag = dotFlag + 1;
		if (dotFlag >= 2) return 0;
		if (!(isdigit(buffer[i]) || (buffer[i] == '.')))
		{
			return 0;
		}		
	}
	return 1;
}


int main(){
	char ch, buffer[15];
	ifstream fin("program.txt");
	int j = 0, repeat = 0;
	int id = 0, key = 0, con = 0, ope = 0;

	string ident[DATA], keyword[DATA], constant[DATA], op[DATA];

	if (!fin.is_open()){
		cout << "error while opening the file\n";
		exit(0);
	}

	while (!fin.eof()){
		ch = fin.get();
		repeat = 0;

		if (isalnum(ch)||(ch=='.')){
			buffer[j++] = ch;
		}
		else if ((ch == ' ' || ch == '\n') && (j != 0)){
			buffer[j] = '\0';
			j = 0;

			if (isKeyword(buffer) == 1)
			{
				cout << buffer << " is keyword\n";
				for (int i = 0; i <= key; i++)
				{
					if (keyword[i] == buffer)
						repeat = 1;
				}
	
				if (repeat == 0)
				{
					keyword[key] = buffer;
					key++;
				}

			}
			else if (isNumber(buffer) == 1)
			{
				cout << buffer << " is Constant\n";
				constant[con] = buffer;
				con++;
			}
			else if (!isdigit(buffer[0]))
			{
				cout << buffer << " is indentifier\n";

				for (int i = 0; i <= id; i++)
				{
					if (ident[i] == buffer)
						repeat = 1;
				}

				if (repeat == 0)
				{
					ident[id] = buffer;
					id++;
				}
			}
			else
				cout << buffer << "Unknown" << endl;
		}

	}

	cout << "\n\n\n\n\n";

	cout << ":::IDENTIFIERS:::" << endl;
	for (int i = 0; i < id; i++)
	{
		cout << i << " = " << ident[i] << endl;
	}

	cout << ":::CONSTANTS:::" << endl;
	for (int i = 0; i < con; i++)
	{
		cout << i << " = " << constant[i] << endl;
	}

	cout << ":::KEYWORDS:::" << endl;
	for (int i = 0; i < key; i++)
	{
		cout << i << " = " << keyword[i] << endl;
	}

	cout << "\n\n\n\n\n";

	fin.close();

	system("pause");
	return 0;
}