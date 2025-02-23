#include "../Header Files/words.h"
/*this file includes functions that handle the words read and to be written during the assembler's operation*/

errorType add_word(word_table *tab, const int val, const int address){
	/*extend the table of words, making place for an additional word*/
	EXTEND_TABLE( (*tab), struct word_table_line);

	/*if the address of the word to be added does not exist in the imaginary computer's memory, it shall be reported (as there is a maximal address to that said machine)*/
	if(address > MAX_ADDRESS)
		return UNABLE_TO_ALLOCATE_MEMORY;

	/*assign the provided values to the newly allocated word*/
	(*tab).table[(*tab).length - 1].address = address;
	(*tab).table[(*tab).length - 1].word.value = val;
	
	return NONE;
}