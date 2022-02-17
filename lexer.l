%option yylineno

%{

  // #include "./structs/hash/symboltable.h"
  // #include "./structs/parse/parsetree.h"
  #include "./structs/parse/grammar_validator.h"
  #include <stdlib.h>
  #include <stdio.h>

  t_list* symbol_table;
  t_list* display_table;
  int cmnt_strt = 0;

%}

/* Exclusive states */
%x CMNT

letter [a-zA-Z_]
digit [0-9]+
ws  [ \t\r\f\v]+
identifier [a-zA-Z][a-zA-Z0-9]*
hex [a-fA-F0-9]

E			[Ee][+-]?{digit}+
FS			(f|F|l|letter)
IS			(u|U|l|letter)*

%%
  /* Keywords Dictionary */
CHAR |
CHARACTER                       {insert(&symbol_table,yytext,"DATATYPE",CHAR, yylineno);}
STRING                          {insert(&symbol_table,yytext,"DATATYPE",STRING, yylineno);}
INT |
INTEGER                         {insert(&symbol_table,yytext,"DATATYPE",INT, yylineno);}
REAL |
"REAL NUMBER"                   {insert(&symbol_table,yytext,"DATATYPE",REAL, yylineno);}
BOOL |
BOOLEAN                         {insert(&symbol_table,yytext,"DATATYPE",BOOL,yylineno);}
NULLABLE                        {insert(&symbol_table,yytext,"NULLABLE",NULLABLE,yylineno);}
PRINT                           {insert(&symbol_table,yytext,"IOKEYWORD",PRINT,yylineno);}
INPUT |
"INPUT IN"                          {insert(&symbol_table,yytext,"IOKEYWORD",INPUT,yylineno);}
AND                             {insert(&symbol_table,yytext,"LOGDKEYWORD",LOGICAL_AND,yylineno);}
OR                              {insert(&symbol_table,yytext,"LOGKEYWORD",LOGICAL_OR,yylineno);}
NOT                             {insert(&symbol_table,yytext,"LOGKEYWORD",LOGICAL_NOT,yylineno);}
IF                              {insert(&symbol_table,yytext,"CONDKEYWORD",IF,yylineno);}
THEN                            {insert(&symbol_table,yytext,"CONDKEYWORD",THEN,yylineno);}
ELSEIF                          {insert(&symbol_table,yytext,"CONDKEYWORD",ELSEIF,yylineno);}
ELSE                            {insert(&symbol_table,yytext,"CONDKEYWORD",ELSE,yylineno);}
ENDIF                           {insert(&symbol_table,yytext,"CONDKEYWORD",ENDIF,yylineno);}
SWITCH                          {insert(&symbol_table,yytext,"CONDKEYWORD",SWITCH,yylineno);}
CASE                            {insert(&symbol_table,yytext,"CONDKEYWORD",CASE,yylineno);}
ENDSWITCH                       {insert(&symbol_table,yytext,"CONDKEYWORD",ENDSWITCH,yylineno);}
DEFAULT                         {insert(&symbol_table,yytext,"CONDKEYWORD",DEFAULT,yylineno);}
FOR                             {insert(&symbol_table,yytext,"LOOPKEYWORD",FOR,yylineno);}
WHILE                           {insert(&symbol_table,yytext,"LOOPKEYWORD",WHILE,yylineno);}
DO                              {insert(&symbol_table,yytext,"LOOPKEYWORD",DO,yylineno);}
ENDLOOP                         {insert(&symbol_table,yytext,"LOOPKEYWORD",ENDLOOP,yylineno);}
BREAK                           {insert(&symbol_table,yytext,"JUMPKEYWORD",BREAK,yylineno);}
CONTINUE                        {insert(&symbol_table,yytext,"JUMPKEYWORD",CONTINUE,yylineno);}
TRUE                            {insert(&symbol_table,yytext,"BOOLKEYWORD",TRUE,yylineno);}
FALSE                           {insert(&symbol_table,yytext,"BOOLKEYWORD",FALSE,yylineno);}
TO                              {insert(&symbol_table,yytext,"LOOPKEYWORD",TO,yylineno);}
AS                              {insert(&symbol_table,yytext,"IOKEYWORD",AS,yylineno);}

  /* Comment Section */
COMMENT                          {cmnt_strt = yylineno; BEGIN CMNT; insert(&symbol_table,yytext,"COMMENT",COMMENT,yylineno);}
<CMNT>.|{ws}                      ;
<CMNT>\n                          {}
<CMNT>ENDCOMMENT                {BEGIN INITIAL; insert(&symbol_table,yytext,"ENDCOMMENT",ENDCOMMENT,yylineno);}
<CMNT>COMMENT                   {insert(&symbol_table,yytext,"INVALID",INVALID,yylineno);}
<CMNT><<EOF>>                     {insert(&symbol_table,yytext,"INVALID",INVALID,yylineno);BEGIN INITIAL;}

  /* Identfier section */
{identifier}                      {insert(&symbol_table,yytext,"IDENTIFIER",IDENTIFIER,yylineno);}
{ws}                              ;
{digit}+({letter}|_)+	            {insert(&symbol_table,yytext,"INVALID",INVALID,yylineno);}


{letter}?'(\\.|[^\\'])+'		      {insert(&symbol_table,yytext,"CHAR_CONSTANT",CHAR_CONSTANT,yylineno);}
{digit}+{E}{FS}?			            {insert(&symbol_table,yytext,"REAL_CONSTANT",REAL_CONSTANT,yylineno);}
{digit}*"."{digit}+({E})?{FS}?		{insert(&symbol_table,yytext,"REAL_CONSTANT",REAL_CONSTANT,yylineno);}
{digit}+"."{digit}*({E})?{FS}?		{insert(&symbol_table,yytext,"REAL_CONSTANT",REAL_CONSTANT,yylineno);}
{digit}                           {insert(&symbol_table,yytext,"INT_CONSTANT",INT_CONSTANT,yylineno);}

  /* Quotations Section */
\"[^\"\n]*\"     {

if(yytext[yyleng-2]=='\\')        /* check if it was an escaped quote */
{
  yyless(yyleng-1);               /* push the quote back if it was escaped */
  yymore();
}
else 
insert(&symbol_table,yytext,"STR_CONSTANT",STR_CONSTANT,yylineno);
}

\"[^\"\n]*$                       {insert(&symbol_table,yytext,"INVALID",INVALID ,yylineno);}
\n                                {insert(&symbol_table,yytext,"ENDLINE",ENDLINE ,yylineno); }

  /* Operators Dictionary */
"--"                              {insert(&symbol_table,yytext,"DECREMENT",DECREMENT,yylineno);}
"++"                              {insert(&symbol_table,yytext,"INCREMENT",INCREMENT,yylineno);}
"<="                              {insert(&symbol_table,yytext,"LS_THAN_EQ",LS_THAN_EQ,yylineno);}
">="                              {insert(&symbol_table,yytext,"GR_THAN_EQ",GR_THAN_EQ,yylineno);}
"=="                              {insert(&symbol_table,yytext,"EQ",EQ,yylineno);}
"!="                              {insert(&symbol_table,yytext,"NOT_EQ",NOT_EQ,yylineno);}
","			                          {insert(&symbol_table,yytext,"COMMA",COMMA,yylineno);}
"="			                          {insert(&symbol_table,yytext,"ASSIGN",ASSIGN,yylineno);}
"("			                          {insert(&symbol_table,yytext,"OPEN_PAR",OPEN_PAR,yylineno);}
")"			                          {insert(&symbol_table,yytext,"CLOSE_PAR",CLOSE_PAR,yylineno);}
"-"			                          {insert(&symbol_table,yytext,"MINUS",MINUS,yylineno);}
"+"			                          {insert(&symbol_table,yytext,"PLUS",PLUS,yylineno);}
"*"			                          {insert(&symbol_table,yytext,"MUL",MUL,yylineno);}
"/"		                            {insert(&symbol_table,yytext,"DIV",DIV,yylineno);}
"%"			                          {insert(&symbol_table,yytext,"MODULO",MODULO,yylineno);}
"<"			                          {insert(&symbol_table,yytext,"LS_THAN",LS_THAN,yylineno);}
">"			                          {insert(&symbol_table,yytext,"GR_THAN",GR_THAN,yylineno);}
.                                 {insert(&symbol_table,yytext,"INVALID",INVALID,yylineno);}


%%


int main(int argc, char **argv)
{
  char filename[200];
  printf("Enter the path filename:");
  scanf("%[^\n]s", filename);
  printf("%s %d",filename, ends_with(filename, "caroline", 8));
  
  if(ends_with(filename, "caroline", 8)) {
    yyin=fopen(filename,"r");
    symbol_table=create_table();
    yylex();
    display_table=symbol_table;
    display(display_table);

    run_with_stat(symbol_table);
  } else {
    printf("Invalid extension. Please input files only with .caroline extension");
  }
  
}
int yywrap()
{
  return(1);
}