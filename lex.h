#ifndef _LEX_H
#define _LEX_H

#include <string.h>

typedef union {
  int val;
  char* string;
} YYSTYPE;


#define lex_ID         2

#define lex_INT        3
#define lex_CHAR       4

#define lex_KW_CHAR    5
#define lex_KW_ELSE    6
#define lex_KW_IF      7
#define lex_KW_INT     8
#define lex_KW_RETURN  9
#define lex_KW_WHILE  10

#define lex_PLUS      11
#define lex_MINUS     12
#define lex_STAR      13
#define lex_SLASH     14
#define lex_PERCENT   15
#define lex_AND       16
#define lex_EQ        17
#define lex_EQEQ      18
#define lex_NE        19
#define lex_GT        20
#define lex_GE        21
#define lex_LT        22
#define lex_LE        23
#define lex_COMMA     24
#define lex_SEMICOLON 25
#define lex_LPAREN    26
#define lex_RPAREN    27
#define lex_LBRACE    28
#define lex_RBRACE    29
#define lex_LBRACK    30
#define lex_RBRACK    31

extern YYSTYPE yylval;

#endif

