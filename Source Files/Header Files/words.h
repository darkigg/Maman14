/* definition of the first word structure*/

#ifndef WORDS
#define WORDS

#define INITIAL_ADDRESS 100 /*the first available address for words*/
#define MAX_ADDRESS 2097151 /*the maximal number which can be represented with 21 bits*/

#include "errorHandling.h"
#include "tables.h"

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
 * Adds a data word to the table of read words. The word will be marked a data word.
 * @param tab pointer to the words table to add a word to.
 * @param val the value to assign to the added word.
 * @param DC the dc value at the time of adding the word (the address of the word).
 * @return the first error encountered during the function's process, usually NONE but potentially UNABLE_TO_ALLOCATE_MEMORY.
 */
errorType add_data_word(word_table *tab, int val, int DC);

/**
 * Adds a word to a table of words.
 * @param tab the table of words to add the word to.
 * @param val the value of the word.
 * @param address the address of the word.
 * @return the most recently encountered error during the function's execution.
 */
errorType add_word(word_table *tab, const int val, const int address);

#endif