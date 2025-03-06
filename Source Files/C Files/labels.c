#include <stdlib.h>
#include <string.h>

#include "../Header Files/labels.h"

/*this file includes functions for handling labels*/


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

errorType is_label_def_valid( const char *label, const tables_host host ){
	int i, char_temp;

	macro_table macros; /*more convenient access to the macro table*/
	label_table other_labels; /*more convenient access to the label table*/

	macros = host.macros;
	other_labels = host.labels;
	
	/* if the label name is not composed solely of letters and digits, the name is illegal */
	for( char_temp = label[0], i=0; char_temp != '\0'; char_temp = label[++i] ){
		if( !((char_temp >= 'a' && char_temp <= 'z') || /*is the current char a lower letter?*/
			(char_temp >= 'A' && char_temp <= 'Z') || /*or perhaps is it capital letter?*/
			(char_temp >= '0' && char_temp <= '9') /*or is it a digit?*/))
			return ILLEGAL_LABEL_NAME; /* if non of the above conditions are met, the label's no good*/
	}

	/* if the label name doesn't start with a letter, the name is illegal */
	if(IS_LETTER(label[0])) return ILLEGAL_LABEL_NAME;

	/* if the label name overlaps with a language word, it is illegal */
	if(is_language_word(label)) return ILLEGAL_LABEL_NAME;

	/* if the label name overlaps with a macro name, it is illegal */
	for(i = 0; i<SIZE_OF_ARR(macros); i++)
		if(strcmp(label, macros.table[i].name) == 0) 
			return ILLEGAL_LABEL_NAME;

	/* if a label by the same name has already been declared, it is illegal */
	for(i = 0; i<SIZE_OF_ARR(other_labels); i++)
		if(strcmp(label, other_labels.table[i].name) == 0) 
			return MULTIPLE_DEF_NOT_ALLOWED;

	return NONE;
}

errorType add_label(label_table *labels, char name[MAXLABEL], int address, boolean code, boolean external, boolean data){
	struct label_table_line *line;
	
	/* extends the label table */
	EXTEND_TABLE((*labels), struct label_table_line);

	line = &( (*labels).table[(*labels).length - 1] ); /*the latest collum in the table*/

	(*line).name = name;
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