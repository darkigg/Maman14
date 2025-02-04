/* This file contains declarations of fundamental functions, used for reading the .am files in the assembler process. The functions here only read; they don not interpert nor do they handle error detection themselves.
The functions here potentially could, though, call functions from other headers to perform those actions.*/

#ifndef READ_AM
#define READ_AM

#include <stdio.h>

#include "assemblerErrorHandling.h"
#include "tables.h"

/**
 * Function responsible for general translation process.
 * @param file the .am file to translate to binary.
 * @param errors the table of errors encountered during the assembly phase.
 */
void translate_file(FILE *file, assembler_error_table *errors);

void translate_line(FILE *file);

#endif