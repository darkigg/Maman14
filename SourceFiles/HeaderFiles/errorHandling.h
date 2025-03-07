/* file for all types and functions used specifically for error handling */

#ifndef AEH
#define AEH

typedef enum{

	NONE,
	ILLEGAL_MACRO_DEFINITION,
	LINE_TOO_LONG,
	ILLEGAL_LABEL_NAME,
	MULTIPLE_DEF_NOT_ALLOWED, /*error for attempting to define multiple labels with the same name*/
	ILLEGAL_LABEL_DEFINITION,
	LABEL_ALREADY_EXTERNAL, /*...and an attempt is made to set it as an entry*/
	ILLEGAL_FUNCTION_NAME,
	ILLEGAL_INSTRUCTION_NAME,
	MULTIPLE_CONSECUTIVE_COMMAS,
	ILLEGAL_COMMA,
	MISSING_COMMA,
	NOT_ENOUGH_ARGUMENTS,
	EXTRANEOUS_TEXT,
	ILLEGAL_ARGUMENT,
	UNIDENTIFIED_LABEL, /*a value which is supposed to be a label does not refer to a real label*/
	CANNOT_GET_EXTERN_LABEL_ADDRESS,
	VALUE_TOO_BIG,
	NO_AVAILABLE_ADDRESS,

	UNABLE_TO_ALLOCATE_MEMORY, /*used when a dynamic allocation fails.*/
	
	/*demo errors, included in this type as they create unusual circumstances and require special handling*/
	NO_LABEL, 
	USELESS_LABEL
} errorType;

/**
 * Table type capable of containing all assembler errors encountered and the line at which they appear.
 */
struct error_table_line{
	errorType error;
	int line_number;
};
typedef struct{
	struct error_table_line *table;
	int length;
} error_table;

/*includes should be after all the type declarations, to avoid situations of necessary declarations not being made prior to the files inclusion*/
#include "utilities.h"
#include "tables.h"


/* an 'operation' is a general term for both instructions and functions */
#define ERROR_TEXTS /*an array containing all the texts to be printed on screen upon error discovery, with the texts in the same order as that of their error's appearance in the above enum*/\
	{ "Macro definition is illegal", /*ILLEGAL_MACRO_DEFINITION*/\
	"The line is longer (contains more characters) than the maximal legal line length (maximal amount of characters)", /*LINE_TOO_LONG*/\
	"The name of the declared label is illegal",/*ILLEGAL_LABEL_NAME*/\
	"Repeated declarations of a label by the same name are illegal",/*MULTIPLE_DEF_NOT_ALLOWED*/\
	"The definition of the label is illegal (e.g. it might be empty)",/*ILLEGAL_LABEL_DEFINITION*/\
	"An external label cannot be accepted as an entry",/*LABEL_ALREADY_EXTERNAL*/\
	"The function called does not exist",/*ILLEGAL_FUNCTION_NAME*/\
	"The instruction (a suspected operation with a dot prefix) called does not exist",/*ILLEGAL_INSTRUCTION_NAME*/\
	"Only a single comma can be used to split arguments apart, multiple are not allowed",/*MULTIPLE_CONSECUTIVE_COMMAS*/\
	"A comma cannot preceed all arguments in an arguments list",/*ILLEGAL_COMMA*/\
	"A comma is expected between separate arguments",/*MISSING_COMMA*/\
	"The operation called expects more arguments than it is provided with",/*NOT_ENOUGH_ARGUMENTS*/\
	"There is extraneous text after the conclusion of the operation call", /*EXTRANEOUS_TEXT*/\
	"An argument provided to the operation is either illegal or cannot be accepted by it",/*ILLEGAL_ARGUMENT*/\
	"A suspected label argument cannot be identified as any declared label",/*UNIDENTIFIED_LABEL*/\
	"The operator & cannot be used on external labels",/*CANNOT_GET_EXTERN_LABEL_ADDRESS*/\
	"The value supplied to the operation cannot be stored within the computer's memory for it is too big",/*VALUE_TOO_BIG*/\
	"There are not enough addresses in the machine to account for the program past this point"/*NO_AVAILABLE_ADDRESS*/}
 
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

/**
 * Ends the program and frees all memory allocations.
 * Note: only tables are dynamically allocated, and so the tables host should contain all dynamically allocated memory blocks.
 * @param tables a pointer to the host of tables to free from memory.
 */
void end_prog(tables_host *tables);

/**
 * Prints all the errors found in an error_table to stderr.
 * @param error_table a pointer to the table of all errors.
 * @param filename the name of the file within which all the errors were encountered.
 * @return the amount of errors printed.
 */
int print_err(error_table *error_table, char *filename);

#endif