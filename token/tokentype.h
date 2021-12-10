/* 
* Compiler Design Project 1 : Lexical Analyser
*
* File        : tokens.h
* Description : This file defines tokens and the values associated to them.
*                  
*/
#ifndef TOKENTYPE_H
#define _TOKENTYPE_H

enum data_type {
  CHAR,
  STRING,  
  INT,
  REAL,
  BOOL,
};

enum logical_op {
  LOGICAL_AND=5,
  LOGICAL_OR,
  LOGICAL_NOT,
};

enum keywords
{
  PRINT=8,
  INPUT,
  AS,
  IF,
  THEN,
  ELSEIF,
  ELSE,
  ENDIF,
  SWITCH,
  CASE,
  ENDSWITCH,
  DEFAULT,
  FOR,
  TO,
  BY,
  WHILE,
  DO,
  ENDLOOP,
  COMMENT,
  ENDCOMMENT,
  BREAK,
  CONTINUE,
};

enum bool_keyword {
  TRUE=50,
  FALSE,
};

enum operators
{
  ASSIGN=100,
  MINUS,
  PLUS,
  MUL,
  DIV,
  MODULO,
  LS_THAN,
  GR_THAN,
  DECREMENT,
  INCREMENT,
  LS_THAN_EQ,
  GR_THAN_EQ,
  EQ,
  NOT_EQ,
  DOT
};

enum special_symbols
{
  DELIMITER=300,
  COMMA,
  OPEN_PAR,
  CLOSE_PAR,
  FW_SLASH
};

enum constants
{
  HEX_CONSTANT=400,
  DEC_CONSTANT,
  REAL_CONSTANT,
  STRING_CONSTANT,
  CHAR_CONSTANT,
};

enum IDENTIFIER
{
  IDENTIFIER=500
};

#endif