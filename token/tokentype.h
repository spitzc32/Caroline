/* 
* Compiler Design Project 1 : Lexical Analyser
*
* File        : tokentype.h
* Description : This file defines tokens and the values associated to them.
*                  
*/
#ifndef TOKENTYPE_H
#define _TOKENTYPE_H

enum TokenType {
  CHAR,
  STRING,  
  INT,
  REAL,
  BOOL,
  LOGICAL_AND=5,
  LOGICAL_OR,
  LOGICAL_NOT,
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
  CONCAT,
  TRUE=50,
  FALSE,
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
  DOT,
  DELIMITER=300,
  COMMA,
  OPEN_PAR,
  CLOSE_PAR,
  FW_SLASH,
  HEX_CONSTANT=400,
  DEC_CONSTANT,
  INT_CONSTANT,
  REAL_CONSTANT,
  STR_CONSTANT,
  CHAR_CONSTANT,
  NULLABLE,
  WS,
  IDENTIFIER=500,
  INVALID,
  PROG=600,
  LINE,
  OBJECT,
  BASE_EXP,
  TERM,
  PREDICATE,
  EXPR,
  ASSIGN_CON,
  INPUT_CON,
  OUTPUT_CON,
  IF_CON,
  SWITCH_CON,
  ENDLINE
};

#endif