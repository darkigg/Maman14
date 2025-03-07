#include "../HeaderFiles/read_am.h"

errorType data_inst(tables_host *host, char *line, int *DC, const int linecnt){
	char *segment; /*the currently iterated over token*/
	errorType error_temp = NONE;
	
	/* rids line of potential label declarations and the instruction call itself */
	line = get_arg_list(line);

	/*get_arg_list returns NULL if an argument list was not found; .data must receive at least some arguments and so an error must be reported*/
	if(line == NULL) error_temp = add_error(&(host->errors), NOT_ENOUGH_ARGUMENTS, linecnt);
	return error_temp;

	if(line[0] == ',') error_temp = add_error(&(host->errors), ILLEGAL_COMMA, linecnt); /*there's a comma at the beginning of the argument list, meaning there's a comma immediately following the instruction*/
	return error_temp;

	/* split it up by commas and scan */
	if(error_temp == NONE) for(segment  = strtok(line, ','); segment; segment = strtok(NULL, ',')){
		int value;

		if(is_comma_missing(segment)){/*if a comma is missing, add a missing comma error and ensure it succeeded*/
			error_temp = add_error(&(host->errors), MISSING_COMMA, linecnt);
			return error_temp;

			break; /*there is an error in the line, continuing to read it will be meaningless*/
		}

		else if(!is_string_numeric(segment)){/*if the argument is not numeric, space cannot be allocated to it*/
			error_temp = add_error(&(host->errors), ILLEGAL_ARGUMENT, linecnt);
			return error_temp;

			break; /*again, there is an error in the line, continuing to read it will be meaningless*/
		}

		value = atoi(segment); /*convert the argument to an integer*/ 
		error_temp = add_word( &(host->data_words), value, (*DC)++, False ); /*adds the argument to the table of words; increments the value of DC as a data word has been encountered. */
		ADD_WORD_ERROR_HANDLING(host, error_temp, linecnt)
		
	}

	return error_temp;
}

errorType string_inst(tables_host *host, char *line, int *DC, const int linecnt){
	errorType error_temp = NONE;
	int char_temp, /*stores the currently iterated over character*/
		i; 

	/* rids line of potential label declarations and the instruction call itself, bringing it to the beginning of the string */
	line = get_arg_list(line); 

	/*get_arg_list returns NULL if an argument list was not found; .string must receive 1 argument and so an error must be reported*/
	if(line == NULL){ 
		error_temp = add_error(&(host->errors), NOT_ENOUGH_ARGUMENTS, linecnt);
		return error_temp;
	}

	/*if the first character of the argument list is not a ", meaning it is not the beginning of a string, that argument is invalid and an error is to be reported*/
	if(line[0] != '"') { 
		error_temp = add_error(&(host->errors), ILLEGAL_ARGUMENT, linecnt);
		return error_temp;
	}

	/* a loop iterating over all characters in the string, but only if no errors were encountered so far */
	if(error_temp == NONE) for(i = 1, char_temp = line[i]; char_temp != '"'; char_temp = line[++i]){
		/*i starts at 1 because the first character in line is a ", yet it is not a part of the string*/

		error_temp = add_word( &(host->data_words), char_temp, (*DC)++, False ); /*adds the character to the table of words; increments the value of DC as a data word has been encountered. */
		ADD_WORD_ERROR_HANDLING(host, error_temp, linecnt)
	}

	/* a loop iterating what is left of the line after the string has ended, to ensure no additional arguments were listed as that is illegal */
	for(char_temp = line[++i]; char_temp != '\0'; char_temp = line[++i])
		if( !(IS_WHITESPACE(char_temp)) ) { /*if a character that is not white is encountered, an error must be reported*/
			error_temp = add_error(&(host->errors), EXTRANEOUS_TEXT, linecnt);
			return error_temp;
		}

	return error_temp;
}

errorType extern_inst(tables_host *host, char *line, const int linecnt){
	errorType error_temp = NONE;
	char label[MAXLABEL], /*stores the name of the label referenced in the instruction*/
		*char_ptr_temp; 

	/* rids line of potential label declarations and the instruction call itself, bringing it to the beginning of the label name */
	line = get_arg_list(line); 

	/*get_arg_list returns NULL if an argument list was not found; .extern must receive 1 argument and so an error must be reported*/
	if(line == NULL) { 
		error_temp = add_error(&(host->errors), NOT_ENOUGH_ARGUMENTS, linecnt);
		return error_temp;
	}

	/* a loop copying the suspected label name into the label string */
	for(char_ptr_temp = line; *char_ptr_temp != ' ' && (char_ptr_temp - line) <= MAXLABEL; char_ptr_temp++)
		label[char_ptr_temp-line] = *char_ptr_temp; /*char_ptr_temp-line is the index of the char pointed to by char_ptr_temp within the line string*/

	/* checks for additional arguments post label name, and potentially reports an error accordingly */
	for(; *char_ptr_temp != '\0'; char_ptr_temp++)
		if( !(IS_WHITESPACE((*char_ptr_temp))) ){
			error_temp = add_error(&(host->errors), EXTRANEOUS_TEXT, linecnt);
			return error_temp;
		}
	
	/* ensures the validity of the supposed label name */
	error_temp = is_label_def_valid(label, *host);
	if(error_temp != NONE){
		error_temp = add_error(&(host->errors), ILLEGAL_LABEL_NAME, linecnt);
		return error_temp;
	}

	/* in the case none of the above errors were encountered, the function adds label to the labels table as an external label */
	error_temp = add_label(&(host->labels), label, 0, 0, 1, 0);
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;

	return error_temp;
}

errorType firstphase_entry_inst(tables_host *host, char *line, const int linecnt){
	errorType error_temp = NONE;
	char label[MAXLABEL], /*stores the name of the label referenced in the instruction*/
		*char_ptr_temp; 

	/* rids line of potential label declarations and the instruction call itself, bringing it to the beginning of the label name */
	line = get_arg_list(line);

	/*get_arg_list returns NULL if an argument list was not found; .entry must receive 1 argument and so an error must be reported*/
	if(line == NULL) { 
		error_temp = add_error(&(host->errors), NOT_ENOUGH_ARGUMENTS, linecnt);
		return error_temp;
	}

	/* a loop copying the suspected label name into the label string */
	for(char_ptr_temp = line; *char_ptr_temp != ' ' && (char_ptr_temp - line) <= MAXLABEL; char_ptr_temp++)
		label[char_ptr_temp-line] = *char_ptr_temp; /*char_ptr_temp-line is the index of the char pointed to by char_ptr_temp within the line string*/

	/* checks for additional arguments post label name, and potentially reports an error accordingly */
	for(; *char_ptr_temp != '\0'; char_ptr_temp++)
		if( !(IS_WHITESPACE((*char_ptr_temp))) ){
			error_temp = add_error(&(host->errors), EXTRANEOUS_TEXT, linecnt);
			return error_temp;
		}

	/* adds the argument to the label arguments table, so that it will be inferred during the 2nd assembler phase */
	error_temp = add_label_argument( &(host->lab_args), linecnt, -1, label);
	
	/* return either NONE (the initial value) or the most recently encountered error */
	return error_temp;
}