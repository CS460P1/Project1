#ifndef TRANSITION_HPP
#define TRANSITION_HPP

#include <ctype.h>
#include <unordered_map>

using namespace std;


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

//std::unordered_map<string, int> myTokenMap;
//fillTokenMap();
/*
*/

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



#endif
