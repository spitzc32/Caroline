#ifndef _STACK_H
#include <stdio.h>

struct stack {
	struct stack_node* top;
};

struct stack_node {
	void* value;
	struct stack_node* next;
};

/* Initialise stack */
extern struct stack* st_init();

/* Top element of the stack */
extern void* st_top(struct stack* stack);

/* Check if stack is empty */
extern int st_empty(struct stack* stack);

/* Dispose the stack */
//extern int stack_dispose(struct stack* stack);

/* Push node to stack */
extern void st_push(struct stack* stack, void* value);

/* Pop node from stack */
extern void* st_pop(struct stack* stack);

/* Print elements in stack */
extern void st_print(struct stack* stack, FILE* fp);

#endif