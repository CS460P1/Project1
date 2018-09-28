#ifndef TRANSITION_H
#define TRANSITION_H

enum STATESYMBOLS {
  ERROR = 102,
  BU = 101,
  GD = 100
};


enum SYMBOLS {
  alpha_not_list,
  digit,
  period,
  c,
  a,
  d,
  r,
  under_score,
  double_qoute,
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
  modulo,
  ampersand,
  open_bracket,
  close_bracket,
  exclamation,
  colon,
  comma,
  pipe,
  tilde,
  carrot
};

int table [16][30] {
  // symbols ALPHA,DIGIT,.,c,a,d,r,_,"""",+,-,/,*,=,>,<,(,),{'} single,%,&,[,],?,!,:,",",|,~,^
  // States 0-4
  {1,2,5,7,1,1,1,ERR,10,12,13,GD,GD,GD,14,15,GD,GD,GD,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR,ERR},
  {1,1,BU,1,1,1,1,1,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,6,BU,BU,BU,BU,BU,BU},
  {BU,2,3,BU,BU,BU,BU,,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU,BU},
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
#endif
