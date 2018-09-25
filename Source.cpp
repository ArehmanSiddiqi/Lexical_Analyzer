#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<string>

using namespace std;

int isKeyword(char buffer[]){
	char keywords[32][9] = { "auto", "break", "case", "char", "const", "continue", "default",
		"do", "double", "else", "enum", "extern", "float", "for", "goto",
		"if", "int", "long", "register", "return", "short", "signed",
		"sizeof", "static", "struct", "switch", "typedef", "union",
		"unsigned", "void", "volatile", "while" };
	int i, flag = 0;

	for (i = 0; i < 32; ++i){
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
	for (int i = 0; i < string_len; ++i) {	// checking if char array is number
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
	char ch, buffer[15], operators[] = "+-*/%=", braket[] = "{}[]()", terminator = ';';
	ifstream fin("program.txt");
	int i, j = 0;

	if (!fin.is_open()){
		cout << "error while opening the file\n";
		exit(0);
	}

	while (!fin.eof()){
		ch = fin.get();

		if (ch == terminator)
		{
			cout << ch << " is terminator\n";
		}

		for (i = 0; i < 6; ++i){    // 6 operators in string match with each one
			if (ch == operators[i])
				cout << ch << " is operator\n";
		}
	

		if (isalnum(ch)||(ch=='.')){
			buffer[j++] = ch;
		}
		else if ((ch == ' ' || ch == '\n') && (j != 0)){
			buffer[j] = '\0';
			j = 0;

			if (isKeyword(buffer) == 1)
				cout << buffer << " is keyword\n";
			else if (isNumber(buffer) == 1)
				cout << buffer << " is Constant\n";
			else if (!isdigit(buffer[0]))
				cout << buffer << " is indentifier\n";
			else
				cout << "Unknown"

		}

	}

	fin.close();

	system("pause");
	return 0;
}