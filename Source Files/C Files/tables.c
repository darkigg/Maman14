#include "../Header Files/tables.h"
/*this file includes definitions of functions for general table handling and tables host handling*/

/*initiate_tables_host does not return a certification of successful operation as it uses malloc(0) which practically cannot fail*/
void initiate_tables_host(tables_host *host){
	host->errors.table = (struct error_table_line*) malloc(0);
	host->labels.table = (struct label_table_line*) malloc(0);
	host->words.table = (struct word_table_line*) malloc(0);
	host->data_words.table = (struct word_table_line*) malloc(0);
	host->macros.table = (struct macro_table_line*) malloc(0);
	host->lab_args.table = (struct label_arguments_table_line*) malloc(0);
}

/*simply frees all tables using free()*/
void free_tables_host(tables_host *host){
	free(host->errors.table);
	free(host->labels.table);
	free(host->words.table);
	free(host->data_words.table);
	free(host->macros.table);
	frre(host->lab_args.table);
}