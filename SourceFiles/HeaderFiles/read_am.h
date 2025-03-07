/* This file contains declarations of fundamental functions, used for reading the .am files in the assembler process. The functions here only read; they don not interpert nor do they handle error detection themselves.
The functions here potentially could, though, call functions from other headers to perform those actions.*/

#ifndef READ_AM
#define READ_AM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* stores the type of program sentence */
typedef enum{
	INSTRUCTION /*data*/,
	OPERATION /*code*/,
	COMMENT,
	EMPTY
} sentenceType;

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

/*includes should be after all the type declarations, to avoid situations of necessary declarations not being made prior to the files inclusion*/
#include "tables.h"
#include "errorHandling.h"
#include "labels.h"
#include "utilities.h"
#include "instructions.h"
#include "compileFunc.h"
 
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
 * @param host a pointer to the host of tables.
 * @return the most recent error encountered during the function's execution. 
 */
errorType second_passage(tables_host *host);

/**
 * Handles instructions, reports errors, increments the data counter as much as necessary and adding all words to the table of addresses.
 * @param DC the data counter to increment.
 * @param line the line from which to scan the instruction and words.
 * @param host the host of tables.
 * @param linecnt the number of the current line.
 * @return the most recent error encountered, if none were then NONE.
 */
errorType handle_instruction_passage1(int *DC, char *line, tables_host *host, const int linecnt);

#endif