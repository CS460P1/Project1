/*
  File: LexicalAnalyzer.h
  Authors: Brandon Williams, John Salman, Nick Ivanoff
  Class: CS460 Fall 2018
  Description: Header file containing defintions for LexicalAnalyzer class methods and variables. Implementations
               can be found in LexicalAnalyzer.cpp.
 */
#ifndef LEX_H
#define LEX_H

#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

/*
  Object: token_type
  Description: The enumerated types below allow for lexemes to be interpreted as their corresponding token types. 
*/
enum token_type {
	NONE = -1, 

	IDENT_T,
	NUMLIT_T,
	STRLIT_T,
	
	// Key words
	LISTOP_T,
	CONS_T,
	IF_T,
	COND_T,
	ELSE_T,
	DISPLAY_T,
	NEWLINE_T,
	AND_T,
	OR_T,
	NOT_T,
	DEFINE_T,

	// Predicates
	NUMBERP_T,
	LISTP_T,
	ZEROP_T,
	NULLP_T,
	STRINGP_T,


	// Arithmetic
	PLUS_T,
	MINUS_T,
	DIV_T,
	MULT_T,
	MODULO_T,
	ROUND_T,

	// Logical/Relational
	EQUALTO_T,
	GT_T,
	LT_T,
	GTE_T,
	LTE_T,

	// Other
	LPAREN_T,
	RPAREN_T,
	SQUOTE_T,
	ERROR_T,
	EOF_T, 


	NUM_TOKENS
};

/*
  Object: LexicalAnalyzer
  Description: This class interprets input read in from a source file (.ss) and produces a listing (.lst), token (.p1), and a debugging (.dgb) file.
*/
class LexicalAnalyzer 
{
	public:
		LexicalAnalyzer (char * filename);
		~LexicalAnalyzer ();
		token_type GetToken ();
		string GetTokenName (token_type t) const;
		string GetLexeme () const;
		void ReportError (const string & msg);
		token_type GetTokenType(int acceptingState);
		void WriteErrors();
		void fillTokenMap();
	private:
		ifstream input; 
		ofstream listingFile;
		ofstream tokenFile;
		ofstream debugFile;
		token_type token;
		string line;
		int linenum;
		int pos;
		string lexeme;
		int errors;
		//hash table to check a lexeme and return its token if it exists, see GetTokenType function
		std::unordered_map<string, int> myTokenMap; 
};

#endif
