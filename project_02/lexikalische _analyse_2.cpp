// k7scan1.cpp //

#include "stdafx.h"
#pragma warning(disable:4786)
#include <iostream>
#include <string>
#include <fstream> 
#include <stdio.h>
#include <map>
#include <deque>
#include <vector>

using namespace std;
#define Getc(s) getc(s)
#define Ungetc(c) {ungetc(c,IP_Input); ugetflag=1;}
/*
* Lexical analyzer states.
*/


enum lexstate {
	L_START, L_INT, L_IDENT, L_STRING, L_STRING2,
	L_COMMENT, L_TEXT_COMMENT, L_LINE_COMMENT, L_END_TEXT_COMMENT,NET
};

enum stages {
	Empty, Start, Net, bracket, coordinate, comma, Done
};

const int STRING1 = 3;
const int IDENTIFIER = 4;
const int INTEGER1 = 5;
const int TOKENSTART = 300;

class CParser
{
public:
	string yytext;					//input buffer
	vector<string> node_buffer;
	int left_coordinate;
	int right_coordinate;

	struct tyylval {				//value return structure
		string s;					//string
		int i;						//integer
	}yylval;
	FILE* IP_Input;					//Input File
	FILE* IP_Error;					//Error Output
	FILE* IP_List;					//List Output
	int IP_LineNumber;				//Line counter
	int ugetflag;					//checks ungets
	int prflag;						//controls printing
	map<string, int> IP_Token_table;	//Tokendefinitions
	map<int, string> IP_revToken_table; //reverse Tokendefinitions
	int yylex();						//lexical analyser
	void yyerror(char* ers);			//error reporter
	void create_node(string name, int x, int y);
	void create_grid(int x, int y);
	void error_detected(int x, int y);
	int IP_MatchToken(string& tok);	
	void InitParse(FILE* inp, FILE* err, FILE* lst);	//Sets the File pointers
	int yyparse();										//parser
	void pr_tokentable();											//test output for tokens
	void IP_init_token_table();										//loads the tokens
	void Load_tokenentry(string str, int index);					//load one token
	void PushString(char c);										//Used for dtring assembly
	CParser() { IP_LineNumber = 1; ugetflag = 0; prflag = 0; };		//Constructor
};
//------------------------------------------------------------------------
// Adds a character to the string value
void CParser::PushString(char c)
{
	yylval.s += c;
}
//------------------------------------------------------------------------
void CParser::create_node(string name, int x, int y)
{
	
}
void CParser::create_grid(int x, int y)
{

}
void CParser::error_detected(int x, int y)
{

}

//------------------------------------------------------------------------
void CParser::Load_tokenentry(string str, int index)
{
	IP_Token_table[str] = index;
	IP_revToken_table[index] = str;
}
void CParser::IP_init_token_table()
{
	Load_tokenentry("STRING1", 3);
	Load_tokenentry("IDENTIFIER", 4);
	Load_tokenentry("INTEGER1", 5);

	int ii = TOKENSTART;
	Load_tokenentry("NET", ii++);
	Load_tokenentry("size", ii++);
	Load_tokenentry("OR", ii++);
	Load_tokenentry("Begin", ii++);
	Load_tokenentry("End", ii++);
}
//------------------------------------------------------------------------
void CParser::pr_tokentable()
{
	typedef map<string, int>::const_iterator CI;
	const char* buf;
	printf("Symbol Table ---------------------------------------------\n");
	for (CI p = IP_Token_table.begin(); p != IP_Token_table.end(); ++p) {
		buf = p->first.c_str();
		printf(" key:%s val:%d\n ", buf, p->second);
	}
}
//------------------------------------------------------------------------
int CParser::yyparse()
{
	int tok;
	int ind = 1;
	int line = 1;
	int coordinates[2] = { 0,0 };
	int flag=0;

	string word, name;

	stages c_stage = Empty;
	stages f_stage = Empty;

	if (prflag)fprintf(IP_List, "%5d ", (int)IP_LineNumber);
	/*
	* Go parse things!
	*/
	while ((tok = yylex()) != 0) {

			
		if (tok == STRING1) {
			//printf("%s %s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
			cout << yylval.s.c_str() << "\t";
		}
		else {
			if (tok == INTEGER1) {
				//printf("%s %d ", IP_revToken_table[tok].c_str(), yylval.i);
				cout << yylval.i << "\t";
			}
			else
				if (tok == IDENTIFIER)
				{
					//printf("%s %s ", IP_revToken_table[tok].c_str(), yylval.s.c_str());
					cout << yylval.s.c_str() << "\t";
				}
				else
					if (tok >= TOKENSTART) {
						printf("%s \t", IP_revToken_table[tok].c_str());
					}
					else{
						//printf("%c ", tok);
					}
		}
		if (line != (int)IP_LineNumber) {
			f_stage = Empty;
			c_stage = Empty;
			line = (int)IP_LineNumber;
		}
		// In order for the Nodes to pass, every line has to fit certain parameter
		// Every valid node has to be:
		// NET -> Nxxx -> ( -> xxx -> , -> xxx -> )
		// the size parameter:
		// size -> ( -> xxx -> , -> xxx -> )
		switch (c_stage) {
	
		case Empty:
			if (tok == 300)	//NET
			{
				c_stage = Net;
				flag = 1;
			}
			else if (tok == 301)// size
			{
				f_stage = Net;
				c_stage = bracket;
				flag = 0;
			}
			else {
				cout << " not valid" << endl;
			}
			break;

		case Net:
			word = yylval.s.c_str();
			name = word;
			if (word[0] == 'N')
			{
				ind = 1;
				int pos = 0;
				while (word[ind] != '\0')
				{	
					if (isdigit(word[ind]))
					{
						f_stage = Net;
						c_stage = bracket;
						name[pos] = word[ind];
						pos++;
					}
					else if (isspace(word[ind]))
					{
						f_stage = Net;
						c_stage = bracket;
					}
					else
					{
						f_stage = Empty;
						c_stage = Empty;
						cout << " not valid" << endl;
						break;
					}
					ind++;
				}
				name[pos] = '\0';
				//cout << name;
			}
			else {
				f_stage = Empty;
				c_stage = Empty;
				cout << " not valid" << endl;
			}
			break;

		case bracket:

			word = tok;
			if (word[0] == '(')
			{
				if (f_stage == Net) {
					c_stage = coordinate;
					f_stage = bracket;
				}
				if (f_stage == coordinate) {
					c_stage = Done;
					f_stage = Empty;
				}
			}
			else if (word[0] == ')')
			{
				if (f_stage == Net) {
					c_stage = coordinate;
					f_stage = bracket;
				}
				if (f_stage == coordinate) {
					c_stage = Empty;
					f_stage = Empty;

					if (flag) {
						create_node(name, coordinates[0], coordinates[1]);	
						cout << "node detected";
						cout << endl;
					}
					else {

						create_grid(coordinates[0], coordinates[1]);
						cout << "grid detected";
						cout << endl;
					}					
				}
			}
			else
			{
				c_stage = Empty;
				f_stage = Empty;
				cout << " not valid" << endl;
			}
			break;

		case coordinate:
			
			if( tok == INTEGER1) {
				if (f_stage == bracket) {
					coordinates[0] = yylval.i;
					c_stage = comma;
					f_stage = coordinate;
				}
				if (f_stage == comma) {
					coordinates[1] = yylval.i;
					c_stage = bracket;
					f_stage = coordinate;
				}				
			}
			else
			{
				c_stage = Empty;
				f_stage = Empty;
				cout << " not valid" << endl;
			}
			break;

		case comma:
			word = tok;
			if (word[0] == ',') {
				c_stage = coordinate;
				f_stage = comma;				
			}
			else {
				c_stage = Empty;
				f_stage = Empty;
				cout << " not valid" << endl;
			}
			break;
		}
	//if (!prflag)printf("\n");
	}
	return 0;
}
//------------------------------------------------------------------------
/*
* Parse Initfile:
* This builds the name table for the key words.
* It is passed three file streams, the first is where the input comes
* from; the second is where error messages get printed
*. The third is used to generate a list file
*/
//------------------------------------------------------------------------
/*
* yyerror:
* Standard error reporter, it prints out the passed string
* preceeded by the line number.
*/
void CParser::yyerror(char* ers)
{
	fprintf(IP_Error, "line %d: %s\n", IP_LineNumber, ers);
}
//------------------------------------------------------------------------

void CParser::InitParse(FILE* inp, FILE* err, FILE* lst)
{
	/*
	* Set up the file state to something useful.
	*/
	IP_Input = inp;
	IP_Error = err;
	IP_List = lst;
	IP_LineNumber = 1;
	ugetflag = 0;
	/*
	* Define both the enabled token and keyword strings.
	*/
	IP_init_token_table();
}
//------------------------------------------------------------------------
int CParser::IP_MatchToken(string& tok)
{
	int retval;
	if (IP_Token_table.find(tok) != IP_Token_table.end()) {
		retval = (IP_Token_table[tok]);
	}
	else {
		retval = (0);
	}
	return retval;
}
//------------------------------------------------------------------------
/*
* yylex:
*
*/
int CParser::yylex()
{
	//Locals
	int c;
	string line;
	lexstate s;
	/*
	* Keep on sucking up characters until we find something which
	* explicitly forces us out of this function.
	*/

	for (s = L_START, yytext = ""; 1;) {

		c = Getc(IP_Input);
		yytext = yytext + (char)c;

		if (!ugetflag) {
			if (c != EOF)if (prflag)fprintf(IP_List, "%c", c);
		}
		else ugetflag = 0;
		switch (s) {
			//Starting state, look for something resembling a token.
		case L_START:
			if (isdigit(c)) {
				s = L_INT;
			}
			else if (isalpha(c) || c == '\\') {
				s = L_IDENT;
			}
			else if (isspace(c)) {
				if (c == '\n') {
					IP_LineNumber += 1;
					if (prflag)
						fprintf(IP_List, "%5d ", (int)IP_LineNumber);
				}
				yytext = "";
			}
			else if (c == '/') {
				yytext = "";
				s = L_COMMENT;
			}
			else if (c == '"') {
				s = L_STRING;
			}
			else if (c == EOF) {
				return ('\0');
			}
			else {
				return (c);
			}
			break;
		case L_COMMENT:
			if (c == '/')
				s = L_LINE_COMMENT;
			else if (c == '*')
				s = L_TEXT_COMMENT;
			else {
				Ungetc(c);
				return('/'); /* its the division operator not a comment */
			}
			break;
		case L_LINE_COMMENT:
			if (c == '\n') {
				s = L_START;
				Ungetc(c);
			}
			yytext = "";
			break;
		case L_TEXT_COMMENT:
			if (c == '\n') {
				IP_LineNumber += 1;
			}
			else if (c == '*')
				s = L_END_TEXT_COMMENT;
			yytext = "";
			break;
		case L_END_TEXT_COMMENT:
			if (c == '/') {
				s = L_START;
			}
			else {
				s = L_TEXT_COMMENT;
			}
			yytext = "";
			break;
			/*
			* Suck up the integer digits.
			*/
		case L_INT:
			if (isdigit(c)) {
				break;
			}
			else {
				Ungetc(c);
				yylval.s = yytext.substr(0, yytext.size() - 1);
				yylval.i = atoi(yylval.s.c_str());
				return (INTEGER1);
			}
			break;
			/*
			* Grab an identifier, see if the current context enables
			* it with a specific token value.
			*/
		case L_IDENT:
			if (isalpha(c) || isdigit(c) || c == '_') break;
			Ungetc(c);
			yytext = yytext.substr(0, yytext.size() - 1);
			yylval.s = yytext;
			if (c = IP_MatchToken(yytext)) {
				return (c);
			}
			else {
				return (IDENTIFIER);
			}
			/*
			* Suck up string characters but once resolved they should
			* be deposited in the string bucket because they can be
			* arbitrarily long.
			*/
		case L_STRING2:
			s = L_STRING;
			if (c == '"') {
				PushString((char)c);
			}
			else {
				if (c == '\\') {
					PushString((char)c);
				}
				else {
					PushString((char)'\\');
					PushString((char)c);
				}
			}
			break;
		case L_STRING:
			if (c == '\n')
				IP_LineNumber += 1;
			else if (c == '\r')
				;
			else if (c == '"' || c == EOF) {
				return (STRING1);
			}
			else if (c == '\\') {
				s = L_STRING2;
			}
			else
				PushString((char)c);
			break;
		default: printf("***Fatal Error*** Wrong case label in yylex\n");
		}
	}
}
int main(int argc, char* argv[])
{
	FILE* inf;
	char fistr[100] = "greedy_router_nodes.txt";
	int err;

	//cout << "Enter filename:\n";
	//cin >> fistr;

	err = fopen_s(&inf, fistr, "r");
	if (err) {
		printf("Cannot open input file %s\n", fistr);
		return 0;
	}

	CParser obj;
	obj.InitParse(inf, stderr, stdout);
	//obj.pr_tokentable();
	obj.yyparse();
	return 0;
}
