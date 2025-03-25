#include "../HeaderFiles/label_handling.h"

errorType scan_for_label(char *segment, tables_host *host, int line_n, char *name){

	errorType error_temp = NONE; /*temporary storage for potentially encountered errors*/
	char *char_temp;

	/*in order to avoid problems of whitespaces on the edges, the program will remove whitespaces from the edges of the token (either from the beginning until a non-white character is encountered or from the end until the same occurance)*/
	for(; IS_WHITESPACE(*segment); segment++);
	for(char_temp = segment + strlen(segment)-1; IS_WHITESPACE(*char_temp); char_temp--) *char_temp = '\0';

	/* only if the segment ends with a colon can it be a label definition. following the above process, char_temp should point to the last character in segment */
	if( *char_temp != ':' ) return NO_LABEL; 

	/*if (excluding the colon) segment has more than the maximal amount of characters allowed in a label name, it contains an illegal name. It cannot be detected later on as name might be limited in size while segment is supposed to contain the whole section, as long as it was read from the file to begin with.*/
	if( (strlen(segment) - 1) > MAXLABEL){
		error_temp = add_error(&(host->errors), ILLEGAL_LABEL_NAME, line_n);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
		return error_temp;
	}

	/* slices the string to rid it of the colon and copies it onto name (the original string remains unchanged) */
	string_slicencpy(segment, name, 0, strlen(segment)-1);

	/* ensures the validity  of the found label name, emitting an error if it is not */
	error_temp = is_label_def_valid( name, *host );
	if( error_temp != NONE ) error_temp = add_error(&(host->errors), error_temp, line_n);
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	
	return error_temp;
}

errorType add_label_argument(label_arguments_table *lab_args, int line, int ind, boolean entry, char *arg){
	/*extends the table by 1 slot*/
	EXTEND_TABLE((*lab_args), struct label_arguments_table_line);

	lab_args->table[lab_args->length-1].line = line;
	lab_args->table[lab_args->length-1].word_ind = ind;
	lab_args->table[lab_args->length-1].entry = entry;
	lab_args->table[lab_args->length-1].external = 0; 
	lab_args->table[lab_args->length-1].address = 0;
	strcpy((*lab_args).table[lab_args->length-1].arg, arg);

	return NONE;
}

errorType add_label(label_table *labels, char name[MAXLABEL], int address, boolean code, boolean external, boolean data){
	struct label_table_line *line;
	
	/* extends the label table */
	EXTEND_TABLE((*labels), struct label_table_line)

	line = &( labels->table[labels->length - 1] ); /*the latest collum in the table*/

	strcpy((*line).name, name);
	(*line).value = address;
	(*line).code = code;
	(*line).external = external;
	(*line).data = data;

	(*line).entry = False; /*a label can never be added with entry enabled right off the get-go as entry tags are only assigned after the label table has been completed.*/

	return NONE;
}

struct label_table_line* get_label(label_table *labels, char *label_name){
	int i;
	char *char_temp;

	/*in order to avoid problems of whitespaces on the edges, the program will remove whitespaces from the edges of the token (either from the beginning until a non-white character is encountered or from the end until the same occurance)*/
	for(; IS_WHITESPACE(*label_name); label_name++);
	for(char_temp = label_name + strlen(label_name)-1; IS_WHITESPACE(*char_temp); char_temp--) *char_temp = '\0';
	
	if(label_name[0] == '&') label_name++; /*in order to ignore the potential & prefix when comparing names*/

	for(i = 0; i<labels->length; i++){
		if(strcmp(labels->table[i].name, label_name) == 0){
			return (labels->table) + i;
		}
	}
		
	return NULL; /*if a pointer wasn't already returned, the function could not find the label provided and so it returns a NULL pointer.*/
}

void update_data_labels(label_table labels, int IC){
	struct label_table_line *curr_lab;

	for(curr_lab = labels.table; curr_lab < labels.table + labels.length; curr_lab++)
		if((*curr_lab).data) (curr_lab->value) += IC;
}