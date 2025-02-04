#include <stdlib.h>

#include "../Header Files/tables.h"

boolean extend_table(label_table *table){
	(*table) = realloc(table, SIZE_OF_ARR(table) + 1);
	return (*table) != NULL;
}

boolean extend_table(assembler_error_table *table){
	(*table) = realloc(table, SIZE_OF_ARR(table) + 1);
	return (*table) != NULL;
}