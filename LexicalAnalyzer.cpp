#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"
#include "transition.hpp"
#include <fstream>

using namespace std;

static string token_names[] = {	
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

	line = "";
	linenum = 0; 
	pos = 0;
	lexeme = "";
	errors = 0;

	fillTokenMap();
	listingFile << "Input File: " << filename << endl;

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

	if(line == "" || pos >= line.length()){
		if(!getline(input, line)){
			tokenFile << GetTokenName(EOF_T) << endl; 
			return EOF_T;
		}
		listingFile << linenum + 1 << ": " << line << endl; 
		pos = 0;
		linenum++;

	}	
	lexeme = "";

	int stattablee = 0;
	int prevState = 0;
	int col = 0;
	int state;
	while(pos < line.length()){

		state = 0;
		lexeme = "";
		
		while(state < 100){	
			col = getCol(line[pos]);
	
			if(col < 100){	
				prevState = state;
				state = table[state][col];
			}

			else{
				prevState = state;
				state = col;
			}

			if(state != BU){
				
				if(state == 11 && col == 31){
					lexeme += line[pos];
				}
				else if(col != 31){
				       lexeme += line[pos];
				}
				
			}
			pos++;

		}


		//TODO: set proper width using iomanip

		if(state == ERR){
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
			token = GetTokenType(prevState);
			tokenFile << GetTokenName(token) << "   " << lexeme << endl;
			return token;
		}
		
		else if(state == SPACE){
			token = GetTokenType(prevState);
			tokenFile << GetTokenName(token) << "   " << lexeme << endl;

			return token;
		}
		
		
		}
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
		listingFile << "Error at " << linenum << "," << pos << " invalid character found: " << line[pos-1] << endl;

	}

	token_type LexicalAnalyzer::GetTokenType(int acceptingState){
		std::unordered_map<string, int>::const_iterator got = myTokenMap.find(lexeme);
		if(got != myTokenMap.end()){
			return (token_type)got->second;
		}
		else{//not found in my token map so check acceptingstates
			if(acceptingState == 10){
				return LISTOP_T;
			}
			else if(acceptingState == 11){
				return STRLIT_T;
			}
			else if(acceptingState == 1){
				return IDENT_T;
			}
			else if(acceptingState ==2 || acceptingState == 4 || acceptingState ==3){
				return NUMLIT_T;
			}
		}
	}

	void LexicalAnalyzer::fillTokenMap(){
		myTokenMap.insert({
				{"cons", 4},
				{"if",5},
				{"cond",6},
				{"else",7},
				{"display",8},
				{"newline",9},
				{"and", 10},
				{"or",11},
				{"not",12},
				{"define",13},
				{"number?",14},
				{"list?",15},
				{"zero?",16},
				{"null?",17},
				{"string?",18},
				{"+",19},
				{"-",20},
				{"/",21},
				{"*",22},
				{"modulo",23},
				{"round",24},
				{"=",25},
				{">",26},
				{"<",27},
				{">=",28},
				{"<=",29},
				{"(",30},
				{")",31},
				{"'",32}
		});
	}
	
