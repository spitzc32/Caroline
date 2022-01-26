/* 
* File        : grammar_validator.h
* Description : This file contains functions related to validate tokens. 
*               The functions implemented are:
*               is_program(), create_entry(), insert(), free_parse_tree(), display() 
*/

#include "./token_validator.h"


/* Validate if the rule of variable binding is met. */
int is_var_binding(int type1, int type2) {
    if (is_datatype(type1)) {
       return type2 == IDENTIFIER; 
    }
    return 0;
}


int is_line(t_list** tok, p_tree** line) {
    
    p_tree* subtree;
    t_list* newTok;
    int status;
    t_list* curr;

    /* Check if entry is created successfully */
    if (( *line = create_tree_entry("Line", Line) ) == NULL )
        return MEMORY_ERROR;
    
    curr = *tok;

    if(is_var_binding(curr->token_type, curr->successor)) {
        status = is_identifier(tok, &subtree)
    } else if(curr->token_type == INPUT) {
        status = is_inputc(tok, &subtree);
    } else if (curr->token_type == PRINT) {
        status = is_output(tok, &subtree);
    } else if (curr->token_type == IF || 
    curr->token_type == SWITCH) {
        status = is_cond(tok, &subtree);
    } else if (curr->token_type == WHILE || 
    curr->token_type == DO || 
    curr->token_type == FOR) {
        status = is_loop(tok, &subtree);
    } else {
        printf("SYNTAX ERROR: No grammar match rule.");
        status = PARSING_ERROR;
    }

    (*line)->child = subtree;
    return status;
}

int is_program(t_list** head, p_tree** tree) {
    t_list* tok;
    int status, child;
    p_tree *current;
    p_tree *line, *endline;

    if (( *tree = create_tree_entry("PROG", PROG) ) == NULL )
        return MEMORY_ERROR;

    current = *tree;

    /*
     * Nested call to identify grammar tokens return pointer to subtree(s)
     * or NULL is parsing/memory error happened.
    */
    
    child = 3; // true - the first line is always a child of Program
    // A program is a (possibly empty) sequence of 'line' 'end<token>'

    while ((*head) != NULL ) {
        status = is_line(head, &line);

        if (child == 3) {
            current->child = line;
            child = status;
        } else {
            current->sibling = line;
        }

        if (status == MEMORY_ERROR) {
            printf("Program Out of Memory.");
            break;
        } 
        if (status == PARSING_ERROR){
            printf("PARSER ERROR: \n");
            break;
        }
   
    }
    free_parse_tree(line);
}