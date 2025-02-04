#include <stdlib.h>
#include <string.h>

#include "../Header Files/labels.h"

void addAttribute(labelAttributePool *pool, labelAttribute new_attribute){
	
	int amount_of_attributes;

	amount_of_attributes = SIZE_OF_ARR((*pool).attributes);

	(*pool).attributes = realloc((*pool).attributes, amount_of_attributes += 1);
	(*pool).attributes[amount_of_attributes - 1] = new_attribute;

}

boolean scan_for_label(char *line, label_table *table, assembler_error_table *errors){

	char *name, *word; /* pointers to the discovered label name and to the word of the sentence from which it was taken*/
	labelAttribute new_att; /* the attribute to add to the scanned label (if there was) in the label table */
	assemblerErrorType error_temp; /* stores an error type as it is encountered, before adding it to a table*/
	boolean was_label_scanned = False; /* was a label even scanned to begin with? */

	while(strcmp((word = strtok(line, ' ')), "") == 0);

	if(strcmp(word, ".extern") == 0){
		name = strtok(NULL, ' ');
		new_att = external;
		was_label_scanned = True;
	}
	else if(word[SIZE_OF_ARR(word) - 1] == ':'){
		strncat(name, word, SIZE_OF_ARR(word) - 1);
		new_att = code;	
		was_label_scanned = True;
	}

	/* only add arguments to the tables if a label declaration/definition was found */
	if(was_label_scanned){
		/* scan for error in the label name */
		error_temp = is_label_def_valid(name);
		if(extend_table(errors) && (error_temp != NONE))
			errors[SIZE_OF_ARR(errors) - 1] = error_temp;

		/* if the label is legal, extend the label table */
		if( error_temp == NONE ){
			extend_table(table);

			/* if the label is external, set the address to 0 (non-0 addresses will not be set under this scope, for they do not depend on the label attributes assigned here)*/
			if(new_att == external) table[SIZE_OF_ARR(table)-1]->address = 0;

			/* add label to the table */
			table[SIZE_OF_ARR(table)-1]->name = name;
			addAttribute(&table[SIZE_OF_ARR(table)-1]->attributes, new_att);
		}

		
	}
}