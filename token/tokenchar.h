#ifndef TOKENCHAR_H
#define _TOKENCHAR_H

#include "./tokentype.h"

const char* type2char (enum TokenType t) {
    switch (t)
    {
        case CHAR: return "CHAR";
        case STRING: return "STRING";
        case INT: return "INT";
        case REAL: return "REAL";
        case BOOL: return "BOOL";
        case NULL: return "NULL";
        case LOGICAL_AND: return "AND";
        case LOGICAL_OR: return "OR";
        case LOGICAL_NOT: return "NOT";
        case PRINT: return "PRINT";
        case INPUT: return "INPUT";
        case AS: return "AS";
        case IF: return "IF";
        case THEN: return "THEN";
        case ELSEIF: return "ELSEIF";
        case ELSE: return "ELSE";
        case ENDIF: return "ENDIF";
        case SWITCH: return "SWITCH";
        case CASE: return "CASE";
        case ENDSWITCH: return "ENDSWITCH";
        case DEFAULT: return "DEFAULT";
        case FOR: return "FOR";
        case TO: return "TO";
        case BY: return "BY";
        case WHILE: return "WHILE";
        case DO: return "DO";
        case ENDLOOP: return "ENDLOOP";
        case COMMENT: return "COMMENT";
        case ENDCOMMENT: return "ENDCOMMENT";
        case BREAK: return "BREAK";
        case CONTINUE: return "CONTINUE";
        case TRUE: return "TRUE";
        case FALSE: return "FALSE";
        case ASSIGN: return "=";
        case MINUS: return "-";
        case PLUS: return "+";
        case MUL: return "*";
        case DIV: return "/";
        case MODULO: return "%";
        case LS_THAN: return "<";
        case GR_THAN: return ">";
        case DECREMENT: return "--";
        case INCREMENT: return "++";
        case LS_THAN_EQ: return "<=";
        case GR_THAN_EQ: return ">=";
        case EQ: return "==";
        case NOT_EQ: return "!=";
        case DOT: return "DOT";
        case DELIMITER: return "DELIMITER";
        case COMMA: return "COMMA";
        case OPEN_PAR: return "(";
        case CLOSE_PAR: return ")";
        case HEX_CONSTANT: return "HEX";
        case DEC_CONSTANT: return "Decimal Number";
        case INT_CONSTANT: return "Integer";
        case REAL_CONSTANT: return "Real Number";
        case STR_CONSTANT: return "String";
        case CHAR_CONSTANT: return "Character";
        case IDENTIFIER: return "IDENTIFIER";
        case INVALID: return "INVALID";
        case Program: return "Program";
        case Line: return "Line";
        case ENDLINE: return "ENDLINE";
        default: return "UNKNOWN";
    }
}

#endif