/*This header contains prototypes for functions creating the output files*/

#ifndef OUTPUT_FILES_CREATION
#define OUTPUT_FILES_CREATION

#include <stdio.h>
#include <string.h>

#include "tables.h"

/**
 * Creates a .obj file and writes it in the require required format.
 * @param words the table of words in the program.
 * @param ICF the ICF value of the current file.
 * @param DCF the DCF value of the current file.
 * @param file_name the name of the file for which the .obj file is created. Mustn't include any suffix.
 */
void create_obj_file(const word_table words, int ICF, int DCF, char *file_name);

/**
 * Creates the .ent file and writes to it in the required format.
 * @param labels the table of labels in the program.
 * @param file_name the name of the file for which to create the .ent file.
 */
void create_ent_files(const label_table labels, char *file_name);

/**
 * Creates the .ext file and fills it with content in the required format.
 * @param arguments the table of all suspected label arguments in the program.
 * @param file_name the name of the file for which to create the .ext file.
 */
void create_ext_files(const label_arguments_table arguments, char *file_name);

#endif