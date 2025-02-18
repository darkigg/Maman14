/* This file contains declarations of fundamental functions, used for reading the .am files in the assembler process. The functions here only read; they don not interpert nor do they handle error detection themselves.
The functions here potentially could, though, call functions from other headers to perform those actions.*/

#ifndef READ_AM
#define READ_AM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tables.h"
#include "errorHandling.h"
#include "labels.h"
#include "utilities.h"

/* stores the type of instruction, as each different instruction requires widely different implementation */

/* stores the type of program sentence */
typedef enum{
	INSTRUCTION /*data*/,
	OPERATION /*code*/,
	COMMENT,
	EMPTY
} sentenceType;

/**
 * Function responsible for general translation process.
 * @param file the .am file to translate to binary.
 * @param host the host of tables.
 * @return latest error encountered before function termination.
 */
errorType translate_file(FILE *file, tables_host *host);

/**
 * Function responsible for the 1st stage of the assembler.
 * The first stage is responsible for setting up the label table and translating every line that does not use labels to machine code.
 * @param file the .am file to read.
 * @param host the host of tables.
 * @return latest error encountered before function termination.
 */
errorType first_passage(FILE *file, tables_host *host);

/**
 * Function responsible for processing each line read during the first stage of the assembly.
 * @param line the line to read.
 * @param host the host of tables.
 * @param IC the instructions counter.
 * @param DC the data counter.
 * @return latest error encountered before function termination.
 */
errorType first_passage_line(char *line, tables_host *host, int *IC, int *DC, const int line_num);

/**
 * Function responsible for the 2nd stage of the assembler.
 * The second stage is responsible for translating every line that references labels to machine code.
 * 
 */
errorType second_passage();

/**
 * Handles instructions, reports errors, increments the data counter as much as necessary and adding all words to the table of addresses.
 * @param DC the data counter to increment.
 * @param line the line from which to scan the instruction and words.
 * @param host the host of tables.
 * @param linecnt the number of the current line.
 * @return the most recent error encountered, if none were then NONE.
 */
errorType handle_instruction_passage1(int *DC, char *line, tables_host *host, const int linecnt);

/**
 * This function gets the start of the argument list for a certain line.
 * @param line the line to seek the argument list in.
 * @return a pointer to the beginning of the argument list (without preceeding spaces), or NULL if there is no.
 */
char *get_arg_list(char *line);

#endif