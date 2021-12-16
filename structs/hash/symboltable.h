/* 
* File        : symboltable.h
* Description : This file contains functions related to organised a symbol table. 
*               The functions implemented are:
*               create_table(), create_entry(), insert(), search(), display() 
*/


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

/* struct to hold each entry */
struct token_list
{
	char* lexeme; 
	int token_type;
	char* token_name;
	int line;
	struct token_list* successor;
};

typedef struct token_list t_list;

/* Create a new symbol table. */
t_list* create_table()
{
	t_list* table_ptr = NULL; // declare a pointer
	
	return table_ptr;
}

/* Create an entry for a lexeme, token pair. This will be called from the insert function */
t_list *create_entry( char *lexeme, int token_type, char*token_name, int line)
{
	t_list *newentry;

	/* Allocate space for newentry */
	if( ( newentry =(t_list*) malloc( sizeof( t_list ) ) ) == NULL ) {
		free(newentry);
		return NULL;
	}
	
	/* Copy lexeme to newentry location using strdup (string-duplicate). Return NULL if it fails */
	if( ( newentry->lexeme = strdup( lexeme ) ) == NULL ) {
		return NULL;
	}
	
	newentry->token_type = token_type;
	newentry->token_name = token_name;
	newentry->line = line;
	newentry->successor = NULL;

	return newentry;
}

/* Search for an entry given a lexeme. Return a pointer to the entry of the lexeme exists, else return NULL */
t_list* search( t_list* hash_table_ptr, char* lexeme )
{
	t_list* myentry;
	
	while( myentry != NULL && strcmp( lexeme, myentry->lexeme ) != 0 )
	{
		myentry = myentry->successor;
	}

	if(myentry == NULL) // lexeme is not found
		return NULL;
	
	else // lexeme found
		return myentry;
}

// Traverse the hash table and print all the entries in file
void display(t_list* table_ptr)
{
	t_list* traverser;
	FILE *writeParsed=fopen("parsedTable.txt","w");
    
	fprintf(writeParsed,"\t\tlexeme\t\ttoken\t\ttype\n");

	traverser = table_ptr;

	while( traverser != NULL)
	{
		fprintf(writeParsed,"%15s\t\t%3d\t\t%10s\n", traverser->lexeme, traverser->token_type, traverser->token_name);
		traverser = traverser->successor;
	}
   
}

/* Insert an entry into a hash table. */
void insert( t_list** table_ptr, char* lexeme, char*token_name, int token_type, int line)
{
	t_list* newentry = NULL;

	newentry = create_entry(lexeme, token_type, token_name, line); // Create an entry using the <lexeme, token> pair

	if(newentry == NULL) // In case there was some error while executing create_entry()
	{
		free(newentry);
		printf("Insert failed. New entry could not be created.");
		exit(1);
	}

	if (*table_ptr == NULL){
		*table_ptr = newentry;
		return;
	}
	
	t_list* temp = *table_ptr;
	while (temp->successor != NULL)
		temp = temp->successor;
	temp->successor = newentry;
	
}


