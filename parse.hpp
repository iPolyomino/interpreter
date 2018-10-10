/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSE_HPP_INCLUDED
# define YY_YY_PARSE_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    lex_KW_INT = 258,
    lex_KW_CHAR = 259,
    lex_KW_IF = 260,
    lex_KW_ELSE = 261,
    lex_KW_WHILE = 262,
    lex_KW_RETURN = 263,
    lex_PLUS = 264,
    lex_MINUS = 265,
    lex_STAR = 266,
    lex_SLASH = 267,
    lex_PERCENT = 268,
    lex_AND = 269,
    lex_EQ = 270,
    lex_EQEQ = 271,
    lex_NE = 272,
    lex_LT = 273,
    lex_GT = 274,
    lex_LE = 275,
    lex_GE = 276,
    lex_COMMA = 277,
    lex_SEMICOLON = 278,
    lex_LPAREN = 279,
    lex_RPAREN = 280,
    lex_LBRACE = 281,
    lex_RBRACE = 282,
    lex_LBRACK = 283,
    lex_RBRACK = 284,
    lex_INT = 285,
    lex_CHAR = 286,
    lex_ID = 287
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 29 "parse.yy" /* yacc.c:1909  */
 
  char* string;  
  int val;
  Expression* expression;
  Exp_variable* exp_variable;

#line 94 "parse.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSE_HPP_INCLUDED  */