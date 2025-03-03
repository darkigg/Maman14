#include "../Header Files/words.h"
/*this file includes functions that handle the words read and to be written during the assembler's operation*/

errorType add_word(word_table *tab, const int val, const int address, boolean is_code){
	/*extend the table of words, making place for an additional word*/
	EXTEND_TABLE( (*tab), struct word_table_line);

	/*if the address of the word to be added does not exist in the imaginary computer's memory, it shall be reported (as there is a maximal address to that said machine)*/
	if(address > MAX_ADDRESS || val > WORD_LIMIT)
		return NO_AVAILABLE_ADDRESS;

	/* if val exceeds the maximal value which can be stored in a word, it is an error and so shall be reported. */
	if(val > WORD_LIMIT) return VALUE_TOO_BIG;

	/*assign the provided values to the newly allocated word*/
	(*tab).table[(*tab).length - 1].address = address;
	(*tab).table[(*tab).length - 1].word.value = val;
	(*tab).table[(*tab).length - 1].code = is_code;
	(*tab).table[(*tab).length - 1].data = !is_code;
	
	return NONE;
}

int create_regular_word(int value, boolean A, boolean R, boolean E){
	int result = 0; /* the ultimate result of the process*/

	result+= E; /* the first bit to the right is the E */
	result+= R<<1; /* the 2nd bit to the right is the R, so it should be moved by 1 left */
	result+= A<<2; /* the 3rd bit to the right is the A, so it should be moved by 2 left */
	result+= value<<3; /* the rest of the bits (out of the 24 of a word) to the left of these store the value */

	if(value > MAX_ADDRESS) /*MAX_ADDRESS is 2^21, which is also the max value which can be stored by a regular word considering 3 of the 24 bits are used for something else.*/
		result = ~0; /* an illegal value, which will definetly lead to an error later when an attempt to add the word is added to the table */

	return result;
}

void init_startword(startword *word){
	word->A = 0;
	word->R = 0;
	word->E = 0;
	word->destination_address = 0;
	word->destination_register = 0;
	word->origin_address = 0;
	word->origin_register = 0;
	word->funct = 0;
	word->opcode = 0;
}

int startword_to_value(startword word){
	int result = 0;

	/* converts the startword to an integer according the bits order specified in page 27 of the task's definition */
	result+= word.E;
	result+= word.R << 1;
	result+= word.A << 2;
	result+= word.funct << 3;
	result+= word.destination_register << 8;
	result+= word.destination_address << 11;
	result+= word.origin_register << 13;
	result+= word.origin_address << 16;
	result+= word.opcode << 18;

	return result;
}

errorType append_words_table(word_table *tabA, const word_table tabB){
	struct word_table_line *line_temp_A, *line_temp_B; /* variables used for iteration in the loop copying the lines of tabB into the newly allocated segments of tabB */

	/* EXTEND_TABLE() is not used, as it is more efficient to extend the table by the required length in a single go rather than making multiple extensions of a single line; EXTEND_TABLE() can only add 1 line to the table at a time. */
	tabA->table = (struct word_table_line *) realloc(tabA->table, tabB.length * sizeof(struct word_table_line));
	if( tabA->table == NULL ) return UNABLE_TO_ALLOCATE_MEMORY; /* as the dynamic allocation failed */

	/* a loop iterating over all lines in tabB, copying their values into the matchingly allocated lines in tabA. */
	for(line_temp_A = (tabA->table) + (tabA->length), line_temp_B = tabB.table; line_temp_A && line_temp_B; line_temp_A++, line_temp_B++)
		*line_temp_A = *line_temp_B;

	return NONE; /* The only error which could have been encountered in this function is a failed dynamic allocation. If the program made it thus far, it was not encountered. */
}