#include "../Header Files/compileFunc.h"
/* this file includes the definitions of the functions processing code sentences in the assembly code into binary words */

errorType read_code_line(tables_host *host, char *line, int *IC, const int linecnt, boolean interpret_labels){
	
	operationType op_type; /* the type of operation executed in the line */
	errorType error_temp; 
	char *token; /* stores the current token from line used by the function */
	startword op_word; /*the first word of the sentence found in line*/
	int startword_index, /* the index of the first word of the sentence found in line within the words table */
		expected_arg_count; /* the amount of arguments passed to the operation expected to be found in line */
	int funct_values[] = FUNCT_VALS; /*an array containing the funct values for each operation*/

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
	error_temp = add_word( &(host->words), 0, (*IC)++ ); /*value is 0 for the value of op_word is yet unknown; it will be assigned later.*/
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	startword_index = host->words.length - 1; /*for the first word is now the most recent entry to the table */

	/* so far, the following data can be supplied to op_word regarding the sentence: */

	/*the funct, according to the array containing funct values by order of appearance in the operationType enum*/
	op_word.funct = funct_values[op_type]; 

	/*if the funct is 0 for said operation, operationType is sorted so that the constant value corresponding to that operation is that operation's opcode*/
	if(funct_values[op_type] == 0) op_word.opcode = op_type;
	/*else, operationType is ordered so it is possible to calculate the opcode by subtracting the funct value from the corresponding constant and adding 1; for instance, bne's opcode is 9, its corresponding constant is 10 and its funct value is 2, 10-2+1 is indeed 9.*/
	else op_word.opcode = op_type - funct_values[op_type] + 1;

	/*find out how many arguments does the identified operation expect and store that number in expected_arg_count*/
	expected_arg_count = op_arg_count(op_type);

	line = get_arg_list(line);

	/*analyse the argument list*/
	error_temp = read_op_args(&op_word, host, line, expected_arg_count, IC, linecnt, interpret_labels);
	if(error_temp != NONE) return error_temp;

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

	/* a loop iterating over all the arguments provided to the operation in the line, if there are any*/
	for(i = 0, token = strtok(arg_list, ','); token; token = strtok( NULL, ','), i++){
		if(is_string_empty(token)){
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
		

	}
}