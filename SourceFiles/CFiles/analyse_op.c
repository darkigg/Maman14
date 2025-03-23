#include "../HeaderFiles/analyse_op.h"

operationType detect_op(char *op_text){
	/*contains the type of function ultimately detected*/
	operationType type = ILLEGAL;
	
	/*an array of all operation names, ordered by their appearance in the enum operationType*/
	char *opNames[] = FUNCTEXT;

	int i;
	char *char_temp;

	/*in order to avoid problems of whitespaces on the edges, the program will remove whitespaces from the edges of the token (either from the beginning until a non-white character is encountered or from the end until the same occurance)*/
	for(; IS_WHITESPACE(*op_text); op_text++);
	for(char_temp = op_text + strlen(op_text)-1; IS_WHITESPACE(*char_temp); char_temp--) *char_temp = '\0';

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

/******** FIX THIS DAMN FUNCTIONMMMMM */
boolean is_address_method_valid(int opcode, int address_method, int arg_type){
	/* this function operates according to the table present in page 44 of the task's description, in which the legal addressing methods for each operation are specified.*/
	switch(arg_type)
		case DESTINATION:{
			switch(address_method){
				case IMMEDIATE_ADDRESS:
				if(opcode == 1 || opcode == 13) return True;
				else return False;

				case DIRECT_ADDRESS:
				if(opcode != 14 && opcode != 15) return True;
				else return False;

				case VARIABLE_ADDRESS:
				if( opcode == 9 ) return True;
				else return False;

				case DIRECT_REGISTER_ADDRESS:
				if( opcode != 9 && opcode != 14 && opcode != 15 ) return True;
				else return False;

				default: return False; /*invalid*/
			}
		case ORIGIN:{
			switch(address_method){
				case IMMEDIATE_ADDRESS:
				case DIRECT_REGISTER_ADDRESS:
				if(opcode >= 0 && opcode <=2) return True;
				else return False;

				case DIRECT_ADDRESS:
				if(opcode >= 0 && opcode <=4) return True;
				else return False;

				case VARIABLE_ADDRESS: return False;

				default: return False; /*invalid*/
			}
		}

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