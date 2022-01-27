/* 
* File        : grammar_validator.h
* Description : This file contains functions related to validate tokens. 
*               The functions implemented are:
*               is_program(), create_entry(), insert(), free_parse_tree(), display() 
*/

#include "./token_validator.h"


//Match Compound operations
/* matches operator type */
int match_operator_type (enum TokenType type) {
    return (match_arithmetic_type(type) ||
            match_logical_type(type));
}

// Expressions Functionalities
/* Function that Checks if the expression is compound */
int is_base_expr (t_list** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    int status;
    p_tree *lpar, *rpar, *subexpr, *obj;
    status = SUBTREE_OK;

    (*tree)->token = (char[1]){'\0'};
    (*tree)->type = BASE_EXP;

    if ((*tok)->token_type == OPEN_PAR) {
        // is a sub expression
        
        if ((lpar = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_open_par(tok, &lpar);
        if (status != SUBTREE_OK){
            free_parse_tree(lpar);
            return status;
        }
        (*tree)->child = lpar;

        
        if ((subexpr = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_expression(tok, &subexpr);
        if (status != SUBTREE_OK){
            free_parse_tree(subexpr);
            return status;
        }
        lpar->sibling = subexpr;

        
        if ((rpar = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_close_par(tok, &rpar);
        if (status != SUBTREE_OK){
            free_parse_tree(rpar);
            return status;
        }
        subexpr->sibling = rpar;
    }
    else {
        // if the expression is just an Obj
        // An object is any type of value that a user inputs 
        // (e.g.) x -> object-> identifier 
        //        54.5 -> object -> number -> real
        if (obj == NULL)
            return MEMORY_ERROR;
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(obj);
            return status;
        }
        (*tree)->child = obj;
    }
    return status;
}

/* Checker of Operators  within an expression*/
int is_term (t_list** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    int status;
    enum TokenType type;
    p_tree *base, *op, *term;

    status = SUBTREE_OK;
    (*tree)->token = (char[1]){'\0'};
    (*tree)->type = TERM;

    if ((base = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_base_expr(tok, &base);
    if (status != SUBTREE_OK){
        free_parse_tree(base);
        return status;
    }
    (*tree)->child = base;

    // The remainder of a Term is optional
    type = (*tok)->token_type;

    if (match_term_type(type)){
        if ((op = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_operator(tok, &op);
        if (status != SUBTREE_OK){
            free_parse_tree(op);
            return status;
        }
        base->sibling = op;

        if ((term = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_term(tok, &term);
        if (status != SUBTREE_OK){
            free_parse_tree(term);
            return status;
        }
        op->sibling = term;
    }
    return status;
}

/* Another Checker of Operators with extended (+,-)  within an expression*/
int is_predicate (t_list** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    p_tree *term, *op, *pred;
    enum TokenType type;
    int status;

    status = SUBTREE_OK;
    (*tree)->token = (char[1]){'\0'};
    (*tree)->type = PREDICATE;

    if ((term = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_term(tok, &term);
    if (status != SUBTREE_OK){
        free_parse_tree(term);
        return status;
    }
    (*tree)->child = term;

    // The remainder of Pred is optional
    // (only if there is '+' | '-')
    type = (*tok)->token_type;
    if (match_arithmetic_type(type) &&
        !match_term_type(type)){
        if ((op = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_operator(tok, &op);
        if (status != SUBTREE_OK){
            free_parse_tree(op);
            return status;
        }
        term->sibling = op;

        if ((pred = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_predicate(tok, &pred);
        if (status != SUBTREE_OK){
            free_parse_tree(pred);
            return status;
        }
        op->sibling = pred;
    }

    return status;
}

/* Checker of the whole expression */
int is_expression (t_list** tok, p_tree** tree) {
    if (*tok == NULL)
        return PARSING_ERROR;

    p_tree *pred, *op, *expr;
    enum TokenType type;
    int status;

    status = SUBTREE_OK;
    (*tree)->token = (char[1]){'\0'};
    (*tree)->type = EXPR;
    

    if ((pred = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_predicate(tok, &pred);
    if (status != SUBTREE_OK){
        free_parse_tree(pred);
        return status;
    }
    (*tree)->child = pred;

    // The remainder of Expr is optional
    // (only if there is a conditional operator)
    type = (*tok)->token_type;
    if (match_logical_type(type)){
        if ((op = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_operator(tok, &op);
        if (status != SUBTREE_OK){
            free_parse_tree(op);
            return status;
        }
        pred->sibling = op;

        if ((expr = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_expression(tok, &expr);
        if (status != SUBTREE_OK){
            free_parse_tree(expr);
            return status;
        }
        op->sibling = expr;
    }
    return status;
}

/* ASSIGNMENT AND I/O STATEMENTS */

/* Function checker to see if the line statement is following the rules of assignment statement*/
int is_assignment_stmt(t_list** tok, p_tree** tree) {
    p_tree *datatype, *var1, *eq, *expression;
    int status;

    (*tree)->token = (char[1]) {'\0'};
    (*tree)->type = ASSIGN_CON;

    if ((datatype = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_datatype(tok, &datatype);
    if (status != SUBTREE_OK) {
        free_parse_tree(datatype);
        return PARSING_ERROR;
    }
    (*tree)->child = datatype;

    if ((var1 = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_identifier(tok, &var1);
    if (status != SUBTREE_OK) {
        free_parse_tree(var1);
        return PARSING_ERROR;
    }
    datatype->sibling = var1;

    if ((eq = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_assign(tok, &eq);
    if (status != SUBTREE_OK) {
        free_parse_tree(eq);
        return PARSING_ERROR;
    }
    var1->sibling = eq;

    if ((expression = create_tree()) == NULL)
        return MEMORY_ERROR;

    status = is_expression(tok, &expression);
    if (status != SUBTREE_OK) {
        free_parse_tree(expression);
        return PARSING_ERROR;
    }
    eq->sibling = expression;
    return SUBTREE_OK;
}

/* Function checker to see if the line statement is following the rules of input statement*/
int is_input_stmt(t_list** tok, p_tree** tree) {
    // Create subtree
    p_tree *input, *var, *as, *datatype;
    int status;
   
    (*tree)->token = (char[1]){'\0'};
    (*tree)->type = INPUT_CON;

    if ((input = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_input(tok, &input);
    if (status != SUBTREE_OK) {
        free_parse_tree(input);
        return status;
    }
    (*tree)->child = input;

    if ((var = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_identifier(tok, &var);
    if (status != SUBTREE_OK) {
        free_parse_tree(var);
        return status;
    }
    input->sibling = var;

    if ((as = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_as(tok, &as);
    if (status != SUBTREE_OK) {
        free_parse_tree(as);
        return status;
    }
    input->sibling = as;

    if ((as = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_as(tok, &as);
    if (status != SUBTREE_OK) {
        free_parse_tree(as);
        return status;
    }
    input->sibling = as;

    if ((datatype = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_datatype(tok, &datatype);
    if (status != SUBTREE_OK) {
        free_parse_tree(datatype);
        return PARSING_ERROR;
    }
    as->sibling = datatype;

    return SUBTREE_OK;
}

/* Function checker to see if the line statement is following the rules of input statement*/
int is_output_stmt(t_list** tok, p_tree** tree) {
    // Create subtree
    p_tree *print, *obj;
    int status;
    
    (*tree)->token = (char[1]){'\0'};
    (*tree)->type = OUTPUT_CON;

    if ((print = create_tree()) == NULL)
        return MEMORY_ERROR;
    status = is_print(tok, &print);
    if (status != SUBTREE_OK) {
        free_parse_tree(print);
        return status;
    }
    (*tree)->child = print;

    if ((*tok)->token_type == STR_CONSTANT) {
        if ((obj = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_str_concat(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(obj);
            return status;
        }
        print->sibling = obj;

       
    } else {
        if ((obj = create_tree()) == NULL)
            return MEMORY_ERROR;
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(obj);
            return status;
        }
        print->sibling = obj;
    }
    
    return status;
}

/*
// Validate if the rule of variable binding is met. 
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

    // Check if entry is created successfully 
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

    //
    // Nested call to identify grammar tokens return pointer to subtree(s)
    // or NULL is parsing/memory error happened.
    //
    
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
*/