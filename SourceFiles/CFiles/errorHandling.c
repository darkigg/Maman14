#include "../HeaderFiles/errorHandling.h"

/*this file includes functions for handling errors*/

errorType add_error(error_table *error_table, errorType new_error, int line){
	EXTEND_TABLE((*error_table), struct error_table_line);

	(*error_table).table[SIZE_OF_ARR(error_table) - 1].error = new_error;
	(*error_table).table[SIZE_OF_ARR(error_table) - 1].line_number = line;

	return new_error; /* if no error was encountered, the function shall return the error it was requested to (and successfully) added */
}

boolean is_comma_missing(char* token){
	boolean finished_reading_arg = False; /*did the function already encounter (within the token) a white space character preceeded by a non-white one?*/

	for(token++ /*no need to read the first char as the one before it was undefined*/; *token != '\0'; token++){
		if(IS_WHITESPACE((*token)) && !IS_WHITESPACE( (*(token - 1)) )) finished_reading_arg = True; /* if token is a white character and the previous character is not white, it is the end of an argument*/
		else if(!IS_WHITESPACE((*token)) && finished_reading_arg) return True; /*there is a non-white character despite the end of the argument having already been encountered*/
	}

	return False; /*no case of missing comma was encountered.*/
}

void end_prog(tables_host *tables){
	free_tables_host(tables);

	/*print out an error*/
	fprintf(stderr, "Not enough memory could be allocated for the program to properly compile");
	
	exit(1); /* 1 is used because the program terminated before conclusion of it's function */
}

int print_err(error_table *error_table, char *filename){
	struct error_table_line *current_err; /*points to the line with the data of the currently iterated over error*/
	int i;

	char *error_messages[] = ERROR_TEXTS; /*an array of the texts of all errors in the program, sorted so that each error enum is matched to the appropriate text*/

	/*a loop iterating over all errors, printing them to the standard error*/
	for(current_err = error_table->table, i = 0; i<error_table->length; current_err++, i++){
		fprintf(stderr, "In File %s, line %d: %s.\n", filename, current_err->line_number, error_messages[current_err->error]);
	}

	return i; /*returns i, 0 if no errors were encountered throughout the assembly process*/
}