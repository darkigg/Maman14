#include "../Header Files/read_am.h"
/*this file includes definitions for central and fundumental operations performed during the interpertation process of the .am file*/

errorType translate_file(FILE *file, tables_host *host){
	/* DECLARATIONS */
	char line[MAXLINE]; /*stores the current line*/
	int line_counter = 0; /*counter of lines read so far*/

	/*counters*/
	int IC = 0, DC = 0;

	/* STAGE 1 */
	first_passage(file, host);

	/* STAGE 2 */

	/*free all out of use objects from the heap*/

}

char *get_arg_list(char *line){
	int i, char_temp, prev_char,prev_non_white_char = '\0' /*prev_char stores the last non_white character*/;
	boolean was_comment_passed = False;

	for(char_temp = line[0], i = 0; char_temp != '\0'; prev_char = char_temp, char_temp = line[++i]){
		if(char_temp != ' ' && prev_char == ' ' && prev_non_white_char != ':')
			break; /*if the above conditions are met, we will have found the supposed beginning of the argument list, as it is the first block of characters seperated by space from something that is not a label declaration*/

		prev_non_white_char = (IS_WHITESPACE(char_temp))? prev_non_white_char : char_temp;
	}

	return (char_temp == '\0')? NULL : line + i; /*if char is at index i within line and char is at the beginning of the argument list, line + i will point to that index; although if char_temp is the end of the line the function was deemed to return NULL*/
}