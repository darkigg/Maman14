/*this header contains functions related to the operation of analyzing the .am file*/

#ifndef READ_AM
#define READ_AM

#include <stdio.h>

#include "constants.h"
#include "tables.h"
#include "words.h"
#include "utilities.h"
#include "analyse_op.h"

/**
 * Function responsible for general translation process.
 * @param file the .am file to translate to binary.
 * @param host the host of tables.
 * @param ICF a pointer to the overall instructions counter of the program.
 * @param DCF a pointer to the overall data counter of the program.
 * @return latest error encountered before function termination.
 */
errorType translate_file(FILE *file, tables_host *host, int *ICF, int *DCF);

/**
 * Function responsible for the 1st stage of the assembler.
 * The first stage is responsible for setting up the label table and translating every line that does not use labels to machine code.
 * @param file the .am file to read.
 * @param host the host of tables.
 * @param ICF a pointer to the overall instructions counter of the program.
 * @param DCF a pointer to the overall data counter of the program.
 * @return latest error encountered before function termination.
 */
errorType first_passage(FILE *file, tables_host *host, int *ICF, int *DCF);

/**
 * Function responsible for the 2nd stage of the assembler.
 * The second stage is responsible for translating every line that references labels to machine code.
 * @param host a pointer to the host of tables.
 * @return the most recent error encountered during the function's execution. 
 */
errorType second_passage(tables_host *host);

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
 * This function, given a line with an operation, writes the operation and its arguments into language code words.
 * @param host pointer to the host of tables.
 * @param line the line from which to read.
 * @param IC pointer to the instruction (code) counter.
 * @param linecnt the number of the current line (for error reporting).
 * @param interpret_labels whether or not to write the words of sentences including labels.
 * @return the error encountered most recently during the function's operation.
 */
errorType read_code_line(tables_host *host, char *line, int *IC, const int linecnt, boolean interpret_labels);

/**
 * This function, given a string of operation arguments, will analyse the arguments and update the supplied first word and tables accordingly.
 * The function also reports errors potentially encountered.
 * @param word a pointer to the first word of the sentence for which the argument list is destinied.
 * @param host pointer to the host of tables.
 * @param arg_list the string containing the argument list.
 * @param expected_argument_count the number of arguments the function should expect to find in the argument list.
 * @param IC a pointer to the IC.
 * @param linecnt the line within the file in which the argument list is found.
 * @param interpret_labels whether or not to interpret labels which may be present in the arguments list.
 * @return the most recently encountered error during the function's operation, or NONE if none were.
 */
errorType read_op_args(startword *word, tables_host *host, char *arg_list, int expected_argument_count, int *IC, const int linecnt, boolean interpret_labels);

/**
 * Handles instructions, reports errors, increments the data counter as much as necessary and adding all words to the table of addresses.
 * @param DC the data counter to increment.
 * @param line the line from which to scan the instruction and words.
 * @param host the host of tables.
 * @param linecnt the number of the current line.
 * @return the most recent error encountered, if none were then NONE.
 */
errorType handle_instruction_passage1(int *DC, char *line, tables_host *host, const int linecnt);

/*INSTRUCTION FUNCTIONS*/

/**
 * A function responsible for handling the .data instruction.
 * @param host pointer to the host of tables.
 * @param line the line to read.
 * @param DC pointer to the data counter.
 * @param linecnt the number of the line currently read.
 * @return the most recent error encountered.
 */
errorType data_inst(tables_host *host, char *line, int *DC, const int linecnt);

/**
 * A function responsible for handling the .string instruction.
 * @param host pointer to the host of tables.
 * @param line the line to read.
 * @param DC pointer to the data counter.
 * @param linecnt the number of the line currently read.
 * @return the most recent error encountered.
 */
errorType string_inst(tables_host *host,char *line, int *DC, const int linecnt);

/**
 * A function responsible for handling the .extern instruction.
 * @param host pointer to the host of tables.
 * @param line the line to read.
 * @param linecnt the number of the line currently read.
 * @return the most recent error encountered.
 */
errorType extern_inst(tables_host *host, char *line, const int linecnt);
 
/**
 * A function for 1st assembler phase handling of the .entry instruction.
 * @param host pointer to the host of tables.
 * @param line the line to read.
 * @param linecnt the number of the line currently read.
 * @return the most recent error encountered during the function's operation.
 */
errorType firstphase_entry_inst(tables_host *host, char *line, const int linecnt);

#endif