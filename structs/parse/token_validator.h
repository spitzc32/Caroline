/* 
* File        : token_validator.h
* Description : This file contains functions related to validate tokens. 
*               The functions implemented are:
*               tok_validator(), is_<token>(), is_datatype(), is_var_binding()
*/

#include "./parsetree.h"


/* Validate if belonging to category of Datatypes */
int is_datatype(int toktype) {
    return 
    toktype == CHAR ||
    toktype == STRING ||
    toktype == INT ||
    toktype == BOOL ||
    toktype == REAL;
}

int is_negative(t_list* tok) {
    return tok->token_type == MINUS && 
    (tok->successor->token_type == REAL_CONSTANT ||
    tok->successor->token_type == INT_CONSTANT ||
    tok->successor->token_type == DEC_CONSTANT);
}

/* match which logical operator is used*/
int match_logical_type (enum TokenType type) {
    return (type == EQ ||
            type == NOT_EQ ||
            type == GR_THAN ||
            type == GR_THAN_EQ ||
            type == LS_THAN ||
            type == LS_THAN_EQ ||
            type == LOGICAL_AND ||
            type == LOGICAL_OR);
}

/* Template function for Checking token succession types */

int tok_validator (t_list** tok, p_tree** tree, int type, char* lexeme) {
    
    // First Condition checking if tok is null
    if (*tok == NULL)
        return PARSING_ERROR;
    
    t_list *current = *tok;
    
    // Condition checking syntax rules set to token
    if (current->token_type != type) {
        printf("Expecting <%s>, Found <%s>\n", type2char(type), type2char(current->token_type));
        return PARSING_ERROR;
    }

    if (lexeme != NULL)
        if(strcmp(current->lexeme, lexeme) != 0) {
            printf("Expecting %s, Found %s\n", lexeme, current->lexeme);
            return PARSING_ERROR;
        }
    
    // As by definition above, tree is already allocated
    (*tree)->token = current->lexeme;
    (*tree)->type = current->token_type;
    (*tree)->child = NULL;
    (*tree)->sibling = NULL;
    
    *tok = current->successor;
    
    return SUBTREE_OK;
}


int is_char(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, CHAR, NULL);
}

int is_string(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, STRING, NULL);
}

int is_int(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, INT, NULL);
}

int is_real(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, REAL, NULL);
}

int is_bool(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, BOOL, NULL);
}

int is_null(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, NULLABLE, NULL);
}

int is_and(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, LOGICAL_AND, NULL);
}

int is_or(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, LOGICAL_OR, NULL);
}

int is_not(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, LOGICAL_NOT, NULL);
}

int is_print(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, PRINT, NULL);
}

int is_input(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, INPUT, NULL);
}

int is_as(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, AS, NULL);
}

int is_if(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, IF, NULL);
}

int is_then(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, THEN, NULL);
}

int is_elseif(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, ELSEIF, NULL);
}

int is_else(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, ELSE, NULL);
}

int is_endif(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, ENDIF, NULL);
}

int is_switch(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, SWITCH, NULL);
}

int is_case(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, CASE, NULL);
}

int is_endswitch(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, ENDSWITCH, NULL);
}

int is_default(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, DEFAULT, NULL);
}

int is_for(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, FOR, NULL);
}

int is_to(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, TO, NULL);
}

int is_by(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, BY, NULL);
}

int is_while(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, WHILE, NULL);
}

int is_do(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, DO, NULL);
}

int is_endloop(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, ENDLOOP, NULL);
}

int is_break(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, BREAK, NULL);
}

int is_continue(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, CONTINUE, NULL);
}

int is_true(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, TRUE, NULL);
}

int is_false(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, FALSE, NULL);
}

int is_assign(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, ASSIGN, NULL);
}

int is_minus(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, MINUS, NULL);
}

int is_plus(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, PLUS, NULL);
}

int is_mul(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, MUL, NULL);
}

int is_div(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, DIV, NULL);
}

int is_modulo(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, MODULO, NULL);
}

int is_ls_than(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, LS_THAN, NULL);
}

int is_gt_than(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, GR_THAN, NULL);
}

int is_ls_than_eq(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, LS_THAN_EQ, NULL);
}

int is_decrement(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, DECREMENT, NULL);
}

int is_increment(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, INCREMENT, NULL);
}

int is_gt_than_eq(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, GR_THAN_EQ, NULL);
}

int is_eq(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, EQ, NULL);
}

int is_not_eq(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, NOT_EQ, NULL);
}

int is_dot(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, DOT, NULL);
}

int is_delimeter(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, DELIMITER, NULL);
}

int is_comma(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, COMMA, NULL);
}

int is_open_par(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, OPEN_PAR, NULL);
}

int is_close_par(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, CLOSE_PAR, NULL);
}

int is_hex_const(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, HEX_CONSTANT, NULL);
}

int is_dec_const(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, DEC_CONSTANT, NULL);
}

int is_int_const(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, INT_CONSTANT, NULL);
}

int is_real_const(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, REAL_CONSTANT, NULL);
}

int is_char_const(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, CHAR_CONSTANT, NULL);
}

int is_identifier(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, CHAR, NULL);
}

int is_endline(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, ENDLINE, NULL);
}

int is_char_seq(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, STR_CONSTANT, NULL);
}

/* COPOUND TOKENS VALIDATION */
// TODO: String Constant validated if has contents to print
int is_quoted_string(t_list** tok, p_tree** tree) {
    // Primary condition if no tokens are found
    if (*tok == NULL)
        return PARSING_ERROR;
    
    p_tree *char_seq, *comma, *obj, *last;
    int status, nVar, nObj;

    status = SUBTREE_OK;
    nVar = nObj = 0;

    //Initial Tree declaring we are in a String Container
    (*tree)->token = "String";
    (*tree)->type = STR_CONSTANT;
    
    if ((char_seq = create_tree()) == NULL)
        return MEMORY_ERROR;
    
    // Set the Char Seq as the initial child
    status = is_char_seq(tok, &char_seq);
    if (status != SUBTREE_OK) {
        free_parse_tree(char_seq);
        return status;
    }

    (*tree)->child = char_seq;
    last = char_seq;

    // IF there are variables needed to interpolate, count them
    int i = 0;
    while (char_seq->token[i] != '\0') {
        if (char_seq->token[i] == '%') {
            if (char_seq->token[i+1] == '%') // escape char
                i += 2;
            else if (char_seq->token[i+1] == 's') {
                nVar += 1;
                i += 2;
            }
            else i++;
        }
        else i++;
    }

    while ((*tok)->token_type == COMMA) {
        if ((comma = create_tree()) == NULL)
            return MEMORY_ERROR;
    
        status = is_comma(tok, &comma);
        if (status != SUBTREE_OK) {
            free_parse_tree(comma);
            break;
        }

        last->sibling = comma;
        last = comma;
        
        // Now there must be a Obj
        if ((obj = create_tree()) == NULL)
            return MEMORY_ERROR;
        
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(obj);
            break;
        }
        
        last->sibling = obj;
        last = obj;
        nObj++;
    }

    // Raise Error if assignment of obj is not equal to its intermpolation
    if (nObj != nVar) {
        printf("QuotedStr with #obj != #interpolation (%d != %d)\n", nObj, nVar);
        return PARSING_ERROR;
    }
    return status;
}

/* Function checker if it is under logical operator (is_CondOp)*/
int is_logical_op (t_list** tok, p_tree** new) {
    enum TokenType type;

    type = (*tok)->token_type;
    if (type == LOGICAL_AND)
        return is_and(tok, new);
    else if (type == LOGICAL_OR)
        return is_or(tok, new);
    else if (type == EQ)
        return is_eq(tok, new);
    else if (type == NOT_EQ)
        return is_not_eq(tok, new);
    else if (type == GR_THAN)
        return is_gt_than(tok, new);
    else if (type == GR_THAN_EQ)
        return is_gt_than_eq(tok, new);
    else if (type == LS_THAN)
        return is_ls_than(tok, new);
    else if (type == LS_THAN_EQ)
        return is_ls_than_eq(tok, new);
    else
        return PARSING_ERROR;
}

/* Function Checker to check operators */
int is_Operator (t_list** tok, p_tree** new) {
    enum TokenType type;

    type = (*tok)->token_type;
    if (type == PLUS)
        return is_plus(tok, new);
    else if (type == MINUS)
        return is_minus(tok, new);
    else if (type == MUL)
        return is_mul(tok, new);
    else if (type == DIV)
        return is_div(tok, new);
    else if (type == MODULO)
        return is_modulo(tok, new);
    else
        return is_logical_op(tok, new);
}

/* Function checker to check expressions with/out signs and the precedence of what number(pow)*/
int is_number(t_list** tok, p_tree** tree) {
    // Primary condition if no tokens are found
    if (*tok == NULL)
        return PARSING_ERROR;

    p_tree *sign, *numeric;
    int status, has_sign;

    (*tree)->token = "Number";
    (*tree)->type = OBJECT;

    status = SUBTREE_OK;
    has_sign = 1;
    
    // Checking if expression has sign 
    if ((sign = create_tree()) == NULL)
        return PARSING_ERROR;
    
    if ((*tok)->token_type == PLUS)
        status = is_plus(tok, &sign);
    else if ((*tok)->token_type == MINUS)
        status = is_minus(tok, &sign);
    else
        has_sign = 0;

    if (status != SUBTREE_OK) {
        free_parse_tree(sign);
        return status;
    }
    if (has_sign)
        (*tree)->child = sign;
    else
        free_parse_tree(sign);

    // Checking if expression type it has containing it 
    if ((numeric = create_tree()) == NULL)
        return MEMORY_ERROR;

    if ((*tok)->token_type == INT_CONSTANT)
        status = is_int_const(tok, &numeric);
    else if ((*tok)->token_type == REAL_CONSTANT)
        status = is_real_const(tok, &numeric);
    else if ((*tok)->token_type == DEC_CONSTANT)
        status = is_dec_const(tok, &numeric);
    
    if (status != SUBTREE_OK)
        free_parse_tree(numeric);
    else {
        if (has_sign)
            sign->sibling = numeric;
        else
            (*tree)->child = numeric;
    }
    return status;
}

/* Determine which obj is involved with an expression */
int is_obj(t_list** tok, p_tree** tree) {
    // Primary condition if no tokens are found
    if (*tok == NULL)
        return PARSING_ERROR;
    
    p_tree* subtree;
    int status;

   
    (*tree)->token = "Object";
    (*tree)->type = OBJECT;

    subtree = create_tree();
    if (subtree == NULL)
        return MEMORY_ERROR;

    // use LL(1) FOLLOW Sets
    t_list* curr;
    curr = *tok;

    if (curr->token_type == IDENTIFIER)
        status = is_identifier(tok, &subtree);
    else if (curr->token_type == NULLABLE)
        status = is_null(tok, &subtree);
    else if (curr->token_type == STR_CONSTANT)
        status = is_char_seq(tok, &subtree);
    else if (curr->token_type == BOOL)
        status = is_bool(tok, &subtree);
    else if (curr->token_type == INT_CONSTANT ||
             curr->token_type == REAL_CONSTANT)
        status = is_number(tok, &subtree);
    else
        status = PARSING_ERROR;

    if (status == SUBTREE_OK)
        (*tree)->child = subtree;
    else
        free_parse_tree(subtree);
    return status;
}