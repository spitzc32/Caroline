%option yylineno

%{

  #include "./structs/hash/symboltable.h"
  #include "./token/tokentype.h"
  #include <stdlib.h>
  #include <stdio.h>

  entry_t** symbol_table;
  entry_t** constant_table;
  int cmnt_strt = 0;

%}

/* Exclusive states */
%x CMNT

letter [a-zA-Z_]
digit [0-9]
ws  [ \t\r\f\v]+
identifier [a-zA-Z][a-zA-Z0-9]*
hex [a-fA-F0-9]

E			[Ee][+-]?{digit}+
FS			(f|F|l|letter)
IS			(u|U|l|letter)*

%%
  /* Keywords Dictionary */
CHAR |
CHARACTER                       {insert(symbol_table,yytext,"DATATYPE",CHAR, yylineno);}
STRING                          {insert(symbol_table,yytext,"DATATYPE",STRING, yylineno);}
INT |
INTEGER                         {insert(symbol_table,yytext,"DATATYPE",INT, yylineno);}
REAL |
"REAL NUMBER"                   {insert(symbol_table,yytext,"DATATYPE",REAL, yylineno);}
BOOL |
BOOLEAN                         {insert(symbol_table,yytext,"DATATYPE",BOOL,yylineno);}
PRINT                           {insert(symbol_table,yytext,"IOKEYWORD",PRINT,yylineno);}
INPUT                           {insert(symbol_table,yytext,"IOKEYWORD",INPUT,yylineno);}
LOGICAL_AND                     {insert(symbol_table,yytext,"LOGDKEYWORD",LOGICAL_AND,yylineno);}
LOGICAL_OR                      {insert(symbol_table,yytext,"LOGKEYWORD",LOGICAL_OR,yylineno);}
LOGICAL_NOT                     {insert(symbol_table,yytext,"LOGKEYWORD",LOGICAL_NOT,yylineno);}
IF                              {insert(symbol_table,yytext,"CONDKEYWORD",IF,yylineno);}
THEN                            {insert(symbol_table,yytext,"CONDKEYWORD",THEN,yylineno);}
ELSEIF                          {insert(symbol_table,yytext,"CONDKEYWORD",ELSEIF,yylineno);}
ELSE                            {insert(symbol_table,yytext,"CONDKEYWORD",ELSE,yylineno);}
ENDIF                           {insert(symbol_table,yytext,"CONDKEYWORD",ENDIF,yylineno);}
SWITCH                          {insert(symbol_table,yytext,"CONDKEYWORD",SWITCH,yylineno);}
CASE                            {insert(symbol_table,yytext,"CONDKEYWORD",CASE,yylineno);}
ENDSWITCH                       {insert(symbol_table,yytext,"CONDKEYWORD",ENDSWITCH,yylineno);}
DEFAULT                         {insert(symbol_table,yytext,"CONDKEYWORD",DEFAULT,yylineno);}
FOR                             {insert(symbol_table,yytext,"LOOPKEYWORD",FOR,yylineno);}
WHILE                           {insert(symbol_table,yytext,"LOOPKEYWORD",WHILE,yylineno);}
DO                              {insert(symbol_table,yytext,"LOOPKEYWORD",DO,yylineno);}
ENDLOOP                         {insert(symbol_table,yytext,"LOOPKEYWORD",ENDLOOP,yylineno);}
BREAK                           {insert(symbol_table,yytext,"JUMPKEYWORD",BREAK,yylineno);}
CONTINUE                        {insert(symbol_table,yytext,"JUMPKEYWORD",CONTINUE,yylineno);}
TRUE                            {insert(symbol_table,yytext,"BOOLKEYWORD",TRUE,yylineno);}
FALSE                           {insert(symbol_table,yytext,"BOOLKEYWORD",FALSE,yylineno);}
TO                              {insert(symbol_table,yytext,"LOOPKEYWORD",TO,yylineno);}
AS                              {insert(symbol_table,yytext,"IOKEYWORD",AS,yylineno);}

  /* Comment Section */
COMMENT                          {cmnt_strt = yylineno; BEGIN CMNT;}
<CMNT>.|{ws}                      ;
<CMNT>\n                          {yylineno++;}
<CMNT>ENDCOMMENT                {BEGIN INITIAL;}
<CMNT>COMMENT                   {printf("Line %3d: Nested comments are not valid!\n",yylineno);}
<CMNT><<EOF>>                     {printf("Line %3d: Unterminated comment\n", cmnt_strt); yyterminate();}

  /* Identfier section */
{identifier}                      {insert(symbol_table,yytext,"IDENTIFIER",IDENTIFIER,yylineno);}
{ws}                              ;
{digit}+({letter}|_)+	            {printf("Line %3d: Illegal identifier name %s ",yylineno,yytext);}

0[xX]{hex}+{IS}?			            {insert(symbol_table,yytext,"CONSTANT",HEX_CONSTANT,yylineno);}
0{digit}+{IS}?				            {insert(symbol_table,yytext,"CONSTANT",DEC_CONSTANT,yylineno);}
{hex}+{IS}?				                {insert(symbol_table,yytext,"CONSTANT",HEX_CONSTANT,yylineno);}
{letter}?'(\\.|[^\\'])+'		      {insert(symbol_table,yytext,"CONSTANT",CHAR_CONSTANT,yylineno);}
{digit}+{E}{FS}?			            {insert(symbol_table,yytext,"CONSTANT",REAL_CONSTANT,yylineno);}
{digit}*"."{digit}+({E})?{FS}?		{insert(symbol_table,yytext,"CONSTANT",REAL_CONSTANT,yylineno);}
{digit}+"."{digit}*({E})?{FS}?		{insert(symbol_table,yytext,"CONSTANT",REAL_CONSTANT,yylineno);}

  /* Quotations Section */
\"[^\"\n]*\"     {

if(yytext[yyleng-2]=='\\')        /* check if it was an escaped quote */
{
  yyless(yyleng-1);               /* push the quote back if it was escaped */
  yymore();
}
else 
insert( constant_table,yytext,"CONSTANT",STRING,yylineno);
}

\"[^\"\n]*$                       {printf("Line %3d: Unterminated string %s\n",yylineno,yytext);}
\n                                {yylineno++;}

  /* Operators Dictionary */
"--"                              {insert(symbol_table,yytext,"DATATYPE",DECREMENT,yylineno);}
"++"                              {insert(symbol_table,yytext,"DATATYPE",INCREMENT,yylineno);}
"<="                              {insert(symbol_table,yytext,"DATATYPE",LS_THAN_EQ,yylineno);}
">="                              {insert(symbol_table,yytext,"DATATYPE",GR_THAN_EQ,yylineno);}
"=="                              {insert(symbol_table,yytext,"DATATYPE",EQ,yylineno);}
"!="                              {insert(symbol_table,yytext,"DATATYPE",DECREMENT,yylineno);}
","			                          {insert(symbol_table,yytext,"DATATYPE",COMMA,yylineno);}
"="			                          {insert(symbol_table,yytext,"DATATYPE",ASSIGN,yylineno);}
"("			                          {insert(symbol_table,yytext,"DATATYPE",OPEN_PAR,yylineno);}
")"			                          {insert(symbol_table,yytext,"DATATYPE",CLOSE_PAR,yylineno);}
"-"			                          {insert(symbol_table,yytext,"DATATYPE",MINUS,yylineno);}
"+"			                          {insert(symbol_table,yytext,"DATATYPE",PLUS,yylineno);}
"*"			                          {insert(symbol_table,yytext,"DATATYPE",MUL,yylineno);}
"/"		                            {insert(symbol_table,yytext,"DATATYPE",DIV,yylineno);}
"%"			                          {insert(symbol_table,yytext,"DATATYPE",MODULO,yylineno);}
"<"			                          {insert(symbol_table,yytext,"DATATYPE",LS_THAN,yylineno);}
">"			                          {insert(symbol_table,yytext,"DATATYPE",GR_THAN,yylineno);}
.                                 {printf("Line %3d: Illegal character %s ",yylineno,yytext);}


%%


int main(int argc, char **argv)
{
  yyin=fopen("test-cases/test-5.caroline","r");
  symbol_table=create_table();
  constant_table=create_table();
  yylex();
  display(symbol_table);

  return(0);
}
int yywrap()
{
  return(1);
}