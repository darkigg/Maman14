#include "string.h"

#include "../Header Files/words.h"

boolean is_language_word(char *str){
	int i;
	char **words = LANGUAGE_WORDS, *curr;

	/* array going over all words used by the language, comparing each to str */
	for(i = 0, curr = words[i]; i < SIZE_OF_ARR(words); curr = str[++i]){
		
		/* if str is the same as the current language word, return True */
		if(strcmp(curr, str) == 0) return True;
	}

	/* if str wasn't recognized as any language word, return False */
	return False;
}