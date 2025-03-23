/*this header contains declarations of word types and macros related to words and their handling*/

#ifndef WORDS
#define WORDS

#define ADD_WORD_ERROR_HANDLING(tHost, eTemp, lCount) /*tHost is a pointer to the tables host, eTemp is the error temporary variable, and lCount is the number of the line.*/\
	if(eTemp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(tHost); /*if memory allocation cannot be enacted, the program shall be terminated*/\
	else if(eTemp != NONE){\
		/*if add_word returned any other error (and it could have), that error shall be reported in the usual procedure.*/\
		eTemp = add_error( &(tHost->errors), NO_AVAILABLE_ADDRESS, lCount);\
		if(eTemp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(tHost);\
		return eTemp;\
	}

typedef struct as_first_word{

	unsigned int opcode : 6;
	unsigned int origin_address : 2;
	unsigned int origin_register : 3;
	unsigned int destination_address : 2;
	unsigned int destination_register : 3;
	unsigned int funct : 6;
	unsigned int A : 1;
	unsigned int R : 1;
	unsigned int E : 1;

} startword; /*startword is a struct used to represent the first word of an instruction*/

/* all words are eventually converted to this one, as a word is a mere sequence of 24 bits*/
typedef struct as_word{
	unsigned int value : 24;
} assembly_word;

#endif