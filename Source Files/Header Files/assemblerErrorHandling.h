/* file for all types and functions used specifically for error handling */

#ifndef AEH
#define AEH

#include "utilities.h"
#include "tables.h"

typedef enum{

	NONE,
	ILLEGAL_LABEL_NAME,
	UNABLE_TO_ALLOCATE_MEMORY

} assemblerErrorType;

/**
 * Verifies validity of a label name, emitting an error if it is not.
 * @param label the label whose validity is to be verified.
 * @return NONE if the label is valid, ILLEGAL_LABEL_NAME otherwise.
 */
assemblerErrorType is_label_def_valid( const char *label );

boolean add_error(assembler_error_table *error_table, assemblerErrorType new_error); 

#endif