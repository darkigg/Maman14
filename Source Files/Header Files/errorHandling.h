/* file for all types and functions used specifically for error handling */

#ifndef AEH
#define AEH

#include "utilities.h"
#include "tables.h"

typedef enum{

	NONE,
	ILLEGAL_LABEL_NAME,
	NO_LABEL, /*not a real error*/
	ILLEGAL_FUNCTION_NAME,
	ILLEGAL_INSTRUCTION_NAME,
	MULTIPLE_CONSECUTIVE_COMMAS,
	ILLEGAL_COMMA,
	MISSING_COMMA,
	NOT_ENOUGH_ARGUMENTS,
	TOO_MANY_ARGUMENTS,
	UNABLE_TO_ALLOCATE_MEMORY /* the most significant error; an encounter with it will lead to all other errors to be neglected as it is impossible to accurately point out all errors of the program if dynamic allocation is impossible. */

} errorType;

/**
 * Adds an error to a given error table.
 * @param error_table pointer to the error table to which an error will be added.
 * @param new_error the type of the error to add.
 * @param line the line at which the new error was encountered.
 * @return an error encountered during the table expansion process, if any. The only error which could be practically returned is UNABLE_TO_ALLOCATE_MEMORY, if it is not encountered the return value will be none.
 */
errorType add_error(error_table *error_table, errorType new_error, int line); 

/**
 * Given a token between 2 commas, this function checks whether or not the token contains more arguments than legal.
 * @param token ther token.
 * @return whether or not there is more than a single argument in the token (e.g. a non white character spotted after the end of the argument).
 */
boolean is_comma_missing(char* token);

#endif