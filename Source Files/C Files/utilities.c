#include "../Header Files/utilities.h"

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

boolean is_string_numeric(char *str){
	boolean was_sign_encountered = False; /*whether or not the function already encountered a number sign mark (either + or -) or the start of a number*/
	boolean was_digit_encountered = False; /*whether or not the function already encountered a digit (necessary in order to ensure the function won't consider a standalone sign numeric)*/
	boolean was_end_of_num_encountered = False; /*whether or not the function already encountered a white character after a number*/

	for(; str != '\0'; str++){
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