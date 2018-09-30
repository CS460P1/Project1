#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"
#include "transition.hpp"
#include <fstream>

using namespace std;

static string token_names[] = {	
		"EOF_T", 
		"IDENT_T",
		"NUMLIT_T",
		"STRLIT_T",
		"LISTOP_T",
		"CONS_T",
		"IF_T",
		"COND_T",
		"ELSE_T",
		"DISPLAY_T",
		"NEWLINE_T",
		"AND_T",
		"OR_T",
		"NOT_T",
		"DEFINE_T",
		"NUMBERP_T",
		"LISTP_T",
		"ZEROP_T",
		"NULLP_T",
		"STRINGP_T",
		"PLUS_T",
		"MINUS_T",
		"DIV_T",
		"MULT_T",
		"MODULO_T",
		"ROUND_T",
		"EQUALTO_T",
		"GT_T",
		"LT_T",
		"GTE_T",
		"LTE_T",
		"LPAREN_T",
		"RPAREN_T",
		"SQUOTE_T",
		"ERROR_T",
		"EOF_T"};

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
	input.open(filename);
	listingFile.open("P1-0.lst");
	tokenFile.open("P1-0.p1");
	debugFile.open("P1-0.dbg");
	
	//listingFile("P1-0.lst", ofstream::out);
	//tokenFile("P1-0.p1", ofstream::out);
	//debugFile("P1-0.dbg", ofstream::out);  

	line = "";
	linenum = 0; 
	pos = 0;
	lexeme = "";
	errors = 0;

	token = GetToken();
	fillTokenMap();

}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
	input.close();
	listingFile.close();
	tokenFile.close();
	debugFile.close();
}

token_type LexicalAnalyzer::GetToken ()
{
	// This function will find the next lexeme in the input file and return
	// the token_type value associated with that lexeme

	if(line == ""){
		if(input.eof()){
			return EOF_T;
		}
		else{
			getline(input, line);
			listingFile << linenum << ": " << line << endl; 
			pos = 0;
			linenum++;
		}

	}	
	//else we are still processing the last read in line
	//we are finding a new lexeme
	lexeme = "";


	//TODO- INCOMPLETE//
	//find the next token
	int state = 0;
	int prevState = 0;
	int col = 0;
	while(pos < line.length()){
		//put line[pos] into a dfa table search and increment pos as appropriate
		//if we find a valid token then break loop, write to tokenfile and return (see below), 

		while(state != ERR || state != BU || state != GD){
			col = getCol(line[pos]);

			if(col != ERR || col != BU || col != GD) {
				prevState = state;
				state = table[state][col];	
			}

			else{
				state = col;
			}

			if(state != BU){
				lexeme += line[pos];
			}

			pos++;
		}
	
		//TODO: set proper width using iomanip

		if(state == ERR){
			//uhoh
			errors++;
			ReportError(lexeme);
			return ERROR_T;
		}

		if(state == BU){
			pos--;
			token = GetTokenType(prevState);
			tokenFile << GetTokenName(token) << "   " << lexeme << endl;
			return token;
		}

		else if(state == GD){
			//valid lexeme, leave pos
			token = GetTokenType(prevState);
			tokenFile << GetTokenName(token) << "   " << lexeme << endl;
			return token;
		}

	}
	//means we hit end of line, think 3.3, it never returns a GD, BU, or ERR state. still should be a valid lexeme though
	//
	token = GetTokenType(prevState);
	tokenFile << GetTokenName(token) << "   " << lexeme << endl;
	return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it. 
	return token_names[t];
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return lexeme;
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
	listingFile << "Error at " << linenum << "," << pos << " invalid character found: " << line[pos] << endl;

}

token_type LexicalAnalyzer::GetTokenType(int acceptingState){
	//check to see if we actually have a lexeme to check
	token = enumIdentifierNumber();
	if(token == 0){
		//must be IDENT, NUMLIT, STRLIT, OR LISTOP, find which one based off the state number that returned a GD or BU
		if(acceptingState == 10){
			return LISTOP_T;
		}
		else if(acceptingState == 11){
			return STRLIT_T;
		}
		else if(acceptingState == 1){
			return IDENT_T;
		}
		else if(acceptingState == 4){
			return NUMLIT_T;
		}
	}
	//else we found a token in our hash table. 
	else return token;	
}
void fillTokenMap(){
	myTokenMap.insert({
		{"cons", 5},
		{"if",6},
		{"cond",7},
		{"else",8},
		{"display",9},
		{"newline",10},
		{"and", 11},
		{"or",12},
		{"not",13},
		{"define",14},
		{"number?",15},
		{"list?",16},
		{"zero?",17},
		{"null?",18},
		{"string?",19},
		{"+",20},
		{"-",21},
		{"/",22},
		{"*",23},
		{"modulo",24},
		{"round",25},
		{"=",26},
		{">",27},
		{"<",28},
		{">=",29},
		{"<=",30},
		{"(",31},
		{")",32},
		{"'",33}
		});
		/*
*/

}
//Given a lexeme in string format, will return the number associated with the enumerated token_type.
//does this by using an unordered hash map. 
int enumIdentifierNumber(){
	std::unordered_map<string, int>::const_iterator got = myTokenMap.find(lexeme);
	if(got != myTokenMap.end()){
		return got->second;
	}
	else return 0;
}
