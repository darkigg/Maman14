#include "../HeaderFiles/table_functions.h"
/*this file includes definitions of functions for general table handling and tables host handling*/

/*initiate_tables_host does not return a certification of successful operation as it uses malloc(0) which practically cannot fail*/
void initiate_tables_host(tables_host *host){
	host->errors.table = (struct error_table_line*) malloc(0);
	host->labels.table = (struct label_table_line*) malloc(0);
	host->words.table = (struct word_table_line*) malloc(0);
	host->data_words.table = (struct word_table_line*) malloc(0);
	host->macros.table = (struct macro_table_line*) malloc(0);
	host->lab_args.table = (struct label_arguments_table_line*) malloc(0);

	host->errors.length = 0;
	host->labels.length = 0;
	host->words.length = 0;
	host->data_words.length = 0;
	host->macros.length = 0;
	host->lab_args.length = 0;

	host->errors.valid = True;
	host->labels.valid = True;
	host->words.valid = True;
	host->data_words.valid = True;
	host->macros.valid = True;
	host->lab_args.valid = True;
}

/*simply frees all tables using free()*/
void free_tables_host(tables_host *host){

	if(host->errors.valid) free(host->errors.table);
	if(host->labels.valid) free(host->labels.table);
	if(host->words.valid) free(host->words.table);
	if(host->data_words.valid)free(host->data_words.table);
	if(host->macros.valid) free(host->macros.table);
	if(host->lab_args.valid) free(host->lab_args.table);
}
