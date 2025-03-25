#include "../HeaderFiles/utilities.h"
/*this file includes definitions for functions which do not require any special types defined in the program (with the exception of constants or boolean)*/

void remove_spaces(char *str){

	char *get_ind, /* the address within str which is tested for whether it contains a whites character or not */
		*put_ind; /* the address within str where the next non-white character will be placed */

	/* a loop going over all addresses a part of str */
	for(get_ind = str, put_ind = str; (*get_ind) != '\0'; get_ind++){
		if(!IS_WHITESPACE((*get_ind))){ /* only if the address does not contain a white character can its value be put into put_ind */
			*put_ind = *get_ind;
			put_ind++; /*put_ind will only progress when a character is placed, and that will always be white according to the preceeding condition*/
		}
	}	
	*put_ind = '\0';
}

boolean string_slicencpy(const char* source, char* destination, int start, int end){

	int i, char_temp;
	int source_length; /*the length of the source string*/

	source_length = strlen(source);

	if( start > source_length || end > source_length ) return False; /* ensures the slicing is feasable*/

	for(i = start, char_temp = source[i]; i<end && char_temp != '\0' ; char_temp = source[++i])
		destination[i] = char_temp; /*copy the characters between start and end to destination*/
	
	destination[i] = '\0'; /*end the destination string*/

	return True;

}

boolean is_str_empty(char* str){
	/* a loop iterating over all characters in str,*/
	for(; (*str)!='\0'; str++)
		if(!IS_WHITESPACE(*str))
			return False; /*...returning that str is not empty if a non-white character was found.*/
	return True; /*but if non such was, str is deemed empty and so so is reported to the caller.*/
}

boolean is_string_numeric(char *str){
	boolean was_sign_encountered = False; /*whether or not the function already encountered a number sign mark (either + or -) or the start of a number*/
	boolean was_digit_encountered = False; /*whether or not the function already encountered a digit (necessary in order to ensure the function won't consider a standalone sign numeric)*/
	boolean was_end_of_num_encountered = False; /*whether or not the function already encountered a white character after a number*/

	for(; (*str) != '\0'; str++){
		if( IS_WHITESPACE((*str)) && was_sign_encountered){
			was_end_of_num_encountered = True;
			if(!was_digit_encountered) return False; /* there was, then, a standalone sign, which does not represented a number and is therefore illegal.*/
		}
		else if(!IS_WHITESPACE((*str)) && was_end_of_num_encountered) return False; /*there are either 2 numbers (or more) or a number and whatever else*/
		else if( ((*str) == '+' || (*str) == '-') && !was_sign_encountered && !was_digit_encountered ) was_sign_encountered = True; /*it was just encountered*/
		else if( (*str) >= '0' && (*str <= '9') ) {
			/* a digit was encountered and so the number has been initiated */
			was_sign_encountered = True;
			was_digit_encountered = True;
		}
		else if(!IS_WHITESPACE((*str))) return False; /*there are non-whitespace, non-numeric characters*/
		
	}

	return True; /*if none of the returns above already broke the function, the string is indeed numeric*/
}

boolean is_language_word(char *str){
	int i;
	char *words[] = LANGUAGE_WORDS, *curr;

	/* array going over all words used by the language, comparing each to str */
	for(i = 0, curr = words[i]; i < SIZE_OF_ARR(words); curr = words[++i]){
		
		/* if str is the same as the current language word, return True */
		if(strcmp(curr, str) == 0) return True;
	}

	/* if str wasn't recognized as any language word, return False */
	return False;
}

boolean is_string_empty(char *str){

	/* a loop iterating over the entirety of str, checking for each character whether it is white or not.*/
	for(; (*str) != '\0'; str++){
		if( !IS_WHITESPACE(*str) )
			return False; /*the string is not void of meaningful content*/
	}

	return True; /* the string is indeed void of meaningful content */
}

char *get_arg_list(char *line){
	int i, char_temp, prev_char,prev_non_white_char = '\0' /*prev_char stores the last non_white character*/;

	for(i = 0, char_temp = line[i];  char_temp != '\0'; prev_char = char_temp, char_temp = line[++i]){
		
		if(char_temp != ' ' && prev_char == ' ' && prev_non_white_char != ':' && prev_non_white_char){
			
			break; /*if the above conditions are met, we will have found the supposed beginning of the argument list, as it is the first block of characters seperated by space from something that is not a label declaration*/
		}
			
		prev_non_white_char = (IS_WHITESPACE(char_temp))? prev_non_white_char : char_temp;
	}
	
	return (char_temp == '\0')? NULL : line + i; /*if char is at index i within line and char is at the beginning of the argument list, line + i will point to that index; although if char_temp is the end of the line the function was deemed to return NULL*/
}

boolean is_comma_missing(char* token){
	boolean finished_reading_arg = False; /*did the function already encounter (within the token) a white space character preceeded by a non-white one?*/

	for(token++ /*no need to read the first char as the one before it was undefined*/; *token != '\0'; token++){
		if(IS_WHITESPACE((*token)) && !IS_WHITESPACE( (*(token - 1)) )) finished_reading_arg = True; /* if token is a white character and the previous character is not white, it is the end of an argument*/
		else if(!IS_WHITESPACE((*token)) && finished_reading_arg) return True; /*there is a non-white character despite the end of the argument having already been encountered*/
	}

	return False; /*no case of missing comma was encountered.*/
}

boolean does_include_illegal_comma(char *command){
	/*this function operates by finding (if exists) the first instance of a comma in the provided string, and turning it into the end of it whilst returning that a comma was encountered.
	by doing so, the function practically deletes from the string any unnecessary part appearing after the comma, limiting it to only the operation call and no more.*/
	
	for(; (*command) != '\0'; command++)
		if(*command == ',') {
			(*command) = '\0';
			return True;
		}

	return False;
}

int get_token(char* token_dest, char* token_src, const char delimeter, const int token_ind, int src_len){
	char *char_temp;

	if(token_ind >= src_len) return -1;

	for(char_temp = token_src + token_ind; ((*char_temp) != delimeter && char_temp != token_dest) && (*char_temp) != '\0'; char_temp++, token_dest++)
		(*token_dest) = (*char_temp);  
	
	(*token_dest) = '\0';

	return char_temp - token_src + 1;
}