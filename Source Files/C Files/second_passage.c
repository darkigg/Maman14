#include "../Header Files/read_am.h"

errorType second_passage(tables_host *host){
	/* the 2nd passage consists of a loop iterating over all label arguments detected during the 1st passage */

	errorType error_temp;
	int i;

	struct label_table_line* current_label; /* the line containing all the data regarding the label currently scanned */

	/*the loop iterating over all label arguments*/
	for(i = 0; i<host->lab_args.length; i++){
		current_label = get_label( &(host->labels), host->lab_args.table[i].arg);
		if(current_label == NULL){
			error_temp = add_error( &(host->errors), UNIDENTIFIED_LABEL, host->lab_args.table[i].line);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
		}

		/* if the word index is -1, the argument could have been sent here only by a .extern instruction*/
		if(host->lab_args.table[i].word_ind == -1){ 
			if(!current_label->external)
				current_label->entry = True;
			else{
				error_temp = add_error( &(host->errors), LABEL_ALREADY_EXTERNAL, host->lab_args.table[i].line);
				if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
			}
		}

		/*if the argument is not an entry instruction argument, it can require either the value or the address of the label*/
		else if(host->lab_args.table[i].arg[0] == '&'){ /*the argument requires the address of the label*/

		}
		else{ /*the argument requires the value of the label*/
			
		}

	}
}