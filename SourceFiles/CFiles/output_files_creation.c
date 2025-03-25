#include "../HeaderFiles/output_files_creation.h"

void create_obj_file(const word_table words, int ICF, int DCF, char *file_name){
	
	/*the .obj file*/
	FILE *obj_file;

	struct word_table_line *current_word; /* an iterator over all the words in the words table provided */
	int i;

	char obj_name[MAXFILE]; /*a string for storing the full name of the file referrenced in file_name*/

	strcpy(obj_name, file_name);
	strcat(obj_name, ".obj");
	
	obj_file = fopen(obj_name, "w");
	if(obj_file == NULL){
		fprintf(stderr, "File %s could not be opened and so a .obj file could not be generated\n", obj_name);
		return;
	}

	fprintf(obj_file, "%7d %d\n", ICF, DCF); /*print the first line of the .obj file, which the ICF and the DCF*/
	
	/* a loop iterating over all words in the table, printing them to the .obj file line after line */
	for(current_word = words.table, i = 0; i<words.length; current_word++, i++)
		fprintf(obj_file, "%.7d %.6x\n", current_word->address, (current_word->word).value);

	fclose(obj_file);
}

void create_ent_files(const label_table labels, char *file_name){
	/*the pointer to the .ent file*/
	FILE *ent_file;

	struct label_table_line *current_lab; /*an iterator*/

	/*string for storing the full name of the .ent file.*/
	char ent_name[MAXFILE];

	/*concatenates the file suffix to the file name*/
	strcpy(ent_name, file_name);
	strcat(ent_name, ".ent");

	/*open the file*/
	ent_file = fopen(ent_name, "w");
	if(ent_file == NULL)
		fprintf(stderr, "File %s could not be opened and so the .ent and .ext files could not be generated\n", ent_name);

	else
		/*a loop iterating over all labels, printing the entry ones to the file*/
		for(current_lab = labels.table; current_lab < labels.table + labels.length; current_lab++)
			if(current_lab->entry)
				fprintf(ent_file, "%s %.7d\n", current_lab->name, current_lab->value);

	fclose(ent_file);
}

void create_ext_files(const label_arguments_table arguments, char *file_name){
	/*the pointer to the .ent file*/
	FILE *ext_file;

	struct label_arguments_table_line *current_lab; /*an iterator*/

	/*string for storing the full name of the .ent file.*/
	char ext_name[MAXFILE];

	/*concatenates the file suffix to the file name*/
	strcpy(ext_name, file_name);
	strcat(ext_name, ".ext");

	/*open the file*/
	ext_file = fopen(ext_name, "w");
	if(ext_file == NULL)
		fprintf(stderr, "File %s could not be opened and so the .ent and .ext files could not be generated\n", ext_name);
	
	else
		for(current_lab = arguments.table; current_lab < arguments.table + arguments.length; current_lab++)
			if(current_lab->external)
				fprintf(ext_file, "%s %.7d\n", current_lab->arg, current_lab->address);

	fclose(ext_file);
}