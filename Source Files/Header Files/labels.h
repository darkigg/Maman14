/* This file includes definition of labels and functions for storing and iterperting them*/

#ifndef LABELS
#define LABELS

#include "utilities.h"
#include "tables.h"
#include "assemblerErrorHandling.h"

#define MAXLABEL 31 /*maximal length of a label*/

typedef enum attributes_of_labels{

	data,
	external,
	code

} labelAttribute; /* an enum containing all label attributes*/

typedef struct {

	labelAttribute *attributes;

} labelAttributePool; /* a type containing a pool for label attributes, which will be instanced once for each label*/

/**
 * This function adds a given label attribute to a given pool of label attributes.
 * @param pool the labelAttributePool to which the function is to add a label.
 * @param attribute the attribute to add to the pointed pool.
 */
void addAttribute(labelAttributePool *pool, labelAttribute attribute);

/**
 * This function, given a line, identifies a label definition within that line of any sort (if there is any).
 * The function accounts for both normal label definitions and definition via inclusion from external files.
 * The function then consequently adds the label to the provided labels table if it is, although it does not assign it an address.
 * @param line the line from which to scan a label.
 * @param table the table to which the label will be added.
 * @param errors an array containing all encountered errors, in order to add to it any errors which may be encountered.
 * @return True if a label was found, False otherwise.
 */
boolean scan_for_label(char *line, label_table *table, assembler_error_table *errors);

#endif