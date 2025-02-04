/* a header containing non usage-specific types found throughout the entire program*/

#ifndef MAIN
#define MAIN

/* returns the length of an array of any type */
#define SIZE_OF_ARR(x) sizeof(x)/sizeof(x[0])

/* checks whether a char x is a letter */
#define IS_LETTER(x) ( ('a' <= x && x <= ' z') || ('A' <= x && x <= 'Z') )

/* array of all words used by the assembly language, represented as strings*/
#define LANGUAGE_WORDS {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "mcro", "mcroend", ".data", ".string", ".extern", ".entry", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r0"}

/* used to represent booleanic resaults of functions */
typedef enum{
	True = 1,
	False = 0
} boolean;

/**
 * Finds out whether str is a word already used by the language or not.
 * @param str the word to check.
 * @return True if str is a word used by the language, False otherwise.
 */
boolean is_language_word(char *str);

#endif