/* file for all types and functions used specifically for error handling */

#ifndef AEH
#define AEH

#include "utilities.h"
#include "tables.h"

typedef enum{

	NONE,
	ILLEGAL_LABEL_NAME,
	MULTIPLE_DEF_NOT_ALLOWED, /*error for attempting to define multiple labels with the same name*/
	ILLEGAL_LABEL_DEFINITION,
	
	ILLEGAL_FUNCTION_NAME,
	ILLEGAL_INSTRUCTION_NAME,
	MULTIPLE_CONSECUTIVE_COMMAS,
	ILLEGAL_COMMA,
	MISSING_COMMA,
	NOT_ENOUGH_ARGUMENTS,
	EXTRANEOUS_TEXT,
	ILLEGAL_ARGUMENT,

	/* the most significant error; an encounter with it will lead to all other errors to be neglected as it is impossible to accurately point out all errors of the program if dynamic allocation is impossible. 
	It is also used when the imaginary machine runs out of addresses, as it is an equivalent situation */
	UNABLE_TO_ALLOCATE_MEMORY, 
	
	/*demo errors, included in this type as they create unusual circumstances and require special handling*/
	NO_LABEL, 
	USELESS_LABEL
} errorType;

/**
 * Adds an error to a given error table.
 * @param error_table pointer to the error table to which an error will be added.
 * @param new_error the type of the error to add.
 * @param line the line at which the new error was encountered.
 * @return an error encountered during the table expansion process; if none were, it will return the error that was added.
 */
errorType add_error(error_table *error_table, errorType new_error, int line); 

/**
 * Given a token between 2 commas, this function checks whether or not the token contains more arguments than legal.
 * @param token ther token.
 * @return whether or not there is more than a single argument in the token (e.g. a non white character spotted after the end of the argument).
 */
boolean is_comma_missing(char* token);

#endif