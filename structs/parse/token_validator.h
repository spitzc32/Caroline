/* 
* File        : token_validator.h
* Description : This file contains functions related to validate tokens. 
*               The functions implemented are:
*               tok_validator(), is_<token>(), match_<operation>(), is_var_binding()
*/

#include "./parsetree.h"

//MATCHER FUNTIONS:
/* Validate if belonging to category of Datatypes */
int match_datatype(int toktype) {
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

int match_constants(enum TokenType type) {
    return (
        type == REAL_CONSTANT ||
        type == INT_CONSTANT ||
        type == DEC_CONSTANT ||
        type == STR_CONSTANT ||
        type == TRUE || type == FALSE
    );
}

int match_identifier(enum TokenType type) {
    return type == IDENTIFIER;
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



/* match which arithmetic operator is used*/
int match_arithmetic_type (enum TokenType type) {
    return (type == PLUS ||
            type == MINUS ||
            type == MUL ||
            type == DIV ||
            type == MODULO);
}

/* match which term operator is used */
int match_term_type (enum TokenType type) {
    return (type == MUL ||
            type == DIV ||
            type == MODULO);
}

/* match which term operator is used */
int match_crement_type (enum TokenType type) {
    return (type == PLUSCREMENT ||
            type == MINUSCREMENT ||
            type == MULTICREMENT ||
            type == DIVCREMENT);
}

// SINGLE TOKEN FUNCTIONS
/* Template function for Checking token succession types */
int tok_validator (t_list** tok, p_tree** tree, int type, char* lexeme) {
    
    // First Condition checking if tok is null
    if (*tok == NULL)
        return PARSING_ERROR;
    
    t_list *current = *tok;
    
    // Condition checking syntax rules set to token
    printf("Sa Validator: %d, %d\n", current->token_type, type);
    if (current->token_type != type) {
        printf("PARSER ERROR: In line %d. Expecting <%s>, Found <%s>\n", current->line, type2char(type), type2char(current->token_type));
        return PARSING_ERROR;
    }

    if (lexeme != NULL)
        if(strcmp(current->lexeme, lexeme) != 0) {
            printf("Expecting %s, Found %s\n", lexeme, current->lexeme);
            return PARSING_ERROR;
        }
    
    *tree = create_tree_entry(current->lexeme, current->token_type, current->line);
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

int is_minuscrement(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, MINUSCREMENT, NULL);
}

int is_pluscrement(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, PLUSCREMENT, NULL);
}

int is_multicrement(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, MULTICREMENT, NULL);
}

int is_divcrement(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, DIVCREMENT, NULL);
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
    return tok_validator(tok, tree, IDENTIFIER, NULL);
}

int is_endline(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, ENDLINE, NULL);
}

int is_char_seq(t_list** tok, p_tree** tree) {
    return tok_validator(tok, tree, STR_CONSTANT, NULL);
}




/* COPOUND TOKENS VALIDATION */
/* Function checker if it is under logical operator (is_CondOp)*/
int is_logical_op (t_list** tok, p_tree** tree) {
    enum TokenType type;

    type = (*tok)->token_type;
    if (type == LOGICAL_AND)
        return is_and(tok, tree);
    else if (type == LOGICAL_OR)
        return is_or(tok, tree);
    else if (type == EQ)
        return is_eq(tok, tree);
    else if (type == NOT_EQ)
        return is_not_eq(tok, tree);
    else if (type == GR_THAN)
        return is_gt_than(tok, tree);
    else if (type == GR_THAN_EQ)
        return is_gt_than_eq(tok, tree);
    else if (type == LS_THAN)
        return is_ls_than(tok, tree);
    else if (type == LS_THAN_EQ)
        return is_ls_than_eq(tok, tree);
    else
        return PARSING_ERROR;
}

/* Function checker if it is under datatype */
int is_datatype (t_list** tok, p_tree** tree) {
    enum TokenType type;

    type = (*tok)->token_type;
    if (type == CHAR)
        return is_char(tok, tree);
    else if (type == STRING)
        return is_string(tok, tree);
    else if (type == INT)
        return is_int(tok, tree);
    else if (type == REAL)
        return is_real(tok, tree);
    else if (type == BOOL)
        return is_bool(tok, tree);
    else
        return PARSING_ERROR;
}

/* Function Checker to check crement operators */
int is_crement (t_list** tok, p_tree** tree) {
    enum TokenType type;

    type = (*tok)->token_type;
    if (type == PLUSCREMENT)
        return is_pluscrement(tok, tree);
    else if (type == MINUSCREMENT)
        return is_minuscrement(tok, tree);
    else if (type == MULTICREMENT)
        return is_multicrement(tok, tree);
    else if (type == DIVCREMENT)
        return is_divcrement(tok, tree);
    else {
        printf("PARSER ERROR: In line %d, where lexeme=<%s>. Expected any type of <CREMENT> found <%s>", 
        (*tok)->line, (*tok)->lexeme, type2char((*tok)->token_type));
        return PARSING_ERROR;
    }
}

/* Function Checker to check operators */
int is_operator (t_list** tok, p_tree** tree) {
    enum TokenType type;

    type = (*tok)->token_type;
    if (type == PLUS)
        return is_plus(tok, tree);
    else if (type == MINUS)
        return is_minus(tok, tree);
    else if (type == MUL)
        return is_mul(tok, tree);
    else if (type == DIV)
        return is_div(tok, tree);
    else if (type == MODULO)
        return is_modulo(tok, tree);
    else
        return is_logical_op(tok, tree);
}

int is_var_binding(int type1, int type2) {
    if (CHAR == type1 || type1 == STRING || type1 == INT || type1 == REAL || type1 == BOOL) {
       return type2 == IDENTIFIER;
    }
    return 0;
}


/* Function checker to check expressions with/out signs and the precedence of what number(pow)*/
int is_number(t_list** tok, p_tree** tree) {
    // Primary condition if no tokens are found
    if (*tok == NULL)
        return PARSING_ERROR;

    p_tree *sign, *numeric;
    int status, has_sign;

    if (( *tree = create_tree_entry("NUMBER", OBJECT, 0) ) == NULL ) {
        printf("MEMORY ERR: output container not created.\n");
        return MEMORY_ERROR;
    }

    status = SUBTREE_OK;
    has_sign = 1;
    
    // Checking if expression has sign 
    sign = create_tree();
    
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

    // Checking if expression type it has containing it 
    numeric = create_tree();

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

    if (( *tree = create_tree_entry("OBJ", OBJECT, 0) ) == NULL ) {
        printf("MEMORY ERR: object container not created.\n");
        return MEMORY_ERROR;
    }

    subtree = create_tree();

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
             curr->token_type == REAL_CONSTANT) {
        status = is_number(tok, &subtree);
    } else if (curr->token_type == TRUE)
        status = is_true(tok, &subtree);
    else if (curr->token_type == FALSE)
        status = is_false(tok, &subtree);
    else if (curr->token_type == ENDLINE) {
        printf("PARSING ERROR: In line %d, where lexeme=\\n, missing type <OBJ> FOUND <ENDLINE> within the statement", curr->line);
        status = PARSING_ERROR;
    } else if (curr->token_type == OPEN_PAR) {
        printf("PARSER ERROR: In line %d, where lexeme=( .Expecting data of type <Obj> found <OPEN_PAR>", curr->line);
        status = PARSING_ERROR;
    } else if (curr->token_type == CLOSE_PAR) {
        printf("PARSER ERROR: In line %d, where lexeme=). Expecting data of Type <Obj> found <CLOSE_PAR>", curr->line);
        status = PARSING_ERROR;
    } else if (match_arithmetic_type(curr->token_type)) {
        printf("PARSER ERROR: In line %d, where lexeme=%s. Expecting data of type <Obj> found <%s>", 
        curr->line, curr->lexeme, type2char(curr->token_type));
    }

    else   
        status = PARSING_ERROR;

    if (status == SUBTREE_OK)
        (*tree)->child = subtree;
    else
        free_parse_tree(subtree);
    return status;
}

/* Function Checker if string has values to format */ 
int is_quoted_string(t_list** tok, p_tree** tree) {
    // Primary condition if no tokens are found
    if (*tok == NULL)
        return PARSING_ERROR;
    
    p_tree *char_seq, *comma, *obj, *last;
    int status, nVar, nObj;

    status = SUBTREE_OK;
    nVar = nObj = 0;

    //Initial Tree declaring we are in a String Container
    if (( *tree = create_tree_entry("STRING_CON", STRING_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: string container not created.\n");
        return MEMORY_ERROR;
    }
    
    char_seq = create_tree();
    
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

    if ((*tok)->token_type == ENDLINE) {
        if (nVar > 0) {
            return PARSING_ERROR;
        }
        else 
            return SUBTREE_OK;
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
        obj = create_tree();
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

/* Function checker if string is concatenated*/
int is_str_concat (t_list** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    p_tree *quotedstr, *plus, *last, *obj;
    int status;

    if (( *tree = create_tree_entry("CONCAT", CONCAT, 0) ) == NULL ) {
        printf("MEMORY ERR: output container not created.\n");
        return MEMORY_ERROR;
    }
    status = SUBTREE_OK;

    quotedstr = create_tree();
    status = is_quoted_string(tok, &quotedstr);
    if (status != SUBTREE_OK) {
        free_parse_tree(quotedstr);
        return status;
    }
    (*tree)->child = quotedstr;
    last = quotedstr;

    if ((*tok)->token_type == ENDLINE)
        return SUBTREE_OK;

    while((*tok)->token_type == PLUS) {
        plus = create_tree();
        status = is_plus(tok, &plus);
        if (status != SUBTREE_OK) {
            free_parse_tree(plus);
            return status;
        }
        last->sibling = plus;
        last = plus;

        obj = create_tree();
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(obj);
            return status;
        }
        last->sibling = obj;
        last = obj;
        
    }
    return status;
}



