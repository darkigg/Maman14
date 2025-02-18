#include "../Header Files/read_am.h"

errorType first_passage(FILE *file, tables_host *host){
	
	/* the currently read line */
	char line[MAX_LINE];

	/* the most recently encountered error */
	errorType error_temp = NONE;

	/* counters */
	int DC = 0, IC = 100, line_counter = 0;

	while( fgets(line, MAX_LINE, file) != NULL ){
		error_temp = first_passage_line(line, host, &IC, &DC, ++line_counter);

		/* An error of not enough memory requires as hurried a return to main as possible; it will lead the assembler to break if it continues. */
		if(error_temp = UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	}
	
	return error_temp;

}

errorType first_passage_line(char *line, tables_host *host, int *IC, int *DC, const int line_num){
	char *segment; /*the token of the line currently scanned*/
	int argument_counter; /*counter for arguments in the line, essentially every piece of text seperated by spaces*/
	errorType error_temp = NONE; /*the latest error encountered*/
	boolean is_label_definition; /*whether or not a label is being define in the current line*/
	boolean suspected_label_usage = False; /*whehter or not there is suspicion of a label usage*/
	sentenceType sentype; /*stores the type of the sentence*/

	/* if the sentence is a comment, it may be ignored */
	if(line[0] == ';') return NONE;

	/* scan for the first literal word in the line (the first row of characters enclosed by spaces from both sides) */
	for(segment = strtok(line, ' '); segment; segment = strtok(NULL, ' ')) {
		if( strlen(segment) != 0 || segment == NULL) break;
	}
	if(segment == NULL) return NONE; /*empty sentence*/
	
	/*scan for a potential label definition at the start of the line*/
	error_temp = scan_for_label(segment, host, line_num);
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;

	if(!(error_temp == NO_LABEL)) {
		/* case a label is defined in this line */

		/* scans for the practically first literal word in the line, as the actual first one is a label declaration as was found above */
		for(segment = strtok(line, ' '); segment; segment = strtok(NULL, ' ')) 
			if( strlen(segment) != 0) 
				break;

	}
		
	if(segment[0] == '.') sentype = INSTRUCTION;
	else sentype = OPERATION;

	switch(sentype){
		case INSTRUCTION:
			if(is_label_definition) {
				host->labels.table[(host->labels).length-1].data = True;
				host->labels.table[(host->labels).length-1].value = *DC;
			}
			
			error_temp = handle_instruction_passage1(DC, line, host, line_num);
			if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;

			break;

		case OPERATION:
			if(is_label_definition) {
				host->labels.table[(host->labels).length-1].code = True;
				host->labels.table[(host->labels).length-1].value = *IC;
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

	}
	else if(strcmp(segment, ".extern") == 0){
		/* case for .extern instruction*/

	}
	else if(strcmp(segment, ".entry") == 0){
		/* case for .entry instruction*/

	}
	else{

		/*if a comma is not seperated from the instruction itself by any spaces, it is considered a part of it, and so an illegal comma error will not be emitted here*/
		error_temp = add_error(&(host->errors), ILLEGAL_INSTRUCTION_NAME, linecnt);
		if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return UNABLE_TO_ALLOCATE_MEMORY;
		else error_temp = ILLEGAL_INSTRUCTION_NAME;
		
	}

	return error_temp;
}