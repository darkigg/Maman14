/* This header includes definition of all table types in the program, and declarations of related functions */

#ifndef TABLES
#define TABLES

#include "errorHandling.h"
#include "utilities.h"
#include "macros.h"
#include "labels.h"

#define EXTEND_TABLE(tab) /*expects 'tab' to be one of the table types, and to be called only when errorType is the return type.*/ \
	void *result;\
	result = realloc( (tab).table, (tab).length + sizeof((tab).table[0]) );\
	if(result == NULL) return UNABLE_TO_ALLOCATE_MEMORY;\
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
	boolean data;
	boolean code;
	boolean external;
	boolean entry;
	
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
	int length
} error_table;

/**
 * Table type capable of containting all word bit values and their addresses.
 */
struct word_table_line{
	int value : 24;
	int address : 21;
};
typedef struct{
	struct word_table_line *table;
	int length;
} word_table;

/**
 * A struct containing all tables used while assembling a file, nicknamed a host.
 */
typedef struct tables{
	macro_table macros;
	label_table labels;
	word_table words;
	error_table errors;
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
