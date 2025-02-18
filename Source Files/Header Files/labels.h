/* This file includes definition of labels and functions for storing and iterperting them*/

#ifndef LABELS
#define LABELS

#include "errorHandling.h"
#include "utilities.h"
#include "tables.h"

#define MAXLABEL 31 /*maximal length of a label*/

/**
 * This function, given the first token of a line seperated by whitespaces, seeks a label within that line.
 * If a label is found, it will be added to the table.
 * @param segment the token from which to attempt extracting the label.
 * @param name the string to write the label name to.
 * @param host the tables host.
 * @return the most recent error encountered by the function.
 */
errorType scan_for_label(const char *segment, tables_host *host, int line_n);

/**
 * Verifies validity of a label name, emitting an error if it is not.
 * @param label the label whose validity is to be verified.
 * @param host the table host.
 * @return NONE if the label is valid, ILLEGAL_LABEL_NAME otherwise.
 */
errorType is_label_def_valid( const char *label, const tables_host host );

/**
 * adds a label to a label table, with a name, address and identifiers.
 * FINISH APIIIIIIIIIIIII
 */
errorType add_label(label_table *labels, char name[MAXLABEL], int address, boolean code, boolean external, boolean data);

#endif