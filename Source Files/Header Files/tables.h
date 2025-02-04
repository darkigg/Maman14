/* This header includes definition of all table types in the program, and declarations of related functions */

#ifndef TABLES
#define TABLES

#include "labels.h"
#include "utilities.h"
#include "assemblerErrorHandling.h"
#include "macros.h"

#define EXTEND_TABLE(table) ( (*table) = realloc(table, SIZE_OF_ARR(table) + sizeof(table[0])) )

/**
 * Table type capable of containing all labels encountered, their addresses and all of their assigned attributes.
 */
struct label_table_line{
	char name[MAXLABEL];
	int address;
	labelAttributePool attributes;
};
typedef struct label_table_line * label_table;

/**
 * Table type capable of containing all assembler errors encountered and the line at which they appear.
 */
struct assembler_error_table_line{
	assemblerErrorType error;
	int line_number;
};
typedef struct assembler_error_table_line * assembler_error_table;

/**
 * Table type capable of containing all macros and their contents
 */
struct macro_table_line{
	char *name;
	char *content;
};
typedef struct macro_table_line * macro_table;

/* C HAS NO SUPPORT FOR FUNCTION OVERLOADING - PLEASE FIX THE BELOW */

#endif
