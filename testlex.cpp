/*=====================================================================

     testlex.c: mini-C プログラムの字句解析系のテスト
        コンパイラ演習  2004 (c) 平岡佑介, 石浦菜岐佐

=====================================================================*/

#define _LEX_C

#include <stdio.h>
#include <stdlib.h>
#include "lex.h"

/*-------------------------------------------------------------------
    字句解析系とのインタフェース
  -------------------------------------------------------------------*/
int yylex(void);            /* トークンを一つ切り出す関数 */
extern FILE* yyin;          /* 処理対象のファイルへのポインタ */
extern char* yytext;        /* 切り出されたトークン */
extern int linenum;         /* 処理中の行番号 */
YYSTYPE yylval;             /* トークンの値を保持する union */


/*-------------------------------------------------------------------
  関数 lex_typename
    yylex の返すトークン番号 t を表示用の名前 name に変換する関数
  -------------------------------------------------------------------*/
void lex_typename(int t, char *name)  

{ 
  switch (t) {
  case lex_ID: strcpy(name,"ID"); break;  
  case lex_INT: strcpy(name,"INT"); break; 
  case lex_CHAR: strcpy(name,"CHAR"); break;   
  case lex_KW_WHILE: strcpy(name,"KW_WHILE"); break;  
  case lex_KW_RETURN: strcpy(name,"KW_RETURN"); break; 
  case lex_KW_INT: strcpy(name,"KW_INT"); break;
  case lex_KW_IF: strcpy(name,"KW_IF"); break;   
  case lex_KW_ELSE: strcpy(name,"KW_ELSE"); break; 
  case lex_KW_CHAR: strcpy(name,"KW_CHAR"); break;  
  case lex_PLUS: strcpy(name,"PLUS"); break;  
  case lex_MINUS: strcpy(name,"MINUS"); break;  
  case lex_STAR: strcpy(name,"STAR"); break;  
  case lex_SLASH: strcpy(name,"SLASH"); break;  
  case lex_PERCENT: strcpy(name,"PERCENT"); break;  
  case lex_AND: strcpy(name,"AND"); break;  
  case lex_LE: strcpy(name,"LE"); break;  
  case lex_LT: strcpy(name,"LT"); break; 
  case lex_GE: strcpy(name,"GE"); break;
  case lex_GT: strcpy(name,"GT"); break;   
  case lex_EQ: strcpy(name,"EQ"); break; 
  case lex_NE: strcpy(name,"NE"); break;  
  case lex_EQEQ: strcpy(name,"EQEQ"); break;  
  case lex_COMMA:  strcpy(name,"COMMA"); break;   
  case lex_RPAREN:  strcpy(name,"RPAR"); break; 
  case lex_RBRACE:  strcpy(name,"RBRACE"); break;  
  case lex_LBRACE:  strcpy(name,"LBRACE"); break; 
  case lex_LPAREN:  strcpy(name,"LPAR"); break;
  case lex_SEMICOLON:  strcpy(name,"SEMICOLON"); break;   
  case lex_LBRACK:  strcpy(name,"LBRACK"); break; 
  case lex_RBRACK:  strcpy(name,"RBRACK"); break;  
  default:        strcpy(name,"UNDEF");  
  } 
}   
 

/*-------------------------------------------------------------------
  関数 main
    ファイルのトークンを一つづつ切り出して表示する
  -------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  FILE* fp;
  int type;
  char name[32];
  if ( (fp = fopen(argv[1], "r")) == 0 ) {
    fprintf(stderr, "Failed to open file '%s'\n", argv[1]);
    exit(4);
  }
  yyin = fp;
  linenum = 1;
  while ((type = yylex())) {
    lex_typename(type, name);
    printf("%3d: type = %-10s token = \"%s\"", 
	   linenum, name, yytext);
    if (type==lex_INT || type==lex_CHAR) {
      printf("  val = %d", yylval.val);
    }
    printf("\n");
  }
  return 0;
}



