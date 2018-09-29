#include <iomanip>
#include <cstdlib>
#include "LexicalAnalyzer.h"

using namespace std;

static string token_names[] = {	"EOF_T" }; 

LexicalAnalyzer::LexicalAnalyzer (char * filename)
{
	input.open(filename);
	listingFile("P1-0.lst", ofstream::out);
	tokenFile("P1-0.p1", ofstream::out);
	debugFile("P1-0.dbg", ofstream::out);  


	// This function will initialize the lexical analyzer class
}

LexicalAnalyzer::~LexicalAnalyzer ()
{
	input.close();
	listingFile.close();
	tokenFile.close();
	debugFile.close();
	// This function will complete the execution of the lexical analyzer class
}

token_type LexicalAnalyzer::GetToken ()
{
	// This function will find the next lexeme in the input file and return
	// the token_type value associated with that lexeme
	getline(input, line);
	linenum++;
	listingFile << linenum << ": " << line << endl; 
	
	//TODO- INCOMPLETE//
	//find the next token
	while(pos < line.length()){
		//put line[pos] into a dfa table search and increment pos as appropriate
		//if we find a valid token then break loop, write to tokenfile and return (see below), 
		pos++
	}
	//if we never find a token at this point that means we read the entire line and didnt find anything,
	//so that's an error

	/*This splits a string up where there is spaces. can be deleted if not useful
	
	string word;
	istringstream iss(line);
	while(iss >> word);
	*/
	

	/*
	once we find a token, call find GetLexeme, 
	and print in token file the token followed by the corresponding lexeme.

	create a hash with <int, string> structure so we can print to the token file in string.
	this should be done in a global scope outside of the function 
	e.g: 
		std::unordered_map<std::string,double> mymap = {
     			{0,"CONS_T"};

	*/

	int IntValueOfToken = token; 
	std::unordered_map<int, string>::const_iterator got = mymap.find (IntValueOfToken);
	if ( got != mymap.end() )
    		tokenFile << got->second;

	lexeme = getLexeme(token);
	tokenFile << lexeme << endl;
	return token;
}

string LexicalAnalyzer::GetTokenName (token_type t) const
{
	// The GetTokenName function returns a string containing the name of the
	// token passed to it. 

	return "";
}

string LexicalAnalyzer::GetLexeme () const
{
	// This function will return the lexeme found by the most recent call to 
	// the get_token function
	return "";
}

void LexicalAnalyzer::ReportError (const string & msg)
{
	// This function will be called to write an error message to a file
}

int LexicalAnalyzer::getCol(char c) {
    switch (c)
    {
        case '_':
            return underscore;
            
        case '+':
            return plusOperator;
            
        case '=':
            return equalityOperator;
            
        case '%':
            return percent;
            
        case '&':
            return ampersand;
            
        case '*':
            return asterisk;
            
        case ']':
            return encloseBracket;
            
        case '[':
            return openBracket;
            
        case ')':
            return encloseParen;
            
        case '(':
            return openParen;
            
        case '.':
            return period;
            
        case '/':
            return forwardSlash;
            
        case '?':
            return questionMark;
            
        case '!':
            return exclamationMark;
            
        case ':':
            return colon;
            
        case ',':
            return comma;
            
        case '-':
            return dash;
            
        case '>':
            return greaterThan;
            
        case '|':
            return pipe;
            
        case '<':
            return lessThan;
            
        case '~':
            return tilde;
            
        case '^':
            return carrot;

        default:
            if (isdigit(c)) {
                return digit;
                
            } else if (isalpha(c)) {
                return alpha;
                
            }
    
            return BU;
    }
}
