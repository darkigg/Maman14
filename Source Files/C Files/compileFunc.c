#include "../Header Files/compileFunc.h"
/* this file includes the definitions of the functions processing code sentences in the assembly code into binary words */

errorType read_code_line(tables_host *host, char *line, int *IC, const int linecnt, boolean interpret_labels){
	
	operationType op_type; /* the type of operation executed in the line */
	errorType error_temp = NONE; 
	char *token; /* stores the current token from line used by the function */
	startword op_word; /*the first word of the sentence found in line*/
	int startword_index, /* the index of the first word of the sentence found in line within the words table */
		expected_arg_count; /* the amount of arguments passed to the operation expected to be found in line */
	int funct_values[] = FUNCT_VALS; /*an array containing the funct values for each operation*/

	/*initializes the op_word:*/
	init_startword(&op_word);
	op_word.A = True; /*for startwords, A is always the triggered specifier*/

	/*makes token the name of the operation called*/
	for(token = strtok(line, ' '); token; token = strtok(NULL, ' ') ){
		if( token[strlen(token)-1] != ':' && !(IS_WHITESPACE(token[0])) )
			break; /*if the token does not comprise of whitespaces and does not end with a colon (a label definition), it is the operation.*/
	}

	/* identifies the operation */
	op_type = detect_op(token);

	/* is the operation valid? */
	if(op_type == ILLEGAL){
		error_temp == add_error( &(host->errors),ILLEGAL_FUNCTION_NAME, linecnt);
		return error_temp; /*no need to continue going over the line past the first error*/
	}

	/*if the operation is valid, a word should be allocated for the sentence where the first word shall be*/
	error_temp = add_word( &(host->words), 0, (*IC)++, True ); /*value is 0 for the value of op_word is yet unknown; it will be assigned later.*/
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	startword_index = host->words.length - 1; /*for the first word is now the most recent entry to the table */

	/* so far, the following data can be supplied to op_word regarding the sentence: */

	/*the funct, according to the array containing funct values by order of appearance in the operationType enum*/
	op_word.funct = funct_values[op_type]; 
	op_word.opcode = get_opcode(op_type);

	/*find out how many arguments does the identified operation expect and store that number in expected_arg_count*/
	expected_arg_count = op_arg_count(op_type);

	/*gets the argument list and ensures it is not empty*/
	line = get_arg_list(line);
	if(line == NULL) {
		error_temp = add_error( &(host->errors), NOT_ENOUGH_ARGUMENTS, linecnt);
		return error_temp; /*there is an error, and so there is no real reason to continue reading the line.*/
	}

	/*analyse the argument list*/
	error_temp = read_op_args(&op_word, host, line, expected_arg_count, IC, linecnt, interpret_labels);
	if(error_temp != NONE) return error_temp;

	/*sets the value of the startword in the word table to the op_word infered thus far.*/
	host->words.table[startword_index].word.value = startword_to_value(op_word);

	return error_temp;

}

operationType detect_op(char *op_text){
	/*contains the type of function ultimately detected*/
	operationType type = ILLEGAL;
	
	/*an array of all operation names, ordered by their appearance in the enum operationType*/
	char *opNames[] = FUNCTEXT;

	int i;

	/*go over all operations, check for each one whether or not it is the one found within op_text*/
	for(i = 0; i<FUNCOUNT; i++){
		if(strcmp(op_text, opNames[i]) == 0)
			type = i; /*because opNames is ordered according the values in the enum operationType, i will always be both the index of a certain operation's name within opNames and the value of its corresponding enum constant*/
	}

	/* returns the operation type identified, or ILLEGAL if none such was */
	return type; 
}

int op_arg_count(operationType type){
	/*according to the groups listed in the assignment's description: */
	switch(type){
		case MOV:
		case CMP:
		case ADD:
		case SUB:
		case LEA:
		return 2;

		case CLR:
		case NOT:
		case INC:
		case DEC:
		case JMP:
		case BNE:
		case JSR:
		case RED:
		case PRN:
		return 1;

		case RTS:
		case STOP:
		default: /*in the unlikely case of type not matching any of the above values, 0 is a fitting return value*/
		return 0;
	}
}

errorType read_op_args(startword *word, tables_host *host, char *arg_list, int expected_argument_count, int *IC, const int linecnt, boolean interpret_labels){

	int i;
	char *token; /* stores the current token from line used by the function */
	errorType error_temp;
	int addressing_manner; /* stores the manner in which an argument is to be addressed */

	/* a loop iterating over all the arguments provided to the operation in the line, if there are any*/
	for(i = 0, token = strtok(arg_list, ','); token; token = strtok( NULL, ','), i++){
		
		/**** ERROR CHECKING ****/

		if(is_string_empty(token)){ /*there's a token between 2 commas, between the begining of the argument list and a comma or between a comma and the end of the line, which is empty*/
			if( i == 0){
				error_temp = add_error( &(host->errors), ILLEGAL_COMMA, linecnt); /* in this case, the comma is directly following the operation, making it illegal */
				return error_temp;
			}
			else if( i >= expected_argument_count){
				error_temp = add_error( &(host->errors), EXTRANEOUS_TEXT, linecnt); /*int this case, the comma must be after all of the arguments, meaning it is an extraneous piece of text which cannot be spotted by conventional methods.*/
				return error_temp;
			}
			else {
				error_temp = add_error( &(host->errors), MULTIPLE_CONSECUTIVE_COMMAS, linecnt); /*if none of the above is the case, then 2 commas within the argument list must be consecutive.*/
				return error_temp;
			}
		}
		else if(i >= expected_argument_count){ /*if the token is not empty, there is an argument; if said argument appears after all expected arguments have already been scanned, it is extraneous text.*/
			error_temp = add_error( &(host->errors), EXTRANEOUS_TEXT, linecnt);
			return error_temp;
		}

		if(is_comma_missing(token)){ /*if 2 arguments or more appear within a single token*/
			/*** a note regarding this section: I am well aware that an operation cannot accept more than 2 arguments according to the task's description, and yet I prefer handling the following case without relying on that; have it capable of accounting for more arguments. ***/

			if(i < (expected_argument_count - 1)){
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
					if(error_temp != NONE) return error_temp;
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
				if(error_temp != NONE) return error_temp;

				/*add an entry to the label arguments table so that a fitting value will be applied to the word during the 2nd assembler phase*/
				error_temp = add_label_argument( &(host->lab_args), linecnt, host->words.length-1 /*the most recent index, as the word for the label is the most recent*/, token);
				if(error_temp != NONE) return error_temp;

				break;
		}

		if(!is_address_method_valid(word->opcode, addressing_manner)){ /*ensures the discovered addressing method is eligable for the operation*/
			error_temp = add_error(&(host->errors), ILLEGAL_ARGUMENT, linecnt);
			return error_temp;
		}

		if((expected_argument_count == 1 && i == 0) || (expected_argument_count == 2 && i == 1)){ /*in this case, the argument is the destination*/
			if(addressing_manner == DIRECT_REGISTER_ADDRESS)
				word->destination_register = token[1] - '0'; /*if the argument is a register, the register number should be the 2nd character of the argument minus the 0 character constant in order to be converted to an integer*/
			word->destination_address = addressing_manner;
		}
		else{ /*in this case, the argument is the origin (if it is not the destination and it is valid then it is the origin)*/
			if(addressing_manner == DIRECT_REGISTER_ADDRESS)
				word->origin_register = token[1] - '0'; /*same situation as above*/
			word->origin_address = addressing_manner;
		}
	}
}

boolean is_address_method_valid(int opcode, int address_method){
	/* this function operates according to the table present in page 44 of the task's description, in which the legal addressing methods for each operation are specified.*/
	switch(address_method){
		case 0:
		if(opcode == 1 || opcode == 13) return True;
		else return False;

		case 1:
		if(opcode != 14 && opcode != 15) return True;
		else return False;

		case 2:
		if( opcode == 9 ) return True;
		else return False;

		case 3:
		if( opcode == 2 || opcode == 4 || opcode == 5 || opcode == 12 || opcode == 13 ) return True;
		else False;

		default: return False; /*invalid*/
	}
}

int get_opcode(operationType op){
	/*since the enum operationType is sorted according to the opcode ascending order, the op code can be calculated for each operation using the enum's value and the funct value*/
	int funct_values[] = FUNCT_VALS; /*an array containing the funct values for each operation*/

	/*if the funct is 0 for said operation, operationType is sorted so that the constant value corresponding to that operation is that operation's opcode*/
	if(funct_values[op] == 0) return op;
	/*else, operationType is ordered so it is possible to calculate the opcode by subtracting the funct value from the corresponding constant and adding 1; for instance, bne's opcode is 9, its corresponding constant is 10 and its funct value is 2, 10-2+1 is indeed 9.*/
	else return op - funct_values[op] + 1;
}

errorType add_label_argument(label_arguments_table *lab_args, int line, int ind, char *arg){
	/*extends the table by 1 slot*/
	EXTEND_TABLE((*lab_args), struct label_arguments_table_line);

	(*lab_args).table[lab_args->length-1].line = line;
	(*lab_args).table[lab_args->length-1].word_ind = ind;
	strcpy((*lab_args).table[lab_args->length-1].arg, arg);

	return NONE;
}