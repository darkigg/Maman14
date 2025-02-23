
#ifndef FUNCT
#define FUNCT

/*this file includes definitions and declarations which make up an integral part of the operation assembly process.*/

#include <string.h>

#include "errorHandling.h"
#include "tables.h"
#include "utilities.h"

typedef enum{
	MOV,
	CMP,
	ADD,
	SUB,
	LEA,
	CLR,
	NOT,
	INC,
	DEC,
	JMP,
	BNE,
	JSR,
	RED,
	PRN,
	RTS,
	STOP
} operationType;

#define FUNCT_VALS {0, 0, 1, 2, 0, 1, 2, 3, 4, 1, 2, 3, 0, 0, 0, 0} /*an array of all funct values for the operations*/

/*since the enum operationType is sorted according to the opcode ascending order, the op code can be calculated for each operation using the enum's value and the funct value*/

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

#endif