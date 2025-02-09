#include "../Header Files/errorHandling.h"

errorType add_error(error_table *error_table, errorType new_error, int line){
	EXTEND_TABLE((*error_table));

	(*error_table).table[SIZE_OF_ARR(error_table) - 1].error = new_error;
	(*error_table).table[SIZE_OF_ARR(error_table) - 1].line_number = line;

	return NONE; /* if no error was encountered, the function shall return so*/
}