#include "../Header Files/read_am.h"

errorType second_passage(tables_host *host){
	/* the 2nd passage consists of a loop iterating over all label arguments detected during the 1st passage */

	errorType error_temp;
	int i,
		word_val; /*the value of the word storing the value from the label*/

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
			if(current_label->external){
				error_temp = add_error( &(host->errors), CANNOT_GET_EXTERN_LABEL_ADDRESS, host->lab_args.table[i].line);
				if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
				continue; /*...to potentially discover errors in the next lines*/
			}

			/*the & operator indicates the value assigned is the difference between the address of the label and the address of the startword at the current line. All operations accepting this kind of arguments accept only a single argument, and so the address of the op word is simply the address of the label argument word minus 1.*/
			word_val = current_label->value - (host->words.table[host->lab_args.table[i].word_ind].address-1); 
			host->words.table[host->lab_args.table[i].word_ind].word.value = create_regular_word( word_val, True, False, False); /*assign the value calculated above and the ARE values to the necessary word.*/
		}
		else{ /*the argument requires the value of the label*/
			word_val = current_label->value; /*just use the value of the label for the value of the word*/
			host->words.table[host->lab_args.table[i].word_ind].word.value = create_regular_word( word_val, False, !(current_label->external), current_label->external); /*if the label is external R is disbaled and E is enabled, else it is the other way.*/
		}

	}
}