/* definition of the first word structure*/

#ifndef WORDS
#define WORDS

#define INITIAL_ADDRESS 100 /* the first available address for words*/
#define MAX_ADDRESS 2097151 /* the maximal number which can be represented with 21 bits*/
#define WORD_LIMIT 16777216 /* the maximal number which can be represented with 24 bits*/

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
 
typedef struct as_regular_word{
	unsigned int A : 1;
	unsigned int R : 1;
	unsigned int E : 1;
	int value : 21;
} default_word; /*default_word is a struct used to represent arguments provided to a code line*/

/* all words are eventually converted to this one, as a word is a mere sequence of 24 bits*/
typedef struct as_word{
	int value : 24;
} assembly_word;

/**
 * Table type capable of containting all word bit values and their addresses.
 */
struct word_table_line{
	assembly_word word;
	int address : 21; /*the maximal bits in which an address can be stored*/
	int data : 1;
	int code : 1;
};
typedef struct{
	struct word_table_line *table;
	int length;
} word_table;

#define ADD_WORD_ERROR_HANDLING(tHost, eTemp, lCount) /*tHost is a pointer to the tables host, eTemp is the error temporary variable, and lCount is the number of the line.*/\
	if(eTemp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(tHost); /*if memory allocation cannot be enacted, the program shall be terminated*/\
	else if(eTemp != NONE){\
		/*if add_word returned any other error (and it could have), that error shall be reported in the usual procedure.*/\
		eTemp = add_error( &(tHost->errors), NO_AVAILABLE_ADDRESS, lCount);\
		if(eTemp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(tHost);\
		else return eTemp;\
	}

/*includes should be after all the type declarations, to avoid situations of necessary declarations not being made prior to the files inclusion*/
#include "errorHandling.h"
#include "tables.h"


/**
 * Given a startword, the function initiallizes all of its values to 0.
 * @param word a pointer to the startword to initiallize.
 */
void init_startword(startword *word);

/**
 * Adds a word to a table of words.
 * @param tab the table of words to add the word to.
 * @param val the value of the word.
 * @param address the address of the word.
 * @param is_code whether or not the word is a code word. If not, it is assumed data.
 * @return the most recently encountered error during the function's execution.
 */
errorType add_word(word_table *tab, const int val, const int address, boolean is_code);

/**
 * Given a 21 bits value and A, R, E fields, the function converts it to an integer according to the necessary bit representation (in 24 bits).
 * @param value the value of the regular word.
 * @param A the A value, True for enabled (1) and False for disabled (0).
 * @param R the R value.
 * @param E the E value.
 * @return an integer with the bits triggered according to the provided parameters, can be added to the words table.
 */
int create_regular_word(int value, boolean A, boolean R, boolean E);

/**
 * Given a startword, this function converts it to an integer according to the necessary bit representation (in 24 bits).
 * @param word the startword to convert.
 * @return the result of the convertion; can be added to the words table.
 */
int startword_to_value(startword word);

/**
 * Given 2 word tables, the function appends the latter to the former. Defined only for word tables as only they require it.
 * @param tabA pointer to the table, to which the other will be appended.
 * @param tabB the table appended to tabA.
 * @param IC the ultimate IC value.
 * @return the most recently encountered error during the function's execution.
 */
errorType append_data_words_table(word_table *tabA, const word_table tabB, int IC);

#endif