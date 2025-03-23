#include "../HeaderFiles/read_am.h"
/*this folder contains the fundamental functions for translating the .am file into machine code*/

/*the basic function initiating the 2 main assembly stages*/
errorType translate_file(FILE *file, tables_host *host, int *ICF, int *DCF){
	/* DECLARATIONS */
	errorType error_temp = NONE; /*a variable naming convention throughout the .am file analysis, for variables containing the most recent error*/

	/* STAGE 1 */
	error_temp = first_passage(file, host, ICF, DCF);
	
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host); /* the most urgent error, with it there is both a practical and a theoretical impossibility of the compilitation process proceeding */
	printf("\nat last\n");
	/* STAGE 2 */
	error_temp = second_passage(host);
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
	printf("translation concluded\n");
	(*ICF) -= 100; /*as the ICF equals the instruction counter minus 100*/
	
	return error_temp;
}

/*the basic function initiating the assembly stages*/
errorType first_passage(FILE *file, tables_host *host, int *ICF, int *DCF){
	
	/* the currently read line */
	char line[MAXLINE + 2]; /*+2 for the sake of potential extraneous text and the '\0' character*/

	/* the most recently encountered error */
	errorType error_temp = NONE;

	/* counters */
	int line_counter = 0;
	int i;

	*ICF = 100;
	*DCF = 0;

	while( fgets(line, MAXLINE+2, file) != NULL ){

		if(strlen(line) > MAXLINE){ /*if the 81st character isn't \0, there are more than 80 characters in the line*/
			
			error_temp = add_error( &(host->errors), LINE_TOO_LONG, line_counter + 1 /*as the counter is only decremented later*/);
			
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);

			for(i = fgetc(file); i!='\n' && i!='\0' && i != EOF; i = fgetc(file)); /*reads the rest of the line, in order to not end up reading it later as a new separate line*/

			line_counter++;
		}
		else{
			printf("|%s|\n", line); 
			error_temp = first_passage_line(line, host, ICF, DCF, ++line_counter);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host); /* an error of not enough memory requires immidiate termination of the program */
			else if(error_temp == NO_AVAILABLE_ADDRESS) break; /*if there are no more available addresses for words in the imaginary computer, there is no need to go over the rest of the program */
		}
	}
	printf("first passage concluded:\n data tab len: %d\n instruction tab len: %d\n IC: %d\n DC: %d\n error: %d\n", host->data_words.length, host->words.length, *ICF, *DCF, error_temp);
	/* integrate the table of data words into the main table of words; if errors were encountered, it is not necessary */
	if(error_temp == NONE) {
		error_temp = append_data_words_table(&(host->words), &(host->data_words), *ICF);
		update_data_labels(host->labels, *ICF);
	}
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
	printf("append function concluded. first value: %d\n", host->words.table[0].word.value);
	return error_temp;

}

/*The entire 2nd passage*/
errorType second_passage(tables_host *host){
	/* the 2nd passage consists of a loop iterating over all label arguments detected during the 1st passage */

	errorType error_temp = NONE;
	int i,
		word_val; /*the value of the word storing the value from the label*/

	struct label_table_line* current_label; /* the line containing all the data regarding the label currently scanned */

	/*the loop iterating over all label arguments*/
	for(i = 0; i<host->lab_args.length; i++){
		current_label = get_label( &(host->labels), host->lab_args.table[i].arg);
		if(current_label == NULL){
			error_temp = add_error( &(host->errors), UNIDENTIFIED_LABEL, host->lab_args.table[i].line);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
			continue;
		}
		printf("you're wrong %d\n", host->lab_args.length);
		
		if(host->lab_args.table[i].entry) {printf("yo %d\n", current_label == NULL);
			if(!(current_label->external)){
				current_label->entry = True;
			}
			else{
				error_temp = add_error( &(host->errors), LABEL_ALREADY_EXTERNAL, host->lab_args.table[i].line); printf("Idk |%d|\n", error_temp);
				if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);
				continue;
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
			word_val = current_label->value - ((host->words.table[host->lab_args.table[i].word_ind]).address - 1); 
			word_val = create_regular_word( word_val, True, False, False);
			printf("&label arg value: %.6x\n", word_val);
			((host->words.table[host->lab_args.table[i].word_ind]).word.value) = word_val; /*assign the value calculated above and the ARE values to the necessary word.*/
		}
		else{ /*the argument requires the value of the label*/
			printf("lable usage reportttttttttttttttttttttttttttttttttie |%s| %d\n", current_label->name, current_label->value);
			word_val = current_label->value; /*just use the value of the label for the value of the word*/
			word_val = create_regular_word( word_val, False, !(current_label->external), current_label->external);
			printf("label arg value: %.6x\n", word_val);
			((host->words.table[host->lab_args.table[i].word_ind]).word.value) = word_val; /*if the label is external R is disbaled and E is enabled, else it is the other way.*/ /*PROBLEM ON THIS LINE*/
		}
	}

	return error_temp;
}
