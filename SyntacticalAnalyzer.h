/*
  File: SyntacticalAnalyzer.h
  Authors: John Salman, Brandon Williams, Nick Ivanoff
  Class: CS460 Fall 2018
  Description: Definition of the SyntacticalAnalyzer class.
*/

#ifndef SYN_H
#define SYN_H

#include <iostream>
#include <fstream>
#include "LexicalAnalyzer.h"

using namespace std;

class SyntacticalAnalyzer 
{
    public:
	SyntacticalAnalyzer (char * filename);
	~SyntacticalAnalyzer ();
    private:
	LexicalAnalyzer * lex;
	token_type token;
};
	
#endif
