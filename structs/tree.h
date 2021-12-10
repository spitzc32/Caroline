#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stdlib.h>

#define RULE_MAX_SYMBOLS 20
#define MAX_LEN 80

union value{
	char ch;
	int inum;
	unsigned int boolean;
	float fnum;
	char string[MAX_LEN];
};
 
struct tree_node {
   int symbol;
   union value value;
   int children_count;
   struct tree_node* parent;
   struct tree_node* children[RULE_MAX_SYMBOLS];
};

extern struct tree_node* tr_init(struct tree_node* parent, int symbol, union value value);
extern struct tree_node* tr_traverse(struct tree_node* root);
extern void tr_print(struct tree_node* root, FILE* fp, int flag);
extern void tr_write(struct tree_node* root, char* filename);


#endif