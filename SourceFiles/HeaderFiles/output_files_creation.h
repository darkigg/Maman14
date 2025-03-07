/*This header contains prototypes for functions creating the output files*/

#ifndef OUTPUT_FILES_CREATION
#define OUTPUT_FILES_CREATION

#include <stdio.h>

#include "tables.h"

/**
 * Creates a .obj file and writes it in the require required format.
 * @param words the table of words in the program.
 * @param ICF the ICF value of the current file.
 * @param DCF the DCF value of the current file.
 * @param file_name the name of the file for which the .obj file is created. Mustn't include any suffix.
 */
void create_obj_file(const word_table words, int ICF, int DCF, char *file_name);

#endif