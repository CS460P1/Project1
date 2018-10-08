/*
  File: Project1.cpp
  Authors: Brandon Williams, John Salman, Nick Ivanoff
  Class: CS460 Fall 2018
  Description: This is the main file for project 1, it creates a SyntacticalAnalyzer object which in turn creates
               a LexicalAnalyzer object which interprets a file passed from the command line at run time.
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "SetLimits.h"
#include "SyntacticalAnalyzer.h"

int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		printf ("format: proj1 <filename>\n");
		exit (1);
	}
	SetLimits ();
	SyntacticalAnalyzer parser (argv[1]);

	return 0;
}
