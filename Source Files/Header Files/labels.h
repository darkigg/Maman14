/* This file includes definition of labels and functions for storing and iterperting them*/

#ifndef LABELS
#define LABELS

#include "errorHandling.h"
#include "utilities.h"
#include "tables.h"

#define MAXLABEL 31 /*maximal length of a label*/

/**
 * This function, given the first token of a line seperated by whitespaces, seeks a label within that line.
 * @param segment the token from which to attempt extracting the label.
 * @param name the string to write the label name to.
 * @param host pointer to the tables host.
 * @param name pointer to a string to which the spotted (if was) label's name shall be written.
 * @return the most recent error encountered by the function.
 */
errorType scan_for_label(const char *segment, tables_host *host, int line_n, char *name);

/**
 * Verifies validity of a label name, emitting an error if it is not.
 * @param label the label whose validity is to be verified.
 * @param host the table host.
 * @return NONE if the label is valid, a corresponding error type otherwise.
 */
errorType is_label_def_valid( const char *label, const tables_host host );

/**
 * adds a label to a label table, with a name, address and identifiers.
 * @param labels a pointer to the table of labels.
 * @param name the name of the label to add.
 * @param address the address of the label, e.g. the value it shall possess.
 * @param code whether or not to apply the code identifier to the label added.
 * @param external whether or not to apply the external identifier to the label added.
 * @param data whether or not to apply the data identifier to the label added.
 * @return the error most recently encountered by the function. Either none or UNABLE_TO_ALLOCATE_MEMORY.
 */
errorType add_label(label_table *labels, char name[MAXLABEL], int address, boolean code, boolean external, boolean data);

/**
 * finds a given label within a given table of labels, according to its name.
 * @param labels a pointer to the table of labels.
 * @param label_name the name of the label to look up.
 * @return a pointer to the line of the table at which the label and all of its data is stored.
 */
struct label_table_line* get_label(label_table *labels, char *label_name);

#endif