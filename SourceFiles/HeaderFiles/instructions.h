#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include <string.h>

#include "errorHandling.h"
#include "tables.h"
#include "read_am.h"
#include "words.h"

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