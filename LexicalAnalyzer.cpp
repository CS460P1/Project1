/*
  File: LexicalAnalyzer.cpp
  Authors: Brandon Williams, John Salman, Nick Ivanoff
  Class: CS460 Fall 2018
  Description: This is the implementation of the LexicalAnalyzer class, this class is designed
               to tokenize scheme code from a source file and output files containing the lines
	       of input and errors within those lines, debugging information, and the lexemes with
	       their interpreted token type.
*/

#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"
#include "transition.hpp"
#include <fstream>

using namespace std;

/*
  Object: token_names[]
  Description: This is an array that can be indexed to return the name of a token type.
*/
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

/*
  Function: LexicalAnalyzer()
  Parameters: c-style string representing the name of a file.
  Return: NA
  Description: Constructor for LexicalAnalyzer class, instantiates the private variables, writes the file name
               to the listing file, and populates the hash table used to identify keywords, predicates, and 
	       arithmetic keywords.
*/
LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	// This function will initialize the lexical analyzer class
	input.open(filename);
	listingFile.open("P1-1.lst");
	tokenFile.open("P1-1.p1");
	debugFile.open("P1-1.dbg");

	line = "";
	linenum = 0; 
	pos = 0;
	lexeme = "";
	errors = 0;

	fillTokenMap();
	listingFile << "Input File: " << filename << endl;

}

/*
  Function: ~LexicalAnalyzer()
  Parameters: none
  Return: NA
  Description: Default destructor for LexicalAnalyzer class, primarily exists to close the input/output stream.
 */
LexicalAnalyzer::~LexicalAnalyzer ()
{
	// This function will complete the execution of the lexical analyzer class
	input.close();
	listingFile.close();
	tokenFile.close();
	debugFile.close();
}


/*
  Function: GetToken()
  Parameters: none
  Return: token_type associated with a lexeme
  Description: The function utilizes a DFA to tokenize the next lexeme in the source file, identify the type of the token
               and return said type. In also writes to the listing and token file with the lexemes and their corresponding
	       types.
*/
token_type LexicalAnalyzer::GetToken ()
{
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
	int prevState = 0;
	int col = 0;
	int state = 0;
	while(pos < line.length()){
		state = 0;
		lexeme = "";
		//if a comment is the first thing we find on a line, skip the line
		if (line[pos] == ';') {
			line = "";
		}
		while(state < 100 && pos < line.length()){	
			//if a comment is found part way through a line, skip the rest of the line
			if (line[pos] == ';') {
				line = "";
			}

			col = getCol(line[pos]);
			//if we have not hit a SPACE, ERR2, ERR, BU, or, GD state
			if(col < 100){	
				prevState = state;
				state = table[state][col];
			}

			else{
				prevState = state;
				state = col;
			}

			if(state != BU && state != 0){
				//this handles the case if we are in a string, we want to add the 
				//closing quote to the lexeme
				if(state == 11 && col == 31){
					lexeme += line[pos];
				}
				//only add to the lexeme if line[pos] is not a quote, this is because we 
				//are not in a string
				else if(col != 31){
					lexeme += line[pos];
				}

			}
			pos++;

		}

		if(state == ERR){
			errors++;
			token = ERROR_T;
			ReportError(lexeme);
			return token;
		}
		
		//an error with a backup
		if(state == ERR2){
			errors++;
			pos--;
			ReportError(lexeme);
			return ERROR_T;
		}

		if(state == BU){
			pos--;
			token = GetTokenType(prevState);
			string token_name = GetTokenName(token);
			if(token_name == "IDENT_T" && lexeme[lexeme.length() - 1] == '?'){
			  lexeme.pop_back();
			  token = GetTokenType(prevState);
			  token_name = GetTokenName(token);
			  pos--;
			}
			tokenFile << token_name << "   " << lexeme << endl;
			return token;
		}

		else if(state == GD){
			token = GetTokenType(prevState);
			tokenFile << GetTokenName(token) << "   " << lexeme << endl;
			return token;
		}

		//means we reached the end of a lexeme, and we want to get the token type from the previous state that got
		//us to the SPACE state. 
		else if(state == SPACE){
		  
		  token = GetTokenType(prevState);
		  string token_name = GetTokenName(token);
		  //cout << "Testing: " << token_name << lexeme  << endl;
		  if(token_name == "IDENT_T" && lexeme[lexeme.length() - 1] == '?'){
		    lexeme.pop_back();
		    token = GetTokenType(prevState);
		    token_name = GetTokenName(token);
		    pos-=2;
		  }
		  tokenFile << token_name << "   " << lexeme << endl;
		  return token;
		}


	}
	//at this point we have reached the end of the line but have not reached an ERR, ERR2, BU, GD, or SPACE state. 
	//though we might still have a valid lexeme that needs its token found and written to the token file. 
	token = GetTokenType(state); // CHANGED TO STATE FROM PREVSTATE
	if(token == ERROR_T){
		errors++;
		ReportError(lexeme);
		return token;

	}
	else if(state != 0){
		tokenFile << GetTokenName(token) << "   " << lexeme << endl;
		return token;
	}	

}

/*
  Function: GetTokenName()
  Parameters: the type of a token
  Return: A string that identifies the name of a type of token
  Description: The GetTokenName function returns a string containing the name of the                                                                                                                                                 token passed to it.  
 */
string LexicalAnalyzer::GetTokenName (token_type t) const
{
	return token_names[t];
}

/*
  Function: GetLexeme()
  Parameters: none
  Return: the value in the private variable "lexeme"
  Description: A getter function to access the private variable "lexeme" stored within the 
               LexicalAnalyzer.
 */
string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return lexeme;
}

/*
  Function: ReportError()
  Parameters: a reference to a string constant
  Return: void
  Description: This function will be called to write an error message to a file       
 */
void LexicalAnalyzer::ReportError (const string & msg)
{
        if(lexeme[0] == '"'){ // if there is no end to the string literal
		listingFile << "Error at " << linenum << "," << pos << " no closing quote on string " << lexeme << endl;
		tokenFile << GetTokenName(token) << "   " << lexeme << endl; 
	}
	
	else{
	  listingFile << "Error at " << linenum << "," << pos << " invalid character found: " << line[pos-1] << endl;
	  tokenFile << GetTokenName(token) << "   " << lexeme << endl;
	}
}

/*
  Function: GetTokenType
  Parameters: an accepting state that is given by GetToken
  Return: Token
  Description: This function is designed to return the token associated with a particular lexeme or accepting state.
  It first searches through a hash map of predefined lexemes and their corresponding token, if it is not
  found then it will return the token based on accepting state. 
*/
token_type LexicalAnalyzer::GetTokenType(int acceptingState){
	//at this point we will check the hashmap for the lexeme we have. if found return the corresponding
	//token
	std::unordered_map<string, int>::const_iterator got = myTokenMap.find(lexeme);
	if(got != myTokenMap.end()){
		return (token_type)got->second;
	}
	//not found in my token map so check acceptingstates
	else{
		if(acceptingState == 10){
			return LISTOP_T;
		}
		else if(acceptingState == 11){
			if(lexeme[lexeme.length()-1] != '"'){
				return ERROR_T;
			}
			else return STRLIT_T;
		}
		else if(acceptingState == 1){
			return IDENT_T;
		}
		else if(acceptingState ==2 || acceptingState == 4 || acceptingState ==3){
			return NUMLIT_T;
		}
	}
}

/*
  Function: fillTokenMap
  Parameters: none 
  Return: void
  Description: this function will fill a hash map with predefined lexemes and their corresponding tokens. 
*/
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

/*
  Function: WriteErrors()
  Parameters: none
  Return: void
  Description: This function writes the number of errors found in the source file to the listing file.
 */
void LexicalAnalyzer::WriteErrors(){
  // NOTE: this function is called within SyntacticalAnalyzer.cpp after an EOF token is encountered.
	listingFile << errors << " errors found in input file" << endl;
}

