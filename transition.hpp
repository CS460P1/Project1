#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include <ctype.h>
#include <unordered_map>

using namespace std;

std::unordered_map<string, int> myTokenMap;
fillTokenMap();

enum STATESYMBOLS {
  ERR = 102,
  BU = 101,
  GD = 100
};


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
  exclamation,
  question,
  colon,
  comma,
  pipe,
  tilde,
  carrot
};

int table [16][30] {
  // symbols ALPHA, DIGIT, ., c_char, a_char, d_char, r_char, _, ", +, -, /, *, =, >, <, (, ), {'} single, %, &, [, ], ?, !, :, ,, |, ~, ^
  // States 0-4
  {1,2,5,7,1,1,1,ERR,10,12,13,GD,GD,GD,14,15,GD,GD,GD,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
  {1,1,BU,1,1,1,1,1,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,6,BU,BU,BU,BU,BU,BU},
  {BU,2,3,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
  {BU,4,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
  {BU,4,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},

  // States 5-9
  {ERR,4,ERR, ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR, ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
  {BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
  {1,BU,BU,1,8,9,1,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
  {1,BU,BU,1,1,9,10,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
  {1,BU,BU,1,1,9,10,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},

  // States 10-15
  {1,BU,BU,1,1,1,1,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
  {11,11,11,11,11,11,11,11,GD,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11},
  {BU,2,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
  {BU,2,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
  {BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
  {BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,GD,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,}
};

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
  default:
    if (isdigit(c)) {
      return digit;
      
    } else if (isalpha(c) && c != 'c' && c!= 'a' && c != 'd' && c != 'r') { // will still work for IDENT_T, just treats {c,a,d,r} as a special case
      return alpha_not_list;
    }
    return BU;
  }
}

//Given a lexeme in string format, will return the number associated with the enumerated token_type.
//does this by using an unordered hash map. 
int enumIdentifierNumber(string lexeme){
	std::unordered_map<string, int>::const_iterator got = myTokenMap.find(lexeme);
	if(got != myTokenMap.end()){
		return got->second;
	}
	else return 0;
}

void fillTokenMap(){
	myTokenMap.insert( 
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
			{"'",33});

}

#endif
