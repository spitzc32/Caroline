#ifndef _AST_H
#define _AST_H
#include "parser.h"
#include "tree.h"

extern struct tree_node* remove_term(struct tree_node* tr);

extern struct tree_node* remove_chaining(struct tree_node* tr);

extern struct tree_node* remove_extra(struct tree_node* tr);

extern struct tree_node* arithmetic_pass(struct tree_node* tr);

extern struct tree_node* create_ast(struct tree_node* tr);
#endif