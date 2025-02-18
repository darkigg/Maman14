#include "../Header Files/words.h"

errorType add_data_word(word_table *tab, int val, int DC){
	EXTEND_TABLE( (*tab), struct word_table_line);

	(*tab).table[(*tab).length - 1].address = DC;
	(*tab).table[(*tab).length - 1].value = val;
	
	return NONE;
}