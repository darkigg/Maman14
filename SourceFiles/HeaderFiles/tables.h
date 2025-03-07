/* This header contains the tables_host type and operations for handling labels in general */

#ifndef TABLES
#define TABLES

#include <stdlib.h>

#include "utilities.h"
#include "errorHandling.h"
#include "macros.h"
#include "labels.h"
#include "words.h"

#define EXTEND_TABLE(tab, type) /*expects 'tab' to be one of the table types, and to be called only when errorType is the return type. type is the type of a single table line. */ \
	(tab).table = (type *) realloc( (tab).table, (tab).length + sizeof((tab).table[0]) );\
	if((tab).table == NULL) return UNABLE_TO_ALLOCATE_MEMORY;\
	(tab).length++

/** 
 * Table type capable of containing all macros and their contents
 */
struct macro_table_line{
	char *name;
	char *content;
};
typedef struct {
	struct macro_table_line *table;
	int length;
} macro_table;

/**
 * A struct containing all tables used throughout the program, nicknamed a host.
 * Useful for access to tables through functions requiring multiple tables, and for easy allocation and deallocation of all dynamically allocated memory components in the program.
 */
typedef struct tables{

	macro_table macros; /* table of macros */
	label_table labels; /* table of labels */
	word_table words; /* table of all words from the current file */
	word_table data_words; /* table of data words, storing them prior to their integration into the main words table */
	error_table errors; /* table of all errors encountered throughout the assembling of a file */
	label_arguments_table lab_args; /* table of all arguments suspected to be labels */

} tables_host;

/**
 * Initiates all tables in the host.
 * @param host the host.
 */
void initiate_tables_host(tables_host *host);

/**
 * Frees all tables in the host.
 * @param host the host.
 */
void free_tables_host(tables_host *host);

#endif
