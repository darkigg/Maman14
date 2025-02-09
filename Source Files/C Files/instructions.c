#include "../Header Files/instructions.h"

errorType data_inst(tables_host *host, char *line, int *DC, const int linecnt){
	char *segment; /*the currently iterated over token*/
	errorType error_temp;
	boolean is_prev_data = False, is_prev_comma = False;	
	
	/* rids line of potential label declarations and the instruction call itself */
	line = get_arg_list(line);

	if(line[0] == ',') error_temp = add_error(&(host->errors), ILLEGAL_COMMA, linecnt); /*there's a comma at the beginning of the argument list, meaning there's a comma immediately following the instruction*/
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) return error_temp;
	else error_temp = ILLEGAL_COMMA;

	/* split it up by commas and scan */
	if(error_temp == NONE) for(segment  = strtok(line, ','); segment; segment = strtok(NULL, ',')){
		
	}

	return error_temp;
}