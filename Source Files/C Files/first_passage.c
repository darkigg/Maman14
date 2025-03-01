#include "../Header Files/read_am.h"
/*this file includes functions handling the core of the first passage of the assembler*/

errorType first_passage(FILE *file, tables_host *host){
	
	/* the currently read line */
	char line[MAX_LINE];

	/* the most recently encountered error */
	errorType error_temp = NONE;

	/* counters */
	int DC = 0, IC = INITIAL_ADDRESS, line_counter = 0;

	while( fgets(line, MAX_LINE, file) != NULL ){
		error_temp = first_passage_line(line, host, &IC, &DC, ++line_counter);

		/* An error of not enough memory requires as hurried a return to main as possible; it will lead the assembler to break if it continues. */
		if(error_temp = UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	}

	/* integrate the table of data words into the main table of words */
	
	return error_temp;

}

errorType first_passage_line(char *line, tables_host *host, int *IC, int *DC, const int line_num){
	char *segment, /*the token of the line currently scanned*/
		label_name[MAXLABEL]; /*the name of a label potentially declared in this line*/

	/* the original (before change) value of the counter of the program used in the sentence*/
	int og_counter;

	errorType error_temp = NONE; /*the latest error encountered*/
	boolean is_label_definition; /*whether or not a label is being define in the current line*/
	sentenceType sentype; /*stores the type of the sentence*/

	/* if the sentence is a comment, it may be ignored */
	if(line[0] == ';') return NONE;

	/* scan for the first literal word in the line (the first row of characters enclosed by spaces from both sides) */
	for(segment = strtok(line, ' '); segment; segment = strtok(NULL, ' ')) {
		if( strlen(segment) != 0 || segment == NULL) break;
	}
	if(segment == NULL) return NONE; /*empty sentence*/
	
	/*scan for a potential label definition at the start of the line*/
	error_temp = scan_for_label(segment, host, line_num, label_name);
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;

	if(error_temp != NO_LABEL) {
		/* case a label is defined in this line */
		error_temp == NONE; /*in order to avoid possible confusion*/
		is_label_definition = True;

		/* scans for the practically first literal word in the line, as the actual first one is a label declaration as was found above */
		for(segment = strtok(line, ' '); segment; segment = strtok(NULL, ' ')) 
			if( strlen(segment) != 0) 
				break;

		/* if segment is NULL, no arguments were found following the label declaration; that is illegal. */
		if(segment == NULL){
			error_temp = add_error( &(host->errors), ILLEGAL_LABEL_DEFINITION, line_num);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return UNABLE_TO_ALLOCATE_MEMORY;
		}

	}

	/* check whether or not an instruction call is being made; the sentence can either include an instruction (starting with a dot) or an operation, and there is need to act accordingly for each of these options. */
	if(segment[0] == '.') sentype = INSTRUCTION;
	else sentype = OPERATION;

	switch(sentype){
		case INSTRUCTION:
			og_counter = *DC;	

			/****** POTENTIAL PROBLEM HERE - YOU ARE YET UNCERTAIN REGARDING THE PRECISE METHOD OF HANDLING LABEL DEFINITIONS IN LINES WITH THE INSTRUCTION .extern AND .entry ****************************/
			error_temp = handle_instruction_passage1(DC, line, host, line_num);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;

			/* case instruction was found to be the case */
			if(is_label_definition && error_temp != USELESS_LABEL) {
				add_label(&(host->labels), label_name, og_counter, False, False, error_temp != USELESS_LABEL); /*add the label to the label table, but only enable data tag if the label is not to be ignored.*/
			}
			break;

		case OPERATION:
			og_counter = *IC;

			error_temp = read_code_line(host, line, IC, line_num, False);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;

			/* case an operation execution was found to be the case. */
			if(is_label_definition) {
				add_label(&(host->labels), label_name, og_counter, True, False, False); /*add the label to the label table*/
			}
			break;
		
		default:
			break;
	}

	return error_temp;

}

errorType handle_instruction_passage1(int *DC, char *line, tables_host *host, const int linecnt){
	char *segment;
	errorType error_temp = NONE;

	for(segment = strtok(line, ' '); segment; segment = strtok(NULL, ' ')) 
		/*it is required to start scanning at the instruction name, a section starting with a dot is an insturction. */
		if(segment[0] == '.') break;

	if(strcmp(segment, ".data") == 0){
		/* case for .data instruction*/
		error_temp = data_inst(host, line, DC, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	}
	else if(strcmp(segment, ".string") == 0){
		/* case for .string instruction*/
		error_temp = string_inst(host, line, DC, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	}
	else if(strcmp(segment, ".extern") == 0){
		/* case for .extern instruction*/
		error_temp = extern_inst(host, line, linecnt);
		if(error_temp != NONE) return error_temp;

		error_temp = USELESS_LABEL;
	}
	else if(strcmp(segment, ".entry") == 0){
		/* case for .entry instruction*/
		error_temp = firstphase_entry_inst(host, line, linecnt);
		if(error_temp != NONE) return error_temp;
		
		/* .entry is handled by the 2nd compilation phase, and so the function handling it does not conclude the handling. Yet, a label definition in the current line would be meaningless and the function must notify it is to be partially ignored. */
		error_temp = USELESS_LABEL;
	}
	else{

		/*if a comma is not seperated from the instruction itself by any spaces, it is considered a part of it, and so an illegal comma error will not be emitted here*/
		error_temp = add_error(&(host->errors), ILLEGAL_INSTRUCTION_NAME, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return UNABLE_TO_ALLOCATE_MEMORY;
		else error_temp = ILLEGAL_INSTRUCTION_NAME;
		
	}

	return error_temp;
}