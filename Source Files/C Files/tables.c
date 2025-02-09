#include <stdlib.h>

#include "../Header Files/tables.h"

/*initiate_tables_host cannot fail as it uses malloc(0) which practically cannot fail*/
void initiate_tables_host(tables_host *host){
	host->errors.table = malloc(0);
	host->labels.table = malloc(0);
	host->words.table = malloc(0);
	host->macros.table = malloc(0);
}

void free_tables_host(tables_host *host){
	free(host->errors.table);
	free(host->labels.table);
	free(host->words.table);
	free(host->macros.table);
}