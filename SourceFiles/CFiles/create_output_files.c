#include "../HeaderFiles/create_output_files.h"

void create_obj_file(const word_table words, int ICF, int DCF, char *file_name){
	
	/*the .obj file*/
	FILE *obj_file;

	struct word_table_line *current_word; /* an iterator over all the words in the words table provided */
	int i;

	obj_file = fopen(file_name, "w");

	fprintf(obj_file, "%7d %d\n", ICF, DCF); /*print the first line of the .obj file, which the ICF and the DCF*/

	/* a loop iterating over all words in the table, printing them to the .obj file line after line */
	for(current_word = words.table, i = 0; i<words.length; current_word++, i++)
		fprintf(obj_file, "%.7d %.7x\n", current_word->address, (current_word->word).value);

}