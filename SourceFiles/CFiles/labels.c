#include "../HeaderFiles/label_handling.h"

errorType scan_for_label(const char *segment, tables_host *host, int line_n, char *name){
	
	/****** TEMPORARY COMMENT - THIS FUNCTION MUST NO LONGER ADD THE LABELS IT FINDS */

	errorType error_temp; /*temporary storage for potentially encountered errors*/

	/* only if the segment ends with a colon can it be a label definition */
	if( !(segment[SIZE_OF_ARR(segment) - 1] == ':') ) return NO_LABEL; 

	/*if (excluding the colon) segment has more than the maximal amount of characters allowed in a label name, it contains an illegal name. It cannot be detected later on as name might be limited in size while segment is supposed to contain the whole section, as long as it was read from the file to begin with.*/
	if( (strlen(segment) - 1) > MAXLABEL){
		
		error_temp = add_error(&(host->errors), ILLEGAL_LABEL_NAME, line_n);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	}

	/* slices the string to rid it of the prenthesis and copies it onto name (the original string remains unchanged) */
	string_slicencpy(segment, name, 0, SIZE_OF_ARR(segment)-2);

	/* ensures the validity  of the found label name, emitting an error if it is not */
	error_temp = is_label_def_valid( name, *host );
	if( error_temp != NONE ) error_temp = add_error(&(host->errors), error_temp, line_n);
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	
	return error_temp;
}

errorType add_label_argument(label_arguments_table *lab_args, int line, int ind, char *arg){
	/*extends the table by 1 slot*/
	EXTEND_TABLE((*lab_args), struct label_arguments_table_line);

	(*lab_args).table[lab_args->length-1].line = line;
	(*lab_args).table[lab_args->length-1].word_ind = ind;
	strcpy((*lab_args).table[lab_args->length-1].arg, arg);

	return NONE;
}

errorType add_label(label_table *labels, char name[MAXLABEL], int address, boolean code, boolean external, boolean data){
	struct label_table_line *line;
	
	/* extends the label table */
	EXTEND_TABLE((*labels), struct label_table_line);

	line = &( (*labels).table[(*labels).length - 1] ); /*the latest collum in the table*/

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

	for(i = 0; i<labels->length; i++)
		if(strcmp(labels->table[i].name, label_name) == 0)
			return (labels->table) + i;

	return NULL; /*if a pointer wasn't already returned, the function could not find the label provided and so it returns a NULL pointer.*/
}