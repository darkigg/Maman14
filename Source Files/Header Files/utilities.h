/* a header containing non usage-specific types found throughout the entire program*/

#ifndef UTILITIES
#define UTILITIES

#include <string.h>

/* array of all words used by the assembly language, represented as strings*/
#define LANGUAGE_WORDS {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "mcro", "mcroend", ".data", ".string", ".extern", ".entry", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r0"}

#define MAXLINE 80

#define SIZE_OF_ADDRESS 21

/* checks whether a char x is a letter */
#define IS_LETTER(x) ( ('a' <= x && x <= ' z') || ('A' <= x && x <= 'Z') )

#define IS_WHITESPACE(x) ( x == ' ' || x == '\t' || x == '\n')

/* used to represent booleanic resaults of functions */
typedef enum{
	True = 1,
	False = 0
} boolean;

/**
 * A function taking a string, removing all the white characters in it and replacing those that are between 2 non-white characters with a given character.
 * @param str the string to edit. The max length of str is MAX_LINE.
 * @param replacement the character to replace the spaces with.
 */
void replace_spaces(char *str, char replacement);

/**
 * Copies all characters between the given indicies from the source string to the destination one, essentially slicing it.
 * @param source the original string from which to copy.
 * @param destination the string to copy the sliced part of source to.
 * @param start the start index of the slice.
 * @param end the end index of the slice.
 * @return whether or not the slicing the succeeded.
 */
boolean string_slicencpy(const char* source, char* destination, int start, int end);

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
boolean is_string_numeric(const char *str);

#endif