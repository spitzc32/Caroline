/* 
* File        : parsetree.h
* Description : This file contains functions related to organised a Parse tree. 
*               The functions implemented are:
*               create_tree(), create_entry(), insert(), search(), display() 
*/


#include "../../token/tokentype.h"
#include "../hash/symboltable.h"

struct parse_tree {
    t_list* data;
    struct parse_tree* child;
    struct parse_tree* sibling;
};


#define PARSING_ERROR -1
#define SUBTREE_OK 0
#define MEMORY_ERROR 1

typedef struct parse_tree p_tree;


/*
 * Create a new ParseTree from a given token list.

*/
p_tree* create_tree(t_list* c){
    p_tree* tree;
    
    /* Allocate space for tree */
    if(( tree =(p_tree*) malloc( sizeof( p_tree ) ) ) == NULL ) {
		free(tree);
		return NULL;
	}

    return tree;
}


void print_ParseTree(struct ParseTree* tree);

/*
 * Free memory for the ParseTree and all its internal data, including children and siblings.
 * ParseTrees are built by *cloning* Tokens, so only the clones are freed.
*/
void free_ParseTree(p_tree* tree) {
    p_tree* sibling;
    p_tree* child;
    sibling = tree->sibling;
    child = tree->child;
    free(tree);

    if (sibling != NULL)
        free_ParseTree(sibling);
    if (child != NULL)
        free_ParseTree(child);
}


// int build_ParseTree (struct TokenList* head, struct ParseTree** tree);

int build_ParseTree_FromFile (const char *fileName, struct ParseTree **tree);