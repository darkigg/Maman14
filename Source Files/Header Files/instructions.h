#ifndef INSTRUCTIONS
#define INSTRUCTIONS

#include <string.h>

#include "errorHandling.h"
#include "tables.h"
#include "read_am.h"
#include "words.h"

/**
 * A function responsible for handling the .data instruction.
 * @param host the host of tables.
 * @param line the line to read.
 * @return the most recent error encountered.
 */
errorType data_inst(tables_host *host, char *line, int *DC, const int linecnt);

/**
 * A function responsible for handling the .string instruction.
 * @param host the host of tables.
 * @param line the line to read.
 * @return the most recent error encountered.
 */
errorType string_inst(tables_host *host, char *line, int *DC, const int linecnt);

#endif