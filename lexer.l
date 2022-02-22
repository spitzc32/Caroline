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
CHARACTER                       {insert(&symbol_table,yytext,"DATATYPE",CHAR, yylineno, NULL);}
STRING                          {insert(&symbol_table,yytext,"DATATYPE",STRING, yylineno, NULL);}
INT |
INTEGER                         {insert(&symbol_table,yytext,"DATATYPE",INT, yylineno, NULL);}
REAL |
"REAL NUMBER"                   {insert(&symbol_table,yytext,"DATATYPE",REAL, yylineno, NULL);}
BOOL |
BOOLEAN                         {insert(&symbol_table,yytext,"DATATYPE",BOOL,yylineno, NULL);}
NULLABLE                        {insert(&symbol_table,yytext,"NULLABLE",NULLABLE,yylineno, NULL);}
PRINT                           {insert(&symbol_table,yytext,"IOKEYWORD",PRINT,yylineno, NULL);}
INPUT |
"INPUT IN"                          {insert(&symbol_table,yytext,"IOKEYWORD",INPUT,yylineno, NULL);}
AND                             {insert(&symbol_table,yytext,"LOGDKEYWORD",LOGICAL_AND,yylineno, NULL);}
OR                              {insert(&symbol_table,yytext,"LOGKEYWORD",LOGICAL_OR,yylineno, NULL);}
NOT                             {insert(&symbol_table,yytext,"LOGKEYWORD",LOGICAL_NOT,yylineno, NULL);}
IF                              {insert(&symbol_table,yytext,"CONDKEYWORD",IF,yylineno, NULL);}
THEN                            {insert(&symbol_table,yytext,"CONDKEYWORD",THEN,yylineno, NULL);}
ELSEIF                          {insert(&symbol_table,yytext,"CONDKEYWORD",ELSEIF,yylineno, NULL);}
ELSE                            {insert(&symbol_table,yytext,"CONDKEYWORD",ELSE,yylineno, NULL);}
ENDIF                           {insert(&symbol_table,yytext,"CONDKEYWORD",ENDIF,yylineno, NULL);}
SWITCH                          {insert(&symbol_table,yytext,"CONDKEYWORD",SWITCH,yylineno, NULL);}
CASE                            {insert(&symbol_table,yytext,"CONDKEYWORD",CASE,yylineno, NULL);}
ENDSWITCH                       {insert(&symbol_table,yytext,"CONDKEYWORD",ENDSWITCH,yylineno, NULL);}
DEFAULT                         {insert(&symbol_table,yytext,"CONDKEYWORD",DEFAULT,yylineno, NULL);}
FOR                             {insert(&symbol_table,yytext,"LOOPKEYWORD",FOR,yylineno, NULL);}
WHILE                           {insert(&symbol_table,yytext,"LOOPKEYWORD",WHILE,yylineno, NULL);}
DO                              {insert(&symbol_table,yytext,"LOOPKEYWORD",DO,yylineno, NULL);}
ENDLOOP                         {insert(&symbol_table,yytext,"LOOPKEYWORD",ENDLOOP,yylineno, NULL);}
BREAK                           {insert(&symbol_table,yytext,"JUMPKEYWORD",BREAK,yylineno, NULL);}
CONTINUE                        {insert(&symbol_table,yytext,"JUMPKEYWORD",CONTINUE,yylineno, NULL);}
TRUE                            {insert(&symbol_table,yytext,"BOOLKEYWORD",TRUE,yylineno, NULL);}
FALSE                           {insert(&symbol_table,yytext,"BOOLKEYWORD",FALSE,yylineno, NULL);}
TO                              {insert(&symbol_table,yytext,"LOOPKEYWORD",TO,yylineno, NULL);}
BY                              {insert(&symbol_table,yytext,"LOOPKEYWORD",BY,yylineno, NULL);}
AS                              {insert(&symbol_table,yytext,"IOKEYWORD",AS,yylineno, NULL);}

  /* Comment Section */
COMMENT                          {cmnt_strt = yylineno; BEGIN CMNT; insert(&symbol_table,yytext,"COMMENT",COMMENT,yylineno, NULL);}
<CMNT>.|{ws}                      ;
<CMNT>\n                          {}
<CMNT>ENDCOMMENT                {BEGIN INITIAL; insert(&symbol_table,yytext,"ENDCOMMENT",ENDCOMMENT,yylineno, NULL);}
<CMNT>COMMENT                   {insert(&symbol_table,yytext,"INVALID",INVALID,yylineno,"No closing comment statement before new COMMENT");}
<CMNT><<EOF>>                     {insert(&symbol_table,yytext,"INVALID",INVALID,yylineno,"No closing comment statement before termination");BEGIN INITIAL;}

  /* Identfier section */
{identifier}                      {insert(&symbol_table,yytext,"IDENTIFIER",IDENTIFIER,yylineno, NULL);}
{ws}                              ;
{digit}+({letter}|_)+	            {insert(&symbol_table,yytext,"INVALID",INVALID,yylineno,"Invalid identifier. did not follow rules");}


{letter}?'(\\.|[^\\'])+'		      {insert(&symbol_table,yytext,"CHAR_CONSTANT",CHAR_CONSTANT,yylineno, NULL);}
{digit}+{E}{FS}?			            {insert(&symbol_table,yytext,"REAL_CONSTANT",REAL_CONSTANT,yylineno, NULL);}
{digit}*"."{digit}+({E})?{FS}?		{insert(&symbol_table,yytext,"REAL_CONSTANT",REAL_CONSTANT,yylineno, NULL);}
{digit}+"."{digit}*({E})?{FS}?		{insert(&symbol_table,yytext,"REAL_CONSTANT",REAL_CONSTANT,yylineno, NULL);}
{digit}                           {insert(&symbol_table,yytext,"INT_CONSTANT",INT_CONSTANT,yylineno, NULL);}

  /* Quotations Section */
\"[^\"\n]*\"     {

if(yytext[yyleng-2]=='\\')        /* check if it was an escaped quote */
{
  yyless(yyleng-1);               /* push the quote back if it was escaped */
  yymore();
}
else 
insert(&symbol_table,yytext,"STR_CONSTANT",STR_CONSTANT,yylineno, NULL);
}

\"[^\"\n]*$                       {insert(&symbol_table,yytext,"INVALID",INVALID ,yylineno,"No closing quotations");}
\n                                {insert(&symbol_table,yytext,"ENDLINE",ENDLINE ,yylineno, NULL); }

  /* Operators Dictionary */
"-="                              {insert(&symbol_table,yytext,"DECREMENT",MINUSCREMENT,yylineno, NULL);}
"+="                              {insert(&symbol_table,yytext,"INCREMENT",PLUSCREMENT,yylineno, NULL);}
"*="                              {insert(&symbol_table,yytext,"INCREMENT",MULTICREMENT,yylineno, NULL);}
"/="                              {insert(&symbol_table,yytext,"INCREMENT",DIVCREMENT,yylineno, NULL);}
"<="                              {insert(&symbol_table,yytext,"LS_THAN_EQ",LS_THAN_EQ,yylineno, NULL);}
">="                              {insert(&symbol_table,yytext,"GR_THAN_EQ",GR_THAN_EQ,yylineno, NULL);}
"=="                              {insert(&symbol_table,yytext,"EQ",EQ,yylineno, NULL);}
"!="                              {insert(&symbol_table,yytext,"NOT_EQ",NOT_EQ,yylineno, NULL);}
","			                          {insert(&symbol_table,yytext,"COMMA",COMMA,yylineno, NULL);}
"="			                          {insert(&symbol_table,yytext,"ASSIGN",ASSIGN,yylineno, NULL);}
"("			                          {insert(&symbol_table,yytext,"OPEN_PAR",OPEN_PAR,yylineno, NULL);}
")"			                          {insert(&symbol_table,yytext,"CLOSE_PAR",CLOSE_PAR,yylineno, NULL);}
"-"			                          {insert(&symbol_table,yytext,"MINUS",MINUS,yylineno, NULL);}
"+"			                          {insert(&symbol_table,yytext,"PLUS",PLUS,yylineno, NULL);}
"*"			                          {insert(&symbol_table,yytext,"MUL",MUL,yylineno, NULL);}
"/"		                            {insert(&symbol_table,yytext,"DIV",DIV,yylineno, NULL);}
"%"			                          {insert(&symbol_table,yytext,"MODULO",MODULO,yylineno, NULL);}
"<"			                          {insert(&symbol_table,yytext,"LS_THAN",LS_THAN,yylineno, NULL);}
">"			                          {insert(&symbol_table,yytext,"GR_THAN",GR_THAN,yylineno, NULL);}
.                                 {insert(&symbol_table,yytext,"INVALID",INVALID,yylineno, NULL);}


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