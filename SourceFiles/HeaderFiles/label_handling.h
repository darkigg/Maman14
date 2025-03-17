/*This file contains prototypes for functions related to label handling*/

#ifndef LABEL_HANDLING
#define LABEL_HANDLING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "tables.h"
#include "utilities.h"
#include "error_handling.h"

/**
 * A function for adding arguments dependant on labels to a label_arguments_table.
 * @param lab_args a pointer to the table of label arguments, to which a word will be added.
 * @param line the line at which the argument appears within the code.
 * @param ind the index of the word to which the 2nd passage should write (if there is no such, enter a negative value).
 * @param arg a string containing the argument itself to be scanned.
 * @return the most recently encountered error during the function's execution.
 */
errorType add_label_argument(label_arguments_table *lab_args, int line, int ind, char *arg);

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