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
    
    if (( *tree = create_tree_entry("BASE_EXP", BASE_EXP, 0) ) == NULL ) {
        printf("MEMORY ERR: base_expr container not created.\n");
        return MEMORY_ERROR;
    }

    // if a multiple expression
    if ((*tok)->token_type == OPEN_PAR) {
        // is a sub expression
        
        lpar = create_tree();
        status = is_open_par(tok, &lpar);
        if (status != SUBTREE_OK){
            free_parse_tree(lpar);
            return status;
        }
        (*tree)->child = lpar;

        
        subexpr = create_tree();
        status = is_expression(tok, &subexpr);
        if (status != SUBTREE_OK){
            free_parse_tree(subexpr);
            return status;
        }
        lpar->sibling = subexpr;

        
        rpar = create_tree();
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
        printf("went through obj\n");
        obj = create_tree();
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

    if (( *tree = create_tree_entry("TERM", TERM, 0) ) == NULL ) {
        printf("MEMORY ERR: term container not created.\n");
        return MEMORY_ERROR;
    }

    printf("went through term\n");
    base = create_tree();
    status = is_base_expr(tok, &base);
    if (status != SUBTREE_OK){
        free_parse_tree(base);
        return status;
    }
    (*tree)->child = base;

    // The remainder of a Term is optional
    type = (*tok)->token_type;

    if (match_term_type(type)){
        op = create_tree();
        status = is_operator(tok, &op);
        if (status != SUBTREE_OK){
            free_parse_tree(op);
            return status;
        }
        base->sibling = op;

        term = create_tree();
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

    if (( *tree = create_tree_entry("PREDICATE", PREDICATE, 0) ) == NULL ) {
        printf("MEMORY ERR: predicate container not created.\n");
        return MEMORY_ERROR;
    }
    printf("went through predicate\n");
    term = create_tree();
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
        op = create_tree();
        status = is_operator(tok, &op);
        if (status != SUBTREE_OK){
            free_parse_tree(op);
            return status;
        }
        term->sibling = op;

        printf("Went through arithmetic +-\n");

        pred = create_tree();
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

    if (( *tree = create_tree_entry("EXPR", EXPR, 0) ) == NULL ) {
        printf("MEMORY ERR: expression container not created.\n");
        return MEMORY_ERROR;
    }

    printf("went through expr\n");
    pred = create_tree();
    status = is_predicate(tok, &pred);
    if (status != SUBTREE_OK){
        free_parse_tree(pred);
        return status;
    }
    (*tree)->child = pred;

    //  if there is a conditional operator
    type = (*tok)->token_type;
    
    if (match_operator_type(type)){
        op = create_tree();
        status = is_operator(tok, &op);
        if (status != SUBTREE_OK){
            free_parse_tree(op);
            return status;
        }
        pred->sibling = op;

        expr = create_tree();
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
    t_list * curr;
    p_tree *datatype, *var1, *eq, *expression, *comma, *other, *endline;
    int status;

    if (( *tree = create_tree_entry("ASSIGN_CON", ASSIGN_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: assign container not created.\n");
        return MEMORY_ERROR;
    }

    if (match_datatype((*tok)->token_type)) {
        datatype = create_tree();
        status = is_datatype(tok, &datatype);
        if (status != SUBTREE_OK) {
            free_parse_tree(datatype);
            return PARSING_ERROR;
        }
        (*tree)->child = datatype;
    }
    

    
    var1 = create_tree();
    status = is_identifier(tok, &var1);
    if (status != SUBTREE_OK) {
        free_parse_tree(var1);
        return PARSING_ERROR;
    }
    datatype->sibling = var1;

    if((*tok)->token_type == ENDLINE || (*tok) == NULL) {
        printf("passed through this line");
        return SUBTREE_OK;
    }

    curr = *tok;
    if (curr->token_type == ASSIGN) {
        eq = create_tree();
        status = is_assign(tok, &eq);
        if (status != SUBTREE_OK) {
            free_parse_tree(eq);
            return PARSING_ERROR;
        }
        var1->sibling = eq;

        expression = create_tree();
        status = is_expression(tok, &expression);
        if (status != SUBTREE_OK) {
            free_parse_tree(expression);
            return PARSING_ERROR;
        }
        eq->sibling = expression;

        return status;
    }
    
    if (curr->token_type == COMMA) {
        while (curr->token_type != ENDLINE) {
            comma = create_tree();
            status = is_comma(tok, &comma);
            if (status != SUBTREE_OK) {
                free_parse_tree(var1);
                return PARSING_ERROR;
            }
            var1->sibling = comma;

            var1 = create_tree();
            status = is_identifier(tok, &var1);
            if (status != SUBTREE_OK) {
                free_parse_tree(var1);
                return PARSING_ERROR;
            }
            comma->sibling = var1;
            curr = *tok;
        }
        return status;
    }

    printf("PARSING ERROR: Symbol <%s> did not match Assignment or declaration grammar. please check again.\n", type2char((*tok)->token_type));
    return PARSING_ERROR;
}

/* Function checker to see if the line statement is following the rules of input statement*/
int is_input_stmt(t_list** tok, p_tree** tree) {
    // Create subtree
    p_tree *input, *var, *as, *datatype;
    int status;
   
    if (( *tree = create_tree_entry("INPUT_CON", INPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: assign container not created.\n");
        return MEMORY_ERROR;
    }

    input = create_tree();
    status = is_input(tok, &input);
    if (status != SUBTREE_OK) {
        free_parse_tree(input);
        return status;
    }
    (*tree)->child = input;

    var = create_tree();
    status = is_identifier(tok, &var);
    if (status != SUBTREE_OK) {
        free_parse_tree(var);
        return status;
    }
    input->sibling = var;

    as = create_tree();
    status = is_as(tok, &as);
    if (status != SUBTREE_OK) {
        free_parse_tree(as);
        return status;
    }
    input->sibling = as;

    datatype = create_tree();
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
    p_tree *print, *open_par, *close_par, *obj;
    int status;
    
    if (( *tree = create_tree_entry("OUTPUT_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: output container not created.\n");
        return MEMORY_ERROR;
    }

    print = create_tree();
    status = is_print(tok, &print);
    if (status != SUBTREE_OK) {
        free_parse_tree(print);
        return status;
    }
    (*tree)->child = print;

    open_par = create_tree();
    status = is_open_par(tok, &open_par);
    if (status != SUBTREE_OK) {
        free_parse_tree(print);
        return status;
    }
    print->child = open_par;

    
    if ((*tok)->token_type == STR_CONSTANT) {
        obj = create_tree();
        status = is_str_concat(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(obj);
            return status;
        }
        print->sibling = obj;

       
    } else {
        obj = create_tree();
        status = is_obj(tok, &obj);
        if (status != SUBTREE_OK) {
            free_parse_tree(obj);
            return status;
        }
        print->sibling = obj;
    }

    close_par = create_tree();
    status = is_close_par(tok, &close_par);
    if (status != SUBTREE_OK) {
        free_parse_tree(print);
        return status;
    }
    open_par->child = close_par;
    
    return status;
}

int is_counter(t_list** tok, p_tree** tree){
    p_tree *datatype, *identifier, *eq, *expression;
    t_list* curr;
    int status;

    printf("Going through counter\n");

    if (( *tree = create_tree_entry("COUNTER", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: counter container not created.\n");
        return MEMORY_ERROR;
    }

    curr = *tok;

    if (match_datatype(curr->token_type)){
        datatype = create_tree();
        status = is_datatype(tok, &datatype);
        if (status != SUBTREE_OK) {
            free_parse_tree(datatype);
            return status;
        }

        (*tree)->child = datatype;

        identifier = create_tree();
        status = is_identifier(tok, &identifier);
        if (status != SUBTREE_OK) {
            free_parse_tree(identifier);
            return status;
        }

        datatype->sibling = identifier;
    } else {
        identifier = create_tree();
        status = is_identifier(tok, &identifier);
        if (status != SUBTREE_OK) {
            free_parse_tree(identifier);
            return status;
        }

        (*tree)->child = identifier;
    }

    curr = *tok;
    if (curr->token_type == ASSIGN){
        eq = create_tree();
        status = is_assign(tok, &eq);
        if (status != SUBTREE_OK) {
            free_parse_tree(eq);
            return status;
        }

        identifier->sibling = eq;

        expression = create_tree();
        status = is_expression(tok, &expression);
        if (status != SUBTREE_OK) {
            free_parse_tree(expression);
            return status;
        }

        identifier->sibling = expression;
    }

    printf("Went through counter\n");

    return status;

}

int is_if_stmt(t_list** tok, p_tree** tree){
    p_tree *if_kywrd, *expression, *then, *endline, *body, *else_kywrd, *endif;
    int status;

    if (( *tree = create_tree_entry("IF_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: if condition container not created.\n");
        return MEMORY_ERROR;
    }

    if_kywrd = create_tree();
    status = is_if(tok, &if_kywrd);
    if (status != SUBTREE_OK) {
        free_parse_tree(if_kywrd);
        return status;
    }
    (*tree)->child = if_kywrd;

    printf("Went through if\n");

    expression = create_tree();
    status = is_expression(tok, &expression);
    if (status != SUBTREE_OK) {
        free_parse_tree(expression);
        return status;
    }
    if_kywrd->sibling = expression;

    printf("Went through expression\n");

    then = create_tree();
    status = is_then(tok, &then);
    if (status != SUBTREE_OK) {
        free_parse_tree(then);
        return status;
    }
    expression->sibling = then;

    printf("Went through then\n");

    endline = create_tree();
    status = is_endline(tok, &endline);
    if (status != SUBTREE_OK) {
        free_parse_tree(endline);
        return status;
    }
    then->sibling = endline;

    printf("Went through endline\n");
    
    body = create_tree();
    status = is_block(tok, &body, ENDLOOP);
    if (status != SUBTREE_OK) {
        free_parse_tree(body);
        return status;
    }
    endline->sibling = body;

    printf("Went through body\n");

    else_kywrd = create_tree();
    status = is_else(tok, &else_kywrd);
    if (status != SUBTREE_OK) {
        free_parse_tree(else_kywrd);
        return status;
    }
    body->sibling = else_kywrd;

    printf("Went through ELSE\n");

    endif = create_tree();
    status = is_endif(tok, &endif);
    if (status != SUBTREE_OK) {
        free_parse_tree(endif);
        return status;
    }
    else_kywrd->sibling = endif;

    printf("Went through endif\n");
}

int is_elseif_stmt(t_list** tok, p_tree** tree) {
    p_tree *elseif, *expression, *then,*endline, *body;
    int status;

    if (( *tree = create_tree_entry("ELSEIF_CON", OUTPUT_CON, 0) ) == NULL) {
        printf("MEMORY ERR: elseif container not created.\n");
        return MEMORY_ERROR;
    }

    elseif = create_tree();
    status = is_elseif(tok, &elseif);
    if (status != SUBTREE_OK) {
        free_parse_tree(elseif);
        return status;
    }
    (*tree)->child = elseif;

    printf("Went through ELSEIF\n");

    expression = create_tree();
    status = is_expression(tok, &expression);
    if (status != SUBTREE_OK) {
        free_parse_tree(expression);
        return status;
    }
    elseif->sibling = expression;

    printf("Went through expression\n");

    then = create_tree();
    status = is_then(tok, &then);
    if (status != SUBTREE_OK) {
        free_parse_tree(then);
        return status;
    }
    expression->sibling = then;

    endline = create_tree();
    status = is_endline(tok, &endline);
    if (status != SUBTREE_OK) {
        free_parse_tree(endline);
        return status;
    }
    then->sibling = endline;

    printf("Went through endline\n");
    
    body = create_tree();
    status = is_block(tok, &body, ENDLOOP);
    if (status != SUBTREE_OK) {
        free_parse_tree(body);
        return status;
    }
    endline->sibling = body;

    printf("Went through body\n");
}

int is_else_stmt(t_list** tok, p_tree** tree) {
    p_tree *else_kywrd, *endline, *body, *endif;
    int status;
    
    if (( *tree = create_tree_entry("ELSE CON", OUTPUT_CON, 0) ) == NULL) {
        printf("MEMORY ERR: else statement contatiner not created.\n");
        return MEMORY_ERROR;
    }

    else_kywrd = create_tree();
    status = is_else(tok, &else_kywrd);
    if (status != SUBTREE_OK) {
        free_parse_tree(else_kywrd);
        return status;
    }
    (*tree)->child = else_kywrd;
    
    printf("Went through ELSE\n");

    endline = create_tree();
    status = is_endline(tok, &endline);
    if (status != SUBTREE_OK) {
        free_parse_tree(endline);
        return status;
    }
    else_kywrd->sibling = endline;

    printf("Went through endline\n");
    
    body = create_tree();
    status = is_block(tok, &body, ENDLOOP);
    if (status != SUBTREE_OK) {
        free_parse_tree(body);
        return status;
    }
    endline->sibling = body;

    printf("Went through body\n");

    endif = create_tree();
    status = is_endif(tok, &endif);
    if (status != SUBTREE_OK) {
        free_parse_tree(endif);
        return status;
    }
    body->sibling = endif;

    printf("Went through endif\n");
}

int is_while_loop(t_list** tok, p_tree** tree){
    p_tree *while_kywrd, *expression, *endline, *body, *end_loop;
    int status;

    if (( *tree = create_tree_entry("WHILE_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: while loop container not created.\n");
        return MEMORY_ERROR;
    }

    while_kywrd = create_tree();
    status = is_while(tok, &while_kywrd);
    if (status != SUBTREE_OK) {
        free_parse_tree(while_kywrd);
        return status;
    }

    (*tree)->child = while_kywrd;

    printf("Went through while\n");

    expression = create_tree();
    status = is_expression(tok, &expression);
    if (status != SUBTREE_OK) {
        free_parse_tree(expression);
        return status;
    }

    while_kywrd->sibling = expression;

    printf("Went through expression\n");

    endline = create_tree();
    status = is_endline(tok, &endline);
    if (status != SUBTREE_OK) {
        free_parse_tree(endline);
        return status;
    }

    expression->sibling = endline;

    printf("Went through endline\n");

    body = create_tree();
    status = is_block(tok, &body, ENDLOOP);
    if (status != SUBTREE_OK) {
        free_parse_tree(body);
        return status;
    }

    endline->sibling = body;

    printf("Went through body\n");

    end_loop = create_tree();
    status = is_endloop(tok, &end_loop);
    if (status != SUBTREE_OK) {
        free_parse_tree(end_loop);
        return status;
    }

    body->sibling = end_loop;

    printf("Went through end_loop\n");

}


int is_do_while_loop(t_list** tok, p_tree** tree){
    p_tree *do_kywrd, *while_kywrd, *expression, *endline, *body, *endline_2, *end_loop;
    int status;

    if (( *tree = create_tree_entry("WHILE_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: while loop container not created.\n");
        return MEMORY_ERROR;
    }

    do_kywrd = create_tree();
    status = is_do(tok, &do_kywrd);
    if (status != SUBTREE_OK) {
        free_parse_tree(do_kywrd);
        return status;
    }
    (*tree)->child = do_kywrd;

    printf("Went through do\n");

    endline = create_tree();
    status = is_endline(tok, &endline);
    if (status != SUBTREE_OK) {
        free_parse_tree(endline);
        return status;
    }
    do_kywrd->sibling = endline;

    printf("Went through endline\n");

    body = create_tree();
    status = is_block(tok, &body);
    if (status != SUBTREE_OK) {
        free_parse_tree(body);
        return status;
    }
    endline->sibling = body;

    printf("Went through body\n");

    while_kywrd = create_tree();
    status = is_while(tok, &while_kywrd);
    if (status != SUBTREE_OK) {
        free_parse_tree(while_kywrd);
        return status;
    }
    endline->sibling = while_kywrd;

    printf("Went through while_kywrd\n");

    endline_2 = create_tree();
    status = is_endline(tok, &endline_2);
    if (status != SUBTREE_OK) {
        free_parse_tree(endline_2);
        return status;
    }
    while_kywrd->sibling = endline_2;

    printf("Went through endline_2\n");

    end_loop = create_tree();
    status = is_endloop(tok, &end_loop);
    if (status != SUBTREE_OK) {
        free_parse_tree(end_loop);
        return status;
    }
    endline_2->sibling = end_loop;

    printf("Went through end_loop\n");
}


int is_for_loop(t_list** tok, p_tree** tree){
    p_tree *for_kywrd, *counter, *to, *max_expression, *by, *by_expression, *end_line, *body, *end_loop;
    t_list *curr;
    int status;
    
    if (( *tree = create_tree_entry("FOR_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: for loop container not created.\n");
        return MEMORY_ERROR;
    }

    for_kywrd = create_tree();
    status = is_for(tok, &for_kywrd);
    if (status != SUBTREE_OK) {
        free_parse_tree(for_kywrd);
        return status;
    }

    (*tree)->child = for_kywrd;

    printf("Went through for\n");

    counter = create_tree();
    status = is_counter(tok, &counter);
    if (status != SUBTREE_OK) {
        free_parse_tree(counter);
        return status;
    }
    for_kywrd->sibling = counter;    

    to = create_tree();
    status = is_to(tok, &to);
    if (status != SUBTREE_OK) {
        free_parse_tree(to);
        return status;
    }
    counter->sibling = to;

    printf("Went through to\n");

    max_expression = create_tree();
    status = is_expression(tok, &max_expression);
    if (status != SUBTREE_OK) {
        free_parse_tree(max_expression);
        return status;
    }
    to->sibling = max_expression;

    printf("Went through max_expression\n");

    curr = *tok;
    printf("%d %d\n", curr->token_type, BY);

    if (curr->token_type == BY){
        by = create_tree();
        status = is_by(tok, &by);
        if (status != SUBTREE_OK) {
            free_parse_tree(by);
            return status;
        }
        max_expression->sibling = by;

        printf("Went through by\n");

        by_expression = create_tree();
        status = is_expression(tok, &by_expression);
        if (status != SUBTREE_OK) {
            free_parse_tree(by_expression);
            return status;
        }
        by->sibling = by_expression;

        printf("Went through by_expression\n");

        end_line = create_tree();
        status = is_endline(tok, &end_line);
        if (status != SUBTREE_OK) {
            free_parse_tree(end_line);
            return status;
        }
        by->sibling = end_line;

        printf("Went through end_line\n");

    } else {
        end_line = create_tree();
        status = is_endline(tok, &end_line);
        if (status != SUBTREE_OK) {
            free_parse_tree(end_line);
            return status;
        }
        max_expression->sibling = end_line;

        printf("Went through end_line\n");

    }

    body = create_tree();
    status = is_block(tok, &body, ENDLOOP);
    if (status != SUBTREE_OK) {
        free_parse_tree(body);
        return status;
    }
    end_line->sibling = body;

    end_loop = create_tree();
    status = is_endloop(tok, &end_loop);
    if (status != SUBTREE_OK) {
        free_parse_tree(end_loop);
        return status;
    }
    body->sibling = end_loop;

    printf("Went through end_loop\n");

    return status;
}

int is_block(t_list** tok, p_tree** tree, int terminator){
    int status;
    t_list *curr;
    
    if (( *tree = create_tree_entry("BLOCK_CON", OUTPUT_CON, 0) ) == NULL ) {
        printf("MEMORY ERR: block container not created.\n");
        return MEMORY_ERROR;
    }

    printf("Went through block\n");

    curr = *tok;

    while (curr->token_type != terminator){
        p_tree *line, *end_line;

        line = create_tree();

        status = is_line(tok, &line);
        if (status != SUBTREE_OK) {
            free_parse_tree(line);
            return status;
        }

        (*tree)->child = line;

        printf("Went through line\n");

        end_line = create_tree();
        status = is_endline(tok, &end_line);
        if (status != SUBTREE_OK) {
            free_parse_tree(end_line);
            return status;
        }
        line->sibling = end_line;

        printf("Went through end_line\n");

        curr = *tok;
    }

    return status;
}


// Check which type of line should we check the grammar.
int is_line(t_list** tok, p_tree** line) {
    
    p_tree* subtree;
    t_list* newTok;
    int status;
    t_list* curr;

    // Check if entry is created successfully 
    if (( *line = create_tree_entry("Line", LINE, 0) ) == NULL ) {
        printf("line not created");
        return MEMORY_ERROR;
    }
    
    curr = *tok;

    if(is_var_binding(curr->token_type, curr->successor->token_type) ||
    curr-> token_type == IDENTIFIER) {
        status = is_assignment_stmt(tok, &subtree);
    } else if(curr->token_type == INPUT) {
        status = is_input_stmt(tok, &subtree);
    } else if (curr->token_type == PRINT) {
        status = is_output_stmt(tok, &subtree);
    } else if (curr->token_type == COMMENT || curr->token_type == ENDCOMMENT) {
        *tok = curr->successor;
        status = SUBTREE_OK;
    } else if (curr->token_type == ENDLINE) {
        status = is_endline(tok, &subtree);
    }
    else if (curr->token_type == FOR){
        status = is_for_loop(tok, &subtree);
    }
    else if (curr->token_type == WHILE){
        status = is_while_loop(tok, &subtree);
    }
    else if (curr->token_type == DO){
        status = is_do_while_loop(tok, &subtree);
    }
    else if (curr->token_type == IF) {
        status = is_if_stmt(tok, &subtree);
    }
    else if (curr->token_type == ELSEIF) {
        status = is_elseif_stmt(tok, &subtree);
    }
    else if (curr->token_type == ELSE) {
        status = is_else_stmt(tok, &subtree);
    }
    /* else if (curr->token_type == IF || 
    curr->token_type == SWITCH) {
        status = is_cond(tok, &subtree);
    } else if (curr->token_type == WHILE || 
    curr->token_type == DO || 
    curr->token_type == FOR) {
        status = is_loop(tok, &subtree);
    }*/ else {
        printf("SYNTAX ERROR: No grammar match rule.");
        status = PARSING_ERROR;
    }

    (*line)->child = subtree;
    return status;
}


int is_program(t_list** head, p_tree** tree) {
    t_list* tok, *temp_list;
    int status, child;
    p_tree *current, *temp;
    p_tree *line, *endline;

    temp = create_tree_entry("PROG", PROG, 0);
    if (temp  == NULL ) {
        printf("program not created");
        return MEMORY_ERROR;
    }

    if (*tree == NULL) {
        *tree = temp;

        current = *tree;
        temp_list = *head;

        //
        // Nested call to identify grammar tokens return pointer to subtree(s)
        // or NULL is parsing/memory error happened.
        //
        
        child = 1; // true - the first line is always a child of Program
        // A program is a (possibly empty) sequence of 'line' 'end<token>'

        while ((temp_list) != NULL) {
            status = is_line(&temp_list, &line);
            if (child) {
                current->child = line;
                child = !child;
            } else {
                current->sibling = line;
            }


            if (status == MEMORY_ERROR) {
                printf("Program Out of Memory.\n");
                return MEMORY_ERROR;
            } 
            if (status == PARSING_ERROR){
                printf("PARSER ERROR: \n");
                return PARSING_ERROR;
            }
    
        }
        return SUBTREE_OK;
    }
    
    return MEMORY_ERROR;
    
}


void run_with_stat(t_list* head) {
    p_tree* tree;
    int status;

    tree = create_tree();

    status = is_program(&head, &tree);
    printf("STATUS RETURNED HERE: %d", status);
    if(status == SUBTREE_OK)
        print_parse_tree(tree);
    



}




/*
// Validate if the rule of variable binding is met. 
int is_var_binding(int type1, int type2) {
    if (is_datatype(type1)) {
       return type2 == IDENTIFIER; 
    }
    return 0;
}





*/