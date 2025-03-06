
#ifndef FUNCT
#define FUNCT

/*this file includes definitions and declarations which make up an integral part of the operation assembly process.*/

#include <string.h>

#include "errorHandling.h"
#include "tables.h"
#include "utilities.h"
#include "words.h"
#include "read_am.h"

/* addressing methods codes */

enum address_method{
	IMMEDIATE_ADDRESS,
	DIRECT_ADDRESS,
	VARIABLE_ADDRESS,
	DIRECT_REGISTER_ADDRESS
};

/*amount of operations*/
#define FUNCOUNT 16

/*an array of all operation names, ordered by their appearance in the below enum operationType*/
#define FUNCTEXT {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"}

typedef enum{
	MOV = 0,
	CMP = 1,
	ADD = 2,
	SUB = 3,
	LEA = 4,
	CLR = 5,
	NOT = 6,
	INC = 7,
	DEC = 8,
	JMP = 9,
	BNE = 10,
	JSR = 11,
	RED = 12,
	PRN = 13,
	RTS = 14,
	STOP = 15,
	ILLEGAL /* a value meaning an illegal operation */
} operationType;

#define FUNCT_VALS {0, 0, 1, 2, 0, 1, 2, 3, 4, 1, 2, 3, 0, 0, 0, 0} /*an array of all funct values for the operations*/

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
 * This function, given a potentially viable operation, detects the function (if it is valid).
 * @param op_text text containing the operation; for proper functionality, mustn't include extraneous text.
 * @return the operation detected, by number (according to the values in operationType).
 */
operationType detect_op(char *op_text);

/**
 * @param type the operation type
 * @return the amount of arguments the operation matching the type provided expects.
 */
int op_arg_count(operationType type);

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
 * This function, given an operation's opcode and the address method of which an attempted usage is made, will check whether or not the operation can accept that address method.
 * @param opcode the operation's opcode.
 * @param address_method the attempted addressing method.
 * @return whether or not the address method is acceptable for the operation.
 */
boolean is_address_method_valid(int opcode, int address_method);

/**
 * Given an operation type, the function returns the corresponding opcode matching the operation type.
 * @param op the operation type.
 * @return the opcode.
 */
int get_opcode(operationType op);

/**
 * A function for adding arguments dependant on labels to a label_arguments_table.
 * @param lab_args a pointer to the table of label arguments, to which a word will be added.
 * @param line the line at which the argument appears within the code.
 * @param ind the index of the word to which the 2nd passage should write (if there is no such, enter a negative value).
 * @param arg a string containing the argument itself to be scanned.
 * @return the most recently encountered error during the function's execution.
 */
errorType add_label_argument(label_arguments_table *lab_args, int line, int ind, char *arg);

#endif