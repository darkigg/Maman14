/*This file contains prototypes for all functions related to words handling*/

#ifndef WORDS_FUNCTIONS
#define WORDS_FUNCTIONS

#include "constants.h"
#include "tables.h"
#include "words.h"

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