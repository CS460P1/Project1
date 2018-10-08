/*
  File: transition.hpp
  Authors: John Salman, Brandon Williams, Nick Ivanoff
  Class: CS460 Fall 2018
  Description: This header files contains the multiple components of the DFA. There are the enumerated state symbols
               and enumerated representation of the possible characters the program could encounter. This file also
	       contains the defintion of the getCol() function which interprets characters and returns their enumerated
	       value.
*/

#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include <ctype.h>
#include <unordered_map>

using namespace std;

/*
  Object: STATESYMBOLS
  Description: The symbols in the object below represent various states reachable within the DFA. This includes, the good (GD)
               state, in which the DFA has reached the last character possible for a lexeme and accepts it. The back-up (BU) state, which
	       indicates a character that is not accepted from the current state, meaning the DFA should accept the lexeme and
	       start interpreting from the starting state. There are also two error states, one (ERR) that interprets a character as
	       an error and continues parsing input, and another (ERR2) that indicates the DFA has reached an error but needs to back-up
	       to read the next (possibly accepted) lexeme. The last state in the table (SPACE) indicates a DFA has encountered a white space
	       which could represent the end of a lexeme. The space state is valuable as it allow us to take in string literals in their entirety.
*/
enum STATESYMBOLS {
  SPACE = 104, // space
  ERR2 = 103,  // error with back-up
  ERR = 102,   // error
  BU = 101,    // back-up
  GD = 100     // good
};

/*
  Object: SYMBOLS
  Description: The symbols below represent the numeric value of various characters that can be taken as input in the program.
               This works in conjunction with the GetToken() method of the LexicalAnalyzer class by providing 
*/
enum SYMBOLS {
  alpha_not_list,
  digit,
  period,
  c_char,
  a_char,
  d_char,
  r_char,
  under_score,
  double_quote,
  plus_operator,
  minus_operator,
  division_operator,
  multiplication_operator,
  assignment_operator,
  greater_than,
  less_than,
  open_parentheses,
  close_parentheses,
  single_quote,
  percent,
  ampersand,
  open_bracket,
  close_bracket,
  question,
  exclamation,
  colon,
  comma,
  pipe,
  tilde,
  carrot,
  dollar,
  space
};

/*
  Object: table[][]
  Description: The two dimensional array below represent the tranisition table of the DFA. Arrays that contain the good
               statesymbol (defined above) represent the accepting state of a function. Numerous lexemes don't have
	       a strict defintion, and can only be determined once a character is encountered that transitions to 
	       the back-up state.
*/
int table [16][32] {

  // Symbols,ALPHA (! c | a | d| r),DIGIT,.,c,a,d,r,_,"""",+,-,/,*,=,>,<,(,),{'} single,%,&,[,],?,!,:,",",|,~,^,$, ' (WhiteSpace)
  // States 0-4												
  {1,2,5,7,1,1,1,ERR,11,12,13,GD,GD,GD,14,15,GD,GD,GD,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,0}, // start state
  {1,1,BU,1,1,1,1,1,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,6,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to IDENT_T, keywords (excluding LISTOP_T), predicates and arithmetic keywords {accepting}
  {BU,2,3,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to NUMLIT_T on digit input
  {BU,4,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to NUMLIT_T on digt -> decimal input
  {BU,4,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to NUMLIT_T on ((+ or -)(digit -> decimal -> digit) + (decimal -> digit)) input

  // States 5-9
  {ERR2,4,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2,ERR2}, // path to NUMLIT_T on decimal input
  {BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to predicate tokens alphabet character -> ? input
  {1,BU,BU,1,8,9,1,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to LISTOP_T on 'c' input
  {1,BU,BU,1,1,9,10,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to LISTOP_T on 'ca' input
  {1,BU,BU,1,1,9,10,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to LISTOP_T on 'cd' + 'cad^+' input

  // States 10-15
  {1,BU,BU,1,1,1,1,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to LISTOP_T on 'car' + 'cd^+r' + 'cad^+r' input
  {11,11,11,11,11,11,11,11,GD,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11}, // path to STRLIT_T on '"' + '"(char^*)' input 
  {BU,2,2,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to PLUS_T or NUMLIT_T on '+' input
  {BU,2,2,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to MINUS_T or NUMLIT_T on '-' input
  {BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE}, // path to GT_T or GTE_T on '>' input
  {BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,SPACE} // path to LT_T or LTE_T on '<' input
};

/*
  Function: getCol()
  Parameters: a character
  Return: the enumerated value of the character parameter or a error value if default is reached. 
  Description: This function interprets character inputs and outputs an numeric value used to 
               index the transition table.
*/		
int getCol(char c) {

  switch (c) {
  case '.':
    return period;
  case 'c':
    return c_char;
  case 'a':
    return a_char;
  case 'd':
    return d_char;
  case 'r':
    return r_char;
  case '_':
    return under_score;
  case '"':
    return double_quote;
  case '+':
    return plus_operator;
  case '-':
    return minus_operator;
  case '/':
    return division_operator;
  case '*':
    return multiplication_operator;;
  case '=':
    return assignment_operator;
  case '>':
    return greater_than;
  case '<':
    return less_than;
  case '(':
    return open_parentheses;
  case ')':
    return close_parentheses;
  case '\'':
    return single_quote;
  case '%':
    return percent;
  case '&':
    return ampersand;
  case '[':
    return open_bracket;
  case ']':
    return close_bracket;
  case '!':
    return exclamation;
  case '?':
    return question;
  case ':':
    return colon;
  case ',':
    return comma;
  case '|':
    return pipe;
  case '~':
    return tilde;
  case '^':
    return carrot;
  case '$':
    return dollar;
  case ' ':
    return space;
  default:
    if (isdigit(c)) {
      return digit;
      
    } else if (isalpha(c) && c != 'c' && c!= 'a' && c != 'd' && c != 'r') { // will still work for IDENT_T, just treats {c,a,d,r} as a special case
      return alpha_not_list;
    }
    return ERR;
  }
}



#endif
