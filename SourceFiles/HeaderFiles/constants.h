/*This header contains all the constants of the program*/

#ifndef CONSTS
#define CONSTS

#define MAX_MACRO 31 /*max length of a macro name*/

#define FUNCOUNT 16 /*amount of operations*/

#define MAXFILE 100 /*maximal length of a file name*/

#define MAXLINE 80 /*maximal length of a line*/

#define MAXLABEL 31 /*maximal length of a label*/

#define INITIAL_ADDRESS 100 /* the first available address for words*/

#define MAX_ADDRESS 2097151 /* the maximal number which can be represented with 21 bits*/

#define WORD_LIMIT 16777216 /* the maximal number which can be represented with 24 bits*/

#define WHITESPACES " \t\n" 

/*an array of all operation names, ordered by their appearance in the below enum operationType*/
#define FUNCTEXT {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"}

#define FUNCT_VALS {0, 0, 1, 2, 0, 1, 2, 3, 4, 1, 2, 3, 0, 0, 0, 0} /*an array of all funct values for the operations*/

/* array of all words used by the assembly language, represented as strings*/
#define LANGUAGE_WORDS {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "mcro", "mcroend", ".data", ".string", ".extern", ".entry", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r0"}

/* an 'operation' is a general term for both instructions and functions */
#define ERROR_TEXTS /*an array containing all the texts to be printed on screen upon error discovery, with the texts in the same order as that of their error's appearance in the above enum*/\
	{"", /*for NONE, in order to not mess up the order*/\ 
	"Macro definition is illegal", /*ILLEGAL_MACRO_DEFINITION*/\
	"The line is longer (contains more characters) than the maximal legal line length (maximal amount of characters)", /*LINE_TOO_LONG*/\
	"The name of the declared label is illegal",/*ILLEGAL_LABEL_NAME*/\
	"Repeated declarations of a label by the same name are illegal",/*MULTIPLE_DEF_NOT_ALLOWED*/\
	"The definition of the label is illegal (e.g. it might be empty)",/*ILLEGAL_LABEL_DEFINITION*/\
	"An external label cannot be accepted as an entry",/*LABEL_ALREADY_EXTERNAL*/\
	"The function called does not exist",/*ILLEGAL_FUNCTION_NAME*/\
	"The instruction (a suspected operation with a dot prefix) called does not exist",/*ILLEGAL_INSTRUCTION_NAME*/\
	"Only a single comma can be used to split arguments apart, multiple are not allowed",/*MULTIPLE_CONSECUTIVE_COMMAS*/\
	"A comma cannot preceed all arguments in an arguments list",/*ILLEGAL_COMMA*/\
	"A comma is expected between separate arguments",/*MISSING_COMMA*/\
	"The operation called expects more arguments than it is provided with",/*NOT_ENOUGH_ARGUMENTS*/\
	"There is extraneous text after the conclusion of the operation call", /*EXTRANEOUS_TEXT*/\
	"An argument provided to the operation is either illegal or cannot be accepted by it",/*ILLEGAL_ARGUMENT*/\
	"A suspected label argument cannot be identified as any declared label",/*UNIDENTIFIED_LABEL*/\
	"The operator & cannot be used on external labels",/*CANNOT_GET_EXTERN_LABEL_ADDRESS*/\
	"The value supplied to the operation cannot be stored within the computer's memory for it is too big",/*VALUE_TOO_BIG*/\
	"There are not enough addresses in the machine to account for the program past this point"/*NO_AVAILABLE_ADDRESS*/}

typedef enum{
	True = 1,
	False = 0
} boolean;

enum address_method{
	IMMEDIATE_ADDRESS = 0,
	DIRECT_ADDRESS = 1,
	VARIABLE_ADDRESS = 2,
	DIRECT_REGISTER_ADDRESS = 3
};

enum argument_type{
	ORIGIN,
	DESTINATION
};

typedef enum{
	MOV = 0,
	CMP = 1,
	ADD = 2,
	SUB = 3,
	LEA = 4,
	CLR = 5,
	NOT = 6,
	INC = 7,
	DEC = 8,
	JMP = 9,
	BNE = 10,
	JSR = 11,
	RED = 12,
	PRN = 13,
	RTS = 14,
	STOP = 15,
	ILLEGAL /* a value meaning an illegal operation */
} operationType;

typedef enum{

	NONE,
	ILLEGAL_MACRO_DEFINITION,
	LINE_TOO_LONG,
	ILLEGAL_LABEL_NAME,
	MULTIPLE_DEF_NOT_ALLOWED, /*error for attempting to define multiple labels with the same name*/
	ILLEGAL_LABEL_DEFINITION,
	LABEL_ALREADY_EXTERNAL, /*...and an attempt is made to set it as an entry*/
	ILLEGAL_FUNCTION_NAME,
	ILLEGAL_INSTRUCTION_NAME,
	MULTIPLE_CONSECUTIVE_COMMAS,
	ILLEGAL_COMMA,
	MISSING_COMMA,
	NOT_ENOUGH_ARGUMENTS,
	EXTRANEOUS_TEXT,
	ILLEGAL_ARGUMENT,
	UNIDENTIFIED_LABEL, /*a value which is supposed to be a label does not refer to a real label*/
	CANNOT_GET_EXTERN_LABEL_ADDRESS,
	VALUE_TOO_BIG,
	NO_AVAILABLE_ADDRESS,
	UNABLE_TO_OPEN_FILE,
	INVALID_MACRO_NAME,

	UNABLE_TO_ALLOCATE_MEMORY, /*used when a dynamic allocation fails.*/
	
	/*demo errors, included in this type as they create unusual circumstances and require special handling*/
	NO_LABEL, 
	USELESS_LABEL
} errorType;

typedef enum{
	INSTRUCTION /*data*/,
	OPERATION /*code*/,
	COMMENT,
	EMPTY
} sentenceType;

#endif