#include "../Header Files/errorHandling.h"

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