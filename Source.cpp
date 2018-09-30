#include<iostream>
#include<fstream>
#include<string.h>
#include<ctype.h>
#include<string>
//#include<stdlib.h>

using namespace std;

#define DATA 20
string removeComments(string prgm);
void removeSpaces(string text);

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
	char final_file[1000];
	
	int j = 0, repeat = 0;
	int id = 0, key = 0, con = 0, ope = 0, f = 0;
	string full_file = "";
	string after_space_file = "";
	string after_comment_file = "";
	string ident[DATA], keyword[DATA], constant[DATA], op[DATA];

	ifstream ff("program.txt");

	if (!ff.is_open()){
		cout << "error while opening the file\n";
		exit(0);
	}

	
	while (!ff.eof()){
		ch = ff.get();
		full_file = full_file + ch;
		f++;
	}
	
	cout << "\n\n\n";
	cout << full_file << endl;
	after_comment_file = removeComments(full_file);
	cout << "\n\n\n";
	removeSpaces(after_comment_file);

	ff.close();

	cout << "\n\n\n"; cout << "\n\n\n";

	ifstream fin("program.txt");

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

	fin.close();

	system("pause");
	return 0;
}



string removeComments(string prgm)
{
	int n = prgm.length();
	string res;

	bool s_cmt = false;
	bool m_cmt = false;



	for (int i = 0; i<n; i++)
	{
		// If single line comment flag is on, then check for end of it 
		if (s_cmt == true && prgm[i] == '\n')
			s_cmt = false;

		// If multiple line comment is on, then check for end of it 
		else if (m_cmt == true && prgm[i] == '*' && prgm[i + 1] == '/')
			m_cmt = false, i++;

		// If this character is in a comment, ignore it 
		else if (s_cmt || m_cmt)
			continue;

		// Check for beginning of comments and set the approproate flags 
		else if (prgm[i] == '/' && prgm[i + 1] == '/')
			s_cmt = true, i++;
		else if (prgm[i] == '/' && prgm[i + 1] == '*')
			m_cmt = true, i++;

		// If current character is a non-comment character, append it to res 
		else  res += prgm[i];
	}
	return res;
}

void removeSpaces(string text){
	char blank[1000];

	ofstream fout("program v2.txt");

	int c = 0, d = 0;

	while (text[c] != '\0')
	{
		if (!(text[c] == ' ' && text[c + 1] == ' ')) {
			blank[d] = text[c];
			d++;
		}
		c++;
	}

	blank[d] = '\0';
	cout << blank;


}
