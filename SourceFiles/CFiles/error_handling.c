#include "../HeaderFiles/error_handling.h"

errorType add_error(error_table *error_tab, errorType new_error, int line){
	EXTEND_TABLE((*error_tab), struct error_table_line)

	error_tab->table[(error_tab->length) - 1].error = new_error;
	error_tab->table[(error_tab->length) - 1].line_number = line;

	return new_error; /* if no error was encountered, the function shall return the error it was requested to (and successfully) added */
}

errorType is_label_def_valid( char *label, const tables_host host ){
	int i, char_temp;
	char *ptr_temp;

	macro_table macros; /*more convenient access to the macro table*/
	label_table other_labels; /*more convenient access to the label table*/

	macros = host.macros;
	other_labels = host.labels;

	/*in order to avoid problems of whitespaces on the edges, the program will remove whitespaces from the edges of the token (either from the beginning until a non-white character is encountered or from the end until the same occurance)*/
	for(; IS_WHITESPACE(*label); label++);
	for(ptr_temp = label + strlen(label)-1; IS_WHITESPACE(*ptr_temp); ptr_temp--) *ptr_temp = '\0';

	/* if the label name is not composed solely of letters and digits, the name is illegal */
	for( char_temp = label[0], i=0; char_temp != '\0'; char_temp = label[++i] ){
		if( !((char_temp >= 'a' && char_temp <= 'z') || /*is the current char a lower letter?*/
			(char_temp >= 'A' && char_temp <= 'Z') || /*or perhaps is it capital letter?*/
			(char_temp >= '0' && char_temp <= '9') /*or is it a digit?*/))
			return ILLEGAL_LABEL_NAME; /* if non of the above conditions are met, the label's no good*/
	}
	
	/* if the label name doesn't start with a letter, the name is illegal */
	if(!IS_LETTER(label[0])) return ILLEGAL_LABEL_NAME;

	/* if the label name overlaps with a language word, it is illegal */
	if(is_language_word(label)) return ILLEGAL_LABEL_NAME;

	/* if the label name overlaps with a macro name, it is illegal */
	for(i = 0; i<macros.length; i++)
		if(strcmp(label, macros.table[i].name) == 0) 
			return ILLEGAL_LABEL_NAME;

	/* if a label by the same name has already been declared, it is illegal */
	for(i = 0; i<other_labels.length; i++)
		if(strcmp(label, other_labels.table[i].name) == 0) 
			return MULTIPLE_DEF_NOT_ALLOWED;

	return NONE;
}

void end_prog(tables_host *tables){
	free_tables_host(tables);

	/*print out an error*/
	fprintf(stderr, "Not enough memory could be allocated for the program to properly compile");
	
	exit(1); /* 1 is used because the program terminated before conclusion of it's function */
}

int print_err(const error_table *error_table, char *filename){
	struct error_table_line *current_err; /*points to the line with the data of the currently iterated over error*/
	int i;

	char *error_messages[] = ERROR_TEXTS; /*an array of the texts of all errors in the program, sorted so that each error enum is matched to the appropriate text*/

	/*a loop iterating over all errors, printing them to the standard error*/
	for(current_err = error_table->table, i = 0; i<(error_table->length); current_err++, i++){
		fprintf(stderr, "In File %s, line %d: %s.\n", filename, current_err->line_number, error_messages[current_err->error]);
	}

	return i; /*returns i, 0 if no errors were encountered throughout the assembly process*/
}