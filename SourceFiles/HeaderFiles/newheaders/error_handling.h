/*This file contains prototypes for functions handling erros*/

#ifndef ERROR_HANDLING
#define ERROR_HANDLING

#include <stdlib.h>

#include "constants.h"
#include "tables.h"

/**
 * Adds an error to a given error table.
 * @param error_table pointer to the error table to which an error will be added.
 * @param new_error the type of the error to add.
 * @param line the line at which the new error was encountered.
 * @return an error encountered during the table expansion process; if none were, it will return the error that was added.
 */
errorType add_error(error_table *error_table, errorType new_error, int line); 

/**
 * Verifies validity of a label name, emitting an error if it is not.
 * @param label the label whose validity is to be verified.
 * @param host the table host.
 * @return NONE if the label is valid, a corresponding error type otherwise.
 */
errorType is_label_def_valid( const char *label, const tables_host host );

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