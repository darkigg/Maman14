#include "../HeaderFiles/read_am.h"

errorType first_passage_line(char *line, tables_host *host, int *IC, int *DC, const int line_num){
	char segment[MAXLINE], /*the token of the line currently scanned*/
		label_name[MAXLABEL]; /*the name of a label potentially declared in this line*/

	/* the original (before change) value of the counter of the program used in the sentence*/
	int og_counter, i, line_len;

	errorType error_temp = NONE; /*the latest error encountered*/
	boolean is_label_definition; /*whether or not a label is being define in the current line*/
	sentenceType sentype; /*stores the type of the sentence*/
	
	/* if the sentence is a comment, it may be ignored */
	if(line[0] == ';') return NONE;

	line_len = strlen(line); /*it is more efficient to calculate this value once rather than doing so over and over again upon each loop iteration*/
	
	/* scan for the first literal word in the line (the first row of characters enclosed by spaces from both sides) */
	for(i = get_token(segment, line, ' ', 0, line_len); i>=0; i = get_token(segment, line, ' ', i, line_len)) {
		if( !is_str_empty(segment) ) break;
	}
	if(is_str_empty(segment)) return NONE; /*empty sentence*/

	/*scan for a potential label definition at the start of the line*/
	error_temp = scan_for_label(segment, host, line_num, label_name);
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
	if(error_temp != NONE && error_temp != NO_LABEL) return error_temp;


	if(error_temp != NO_LABEL) {
		/* case a label is defined in this line */
		error_temp = NONE; /*in order to avoid possible confusion*/
		is_label_definition = True;

		/* scans for the practically first literal word in the line, as the actual first one is a label declaration as was found above. i is not reset to 0 as it is important to continue iterating onwards from the point where the last loop concluded */
		for(i = get_token(segment, line, ' ', i, line_len); i>=0; i = get_token(segment, line, ' ', i, line_len)) {

			if( !is_str_empty(segment) ) 
				break;
		}	

		/* if i is negative, no arguments were found following the label declaration; that is illegal. */
		if(i<0){
			error_temp = add_error( &(host->errors), ILLEGAL_LABEL_DEFINITION, line_num);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
			return error_temp;
		}

	}
	
	/* check whether or not an instruction call is being made; the sentence can either include an instruction (starting with a dot) or an operation, and there is need to act accordingly for each of these options. */
	if(segment[0] == '.') sentype = INSTRUCTION;
	else sentype = OPERATION;

	switch(sentype){
		case INSTRUCTION:
			og_counter = *DC;	
			
			error_temp = handle_instruction_passage1(DC, line, host, line_num);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
			if(error_temp == NO_AVAILABLE_ADDRESS) return error_temp; /*if the error of no available address is encountered at this line, other errors are of lower importance in comparasion and therefore the function must return immediately with that error.*/

			/* case instruction was found to be the case */
			if(is_label_definition && error_temp != USELESS_LABEL) {
				error_temp = add_label(&(host->labels), label_name, og_counter, False, False, True); /*add the label to the label table.*/
				if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
			}
			if(error_temp == USELESS_LABEL) error_temp = NONE; /*in order to avoid confusion, as USELESS_LABEL is not an actual error*/
			break;

		case OPERATION:
			og_counter = *IC;
			
			error_temp = read_code_line(host, line, IC, line_num, False);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
			if(error_temp == NO_AVAILABLE_ADDRESS) return error_temp; /*if the error of no available address is encountered at this line, other errors are of lower importance in comparasion and therefore the function must return immediately with that error.*/

			/* case an operation execution was found to be the case. */
			if(is_label_definition) {
				error_temp = add_label(&(host->labels), label_name, og_counter, True, False, False); /*add the label to the label table*/
				if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
			}
			break;
		
		default:
			break;
	}

	return error_temp;

}

errorType handle_instruction_passage1(int *DC, char *line, tables_host *host, const int linecnt){
	char segment[MAXLINE];
	int i, line_len;
	errorType error_temp = NONE;

	line_len = strlen(line); /*again, it is more efficient not to calculate the length of a string over and over again. */

	for(i = get_token(segment, line, ' ', 0, line_len); i>=0; i = get_token(segment, line, ' ', i, line_len)) 
		/*it is required to start scanning at the instruction name, a section starting with a dot is an insturction. */
		if(segment[0] == '.') break;
	
	if(strcmp(segment, ".data") == 0){
		/* case for .data instruction*/
		error_temp = data_inst(host, line, DC, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
	}
	else if(strcmp(segment, ".string") == 0){
		/* case for .string instruction*/
		error_temp = string_inst(host, line, DC, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
	}
	else if(strcmp(segment, ".extern") == 0){
		/* case for .extern instruction*/
		error_temp = extern_inst(host, line, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
		else if(error_temp != NONE) return error_temp;

		error_temp = USELESS_LABEL;
	}
	else if(strcmp(segment, ".entry") == 0){
		/* case for .entry instruction*/ 
		error_temp = firstphase_entry_inst(host, line, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
		else if(error_temp != NONE) return error_temp;
		
		/* .entry is handled by the 2nd compilation phase, and so the function handling it does not conclude the handling. Yet, a label definition in the current line would be meaningless and the function must notify it is to be partially ignored. */
		error_temp = USELESS_LABEL;
	}
	else{

		if(does_include_illegal_comma(segment)) /*an illegal comma adjacent to the instruction's name will be considered a more imminent error than the instruction preceeding it not being identifiable.*/
			error_temp = add_error(&(host->errors), ILLEGAL_COMMA, linecnt);
		else
			error_temp = add_error(&(host->errors), ILLEGAL_INSTRUCTION_NAME, linecnt);
		
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
	}

	return error_temp;
}

errorType read_code_line(tables_host *host, char *line, int *IC, const int linecnt, boolean interpret_labels){
	
	operationType op_type; /* the type of operation executed in the line */
	errorType error_temp = NONE; 
	char token[MAXLINE]; /* stores the current token from line used by the function */
	startword op_word; /*the first word of the sentence found in line*/
	int startword_index, /* the index of the first word of the sentence found in line within the words table */
		expected_arg_count, /* the amount of arguments passed to the operation expected to be found in line */
		i, line_len;
	int funct_values[] = FUNCT_VALS; /*an array containing the funct values for each operation*/

	/*initializes the op_word:*/
	init_startword(&op_word);
	op_word.A = True; /*for startwords, A is always the triggered specifier*/

	line_len = strlen(line);
	/*makes token the name of the operation called*/
	for(i = get_token(token, line, ' ', 0, line_len); i>=0; i = get_token(token, line, ' ', i, line_len) ){
		if( token[strlen(token)-1] != ':' && !(IS_WHITESPACE(token[0])) && token[0]!='\0' /*it can't be the end of the string either*/ )
			break; /*if the token does not comprise of whitespaces and does not end with a colon (a label definition), it is the operation.*/
	}
	
	/*if a comma appears adjacent to the operation call without any seperating spaces, the error will be more imminent than a potential "operation does not exist error"*/
	if(does_include_illegal_comma(token)){
		add_error( &(host->errors), ILLEGAL_COMMA, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
		return error_temp;
	}

	/* identifies the operation */
	op_type = detect_op(token);

	/* is the operation valid? */
	if(op_type == ILLEGAL){
		error_temp = add_error( &(host->errors),ILLEGAL_FUNCTION_NAME, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
		return error_temp; /*no need to continue going over the line past the first error*/
	}

	/*if the operation is valid, a word should be allocated for the sentence where the first word shall be*/
	error_temp = add_word( &(host->words), 0, (*IC)++, True ); /*value is 0 for the value of op_word is yet unknown; it will be assigned later.*/
	ADD_WORD_ERROR_HANDLING(host, error_temp, linecnt)

	startword_index = host->words.length - 1; /*for the first word is now the most recent entry to the table */

	/* so far, the following data can be supplied to op_word regarding the sentence: */

	/*the funct, according to the array containing funct values by order of appearance in the operationType enum*/
	op_word.funct = funct_values[op_type]; 
	op_word.opcode = get_opcode(op_type);

	/*find out how many arguments does the identified operation expect and store that number in expected_arg_count*/
	expected_arg_count = op_arg_count(op_type);

	/*gets the argument list and ensures that if it's not supposed to be empty, it's not empty*/
	line = get_arg_list(line);
	if(line == NULL && expected_arg_count!=0) {
		error_temp = add_error( &(host->errors), NOT_ENOUGH_ARGUMENTS, linecnt);
		return error_temp; /*there is an error, and so there is no real reason to continue reading the line.*/
	}
	else if( line != NULL && expected_arg_count == 0){ /*of course, if there are arguments whilst none are expected that's also an error*/
		error_temp = add_error( &(host->errors), EXTRANEOUS_TEXT, linecnt);
		return error_temp; /*there is an error, and so there is no real reason to continue reading the line.*/
	}

	/*analyse the argument list*/
	if(expected_arg_count > 0) error_temp = read_op_args(&op_word, host, line, expected_arg_count, IC, linecnt, interpret_labels);
	if(error_temp != NONE) return error_temp;

	/*sets the value of the startword in the word table to the op_word infered thus far.*/
	(host->words.table[startword_index].word.value) = startword_to_value(op_word);

	return error_temp;

}

errorType read_op_args(startword *word, tables_host *host, char *arg_list, int expected_argument_count, int *IC, const int linecnt, boolean interpret_labels){

	int args_count, i, list_len;
	char token[MAXLINE]; /* stores the current token from line used by the function */
	errorType error_temp = NONE;
	int addressing_manner; /* stores the manner in which an argument is to be addressed */

	list_len = strlen(arg_list); /*more efficient to calculate once*/
	/* a loop iterating over all the arguments provided to the operation in the line, if there are any*/
	for(args_count = 0,i = get_token(token, arg_list, ',', 0, list_len); i>=0; i = get_token(token, arg_list, ',', i, list_len), args_count++){
		
		/**** ERROR CHECKING ****/

		if(is_string_empty(token)){ /*there's a token between 2 commas, between the begining of the argument list and a comma or between a comma and the end of the line, which is empty*/
			if( args_count == 0){
				error_temp = add_error( &(host->errors), ILLEGAL_COMMA, linecnt); /* in this case, the comma is directly following the operation, making it illegal */
				return error_temp;
			}
			else if( args_count >= expected_argument_count){
				error_temp = add_error( &(host->errors), EXTRANEOUS_TEXT, linecnt); /*int this case, the comma must be after all of the arguments, meaning it is an extraneous piece of text which cannot be spotted by conventional methods.*/
				return error_temp;
			}
			else {
				error_temp = add_error( &(host->errors), MULTIPLE_CONSECUTIVE_COMMAS, linecnt); /*if none of the above is the case, then 2 commas within the argument list must be consecutive.*/
				return error_temp;
			}
		}
		else if(args_count >= expected_argument_count){ /*if the token is not empty, there is an argument; if said argument appears after all expected arguments have already been scanned, it is extraneous text.*/
			error_temp = add_error( &(host->errors), EXTRANEOUS_TEXT, linecnt);
			return error_temp;
		}

		if(is_comma_missing(token)){ /*if 2 arguments or more appear within a single token*/
			/*** a note regarding this section: I am well aware that an operation cannot accept more than 2 arguments according to the task's description, and yet I prefer handling the following case without relying on that; have it capable of accounting for more arguments. ***/

			if(args_count < (expected_argument_count - 1)){
				/*if at least 2 additional are expected ( say 12 arguments are expected and so far 10 have been counted, 10 < (12-1) ), the missing comma is before any potential extraneous text.*/
				error_temp = add_error( &(host->errors), MISSING_COMMA, linecnt);
				return error_temp;
			}
			else{ /*if only a single argument (or 0, although that case is already handled by this point) is expected, and more appear within the token, an extraneous text error is more fitting.*/
				error_temp = add_error( &(host->errors), EXTRANEOUS_TEXT, linecnt);
				return error_temp;
			}
		}

		/**** ARGUMENT LIST INFERENCE ****/

		remove_spaces(token); /* makes token easier to read */

		switch(token[0]){ /*with the spaces removed, the first character of the argument can indicate which addressing method it will require*/
			case '#':
			/* case the argument is a numeric constant */ 
				addressing_manner = IMMEDIATE_ADDRESS;
				if(is_string_numeric(token + 1)){ /*checks whether token contains a valid integer (1 is added to token because token contains the prefix # which is not numeric nor is it a part of the number)*/
					error_temp = add_word( &(host->words), create_regular_word(atoi(token+1), True, False, False), (*IC)++, True); /*add the number to the words table*/
					ADD_WORD_ERROR_HANDLING(host, error_temp, linecnt)
				}

				break;
			case '&':
			/* case the argument is a suspected label address */
				addressing_manner = VARIABLE_ADDRESS;

			case 'r':
				if( (token[1] >= '0' && token[1] <= '7') && token[2] == '\0' /*the register is all the argument includes*/ ){
					/* case the argument is a register */
					addressing_manner =  DIRECT_REGISTER_ADDRESS;
					break;
				}

			default:
			/* case the argument is a suspected label */
				if(token[0] != '&') addressing_manner = DIRECT_ADDRESS; /*if token[0] is &, a different addressing method should be and already have been utilized*/

				/*create a word which will store the necessary value later on*/
				error_temp = add_word( &(host->words), 0, (*IC)++, True ); /*allocates a word slot for the address of the label*/
				ADD_WORD_ERROR_HANDLING(host, error_temp, linecnt)

				/*add an entry to the label arguments table so that a fitting value will be applied to the word during the 2nd assembler phase*/
				error_temp = add_label_argument( &(host->lab_args), linecnt, host->words.length-1 /*the most recent item of the table, as the word for the label is the most recent*/, False, token);
				if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);

				break;
		}
		
		if((expected_argument_count == 1 && args_count == 0) || (expected_argument_count == 2 && args_count == 1)){ /*in this case, the argument is the destination*/
			if(!is_address_method_valid(word->opcode, addressing_manner, DESTINATION)){ /*ensures the discovered addressing method is eligable for the operation*/
				error_temp = add_error(&(host->errors), ILLEGAL_ARGUMENT, linecnt);
				return error_temp;
			}
			if(addressing_manner == DIRECT_REGISTER_ADDRESS)
				word->destination_register = token[1] - '0'; /*if the argument is a register, the register number should be the 2nd character of the argument (the register specifier) minus the 0 character constant in order to be converted to an integer*/
			word->destination_address = addressing_manner;
		}
		else{ /*in this case, the argument is the origin (if it is not the destination and it is valid then it is the origin)*/
			if(!is_address_method_valid(word->opcode, addressing_manner, ORIGIN)){ /*ensures the discovered addressing method is eligable for the operation*/
				error_temp = add_error(&(host->errors), ILLEGAL_ARGUMENT, linecnt);
				return error_temp;
			}
			if(addressing_manner == DIRECT_REGISTER_ADDRESS)
				word->origin_register = token[1] - '0'; /*same situation as above*/
			word->origin_address = addressing_manner;
		}

	}

	return error_temp;
}