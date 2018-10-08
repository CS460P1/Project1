/*
  File: SyntacticalAnalyzer.cpp
  Authors: John Salman
  Class: CS460 Fall 2018
  Description: Implementation of the SyntacticalAnalyzer class, as of now this class primarily serves
               to call the LexicalAnalyzer class in order to parse the input from a source file.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include "SyntacticalAnalyzer.h"

using namespace std;

/*
  Function: SynctacticalAnalyzer()
  Parameters: a c-style string representing the name of a file
  Return: NA
  Description: The constructor for the SyntacticalAnalyzer class, at this moment it solely calls methods
               of the LexicalAnalyzer class in order to parse input from the source file.
 */
SyntacticalAnalyzer::SyntacticalAnalyzer (char * filename)
{
	lex = new LexicalAnalyzer (filename);
	token_type t;
	while ((t = lex->GetToken()) != EOF_T)
	{

	}
	lex->WriteErrors();
}


/*
  Function: ~SyntacticalAnalyzer()
  Parameters: none
  Return: NA
  Description: The default destructor for the SyntacticalAnalyzer class, deletes an internal LexicalAnalyzer
               object.
 */
SyntacticalAnalyzer::~SyntacticalAnalyzer ()
{
	delete lex;
}
