// CS 460 - Class Exercise 1
// File: heronCE1.cpp
// Authors: John Salman, Joe Missamore
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;


int getCol(char c);
void breakup (const string & code, ostream & output);
bool isspecial(char x);

  enum STATESYMBOLS {
        ERROR = 100,
        GD = 101,
        BU = 102,
    };

    // ALPHA,DIGIT,_,+,=,%,&,*,],[,),(,.,/,?,!,:,",",-,>,|,<,~,^
    // VALUES: 0 - 23
    enum SYMBOLS {
        alpha, 
        digit,
        underscore,
        plusOperator,
        equalityOperator,
        percent,
        ampersand,
        asterisk,
        encloseBracket,
        openBracket,
        encloseParen,
        openParen,
        period,
        forwardSlash,
        questionMark,
        exclamationMark,
        colon,
        comma,
        dash,
        greaterThan,
        pipe,
        lessThan,
        tilde,
        carrot
    };


 int table [21][24] = {
        /* Transitions ...
         * 
         * States
         * .
         * .
         * .
         * 
         * Symbols: ALPHA,DIGIT,_,+,=,%,&,*,],[,),(,.,/,?,!,:,",",-,>,|,<,~,^
         * 
        */
       
        // States 0 - 5
        {1,2,1,5,19,10,11,6,GD,GD,GD,GD,4,14,GD,15,16,GD,17,12,18,7,GD,20}, 
        {1,1,1,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,2,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,3,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,4,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,4,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,2,BU,GD,GD,BU,BU,BU,BU,BU,BU,BU,4,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},

        // States 6 - 10
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,BU,BU,BU,8,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,9,BU,BU},
        {BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,GD,BU,BU,BU,BU},
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},

        // States 11 - 15
        {BU,BU,BU,BU,GD,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,13,BU,BU,BU,BU},
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        
        // States 16 - 20 
        {BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU},
        {BU,2,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,4,BU,BU,BU,BU,BU,GD,GD,BU,BU,BU,BU},
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,GD,BU,BU,BU},
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
        {BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
    };

int main (int argc, char * argv [])
{
	if (argc < 2)
	{	
		cerr << "Usage: " << argv[0] << " <filename>\n";
		exit (1);
	}
	ifstream infile (argv[1]);
	if (infile.fail())
	{
		cerr << "File: " << argv[1] << " not found.\n";
		exit (2);
	}
	string line;
	int lineno = 1;
	int i = 0;
	while (getline (infile, line))
	{
		cout << lineno++ << ". " << line << endl;
        
        // eliminating white space
        // may contain one lexeme 
        // or multiple lexemes
        istringstream iss(line);

        string lexeme;
        
        while (iss >> lexeme) {
            breakup (lexeme, cout);
        }
	}

	infile.close();
	return 0;
}

void breakup (const string & code, ostream & output)
{
    int pos = 0;
    int state;
    string lex;
    int col = 0; 

    while(pos < code.length()) {
        
        state = 0;
        lex = "";
        while(state < 100){
            
            col = getCol(code[pos]);
            if (col < 100) {
                state = table[state][col];
                
            } else {
                state = col;
            }
            
            if (state != BU) {
                lex += code[pos];
            }

            pos++;
    
        }

        if (state == BU) {
            pos--; 
            if (lex != "") {
                output << '\t' << lex << endl;
            }
        } else if (state == GD) {
            output << '\t' << lex << endl;
        } else {
            output << '\t' << lex << endl;            
        }

        
        if (code[pos] == ';') {
            output << '\t' << code[pos] << endl;
            pos++;
        }
    
    }

    
} 
    

/* ALPHA
,DIGIT
,_
,+
,=,%,&,*,],[,),(,.,/,?,!,:,",",-,>,|,<,~,^ */
int getCol(char c) {
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
