/*This header includes general macros and functions for handling the different parts of the program, which do not depend on any new type defined in the program*/

#ifndef UTILITIES
#define UTILITIES

#include "string.h"

#include "constants.h"

/* checks whether a char x is a letter */
#define IS_LETTER(x) ( ('a' <= x && x <= 'z') || ('A' <= x && x <= 'Z') )

#define IS_WHITESPACE(x) ( x == ' ' || x == '\t' || x == '\n' || x == '\r' || x == '\v' || x == '\f')

#define SIZE_OF_ARR(x) ( sizeof(x)/sizeof(x[0]) )

/**
 * A function taking a string and removing all the white characters in it.
 * @param str the string to edit.
 */
void remove_spaces(char *str);

/**
 * Copies all characters between the given indicies from the source string to the destination one, essentially slicing it.
 * @param source the original string from which to copy.
 * @param destination the string to copy the sliced part of source to.
 * @param start the start index of the slice.
 * @param end the end index of the slice, excluded from the copy.
 * @return whether or not the slicing the succeeded.
 */
boolean string_slicencpy(const char* source, char* destination, int start, int end);

/**
 * For a given string, checks whether it contains any not-white characters.
 * @param str the string to check.
 * @return True if the str comprises of white characters alone, false otherwise.
 */
boolean is_str_empty(char* str);

/**
 * Finds out whether str is a word already used by the language or not.
 * @param str the word to check.
 * @return True if str is a word used by the language, False otherwise.
 */
boolean is_language_word(char *str);

/**
 * Finds out whether a given string is numeric or not, e.g. can it be converted to an integer without any non_white characters remaining unused.
 * The string is also considered not numeric if it includes more than a single number. 
 * @param str the string to check.
 * @return whether or not str can be converted to an int without non white characters remaining unused.
 */
boolean is_string_numeric(char *str);

/**
 * Finds out whether or not a given string contains any character other than white characters.
 * @param str the string to check.
 * @return whether or not a non-white character was found in str.
 */
boolean is_string_empty(char *str);

/**
 * This function gets the start of the argument list for a certain line.
 * @param line the line to seek the argument list in.
 * @return a pointer to the beginning of the argument list (without preceeding spaces), or NULL if there is no.
 */
char *get_arg_list(char *line);

/**
 * Given a token between 2 commas, this function checks whether or not the token contains more arguments than legal.
 * @param token ther token.
 * @return whether or not there is more than a single argument in the token (e.g. a non white character spotted after the end of the argument).
 */
boolean is_comma_missing(char* token);

/**
 * Given a string of text, a destination and an index, this function will extract the first token from the character token from the string of text into the destination.
 * @param token_dest the string destination to which the token will be copied. Must be long enough to store the token.
 * @param token_src the string from which the tokens will be extracted.
 * @param delimeter the character splitting up the string into tokens.
 * @param token_ind the index from which to start collecting the token.
 * @param src_len the length of token_src.
 * @return the index of the next character after the delimeter closing the token within token_src, or 0 if token_ind exceeds or equals src_len.
 */
int get_token(char* token_dest, char* token_src, const char delimeter, const int token_ind, int src_len);

#endif