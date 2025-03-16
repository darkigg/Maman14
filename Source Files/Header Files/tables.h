/* This header includes definition of all table types in the program, and declarations of related functions */

#ifndef TABLES
#define TABLES

#include <stdlib.h>

#include "errorHandling.h"
#include "utilities.h"
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
 * Table type capable of containing all labels encountered, their addresses and all of their assigned attributes.
 */
struct label_table_line{
	unsigned int value;
	char name[MAXLABEL];

	/* all the identifiers a label can have */
	int data : 1;
	int code : 1;
	int external : 1;
	int entry : 1;

	/*note: if all identifiers are False (0), the label is ignored.*/
	
};
typedef struct {
	struct label_table_line * table;
	int length;
} label_table;

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

/**
 * Table type capable of containting all word bit values and their addresses.
 */
struct word_table_line{
	assembly_word word;
	int address : 21; /*the maximal bits in which an address can be stored*/
	int data : 1;
	int code : 1;
};
typedef struct{
	struct word_table_line *table;
	int length;
} word_table;

/**
 * Table type used to encapsulate all arguments across the code which can only be inferred during the 2nd passage.
 * The 2nd passage's only operation is iteration over this table, whilst writing necessary values into the provided words.
 */
struct label_arguments_table_line{
	int line;
	int word_ind; /* will be negative if there is no word to infer, essentially in a .entry instruction */
	char arg[MAXLABEL + 1]; /*an argument in this table contains a label name and a potential & preceeding it; therefore the argument will not be longer than the max length of a label name plus 1 additional character.*/
};
typedef struct{
	struct label_arguments_table_line *table;
	int length;
} label_arguments_table;

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
