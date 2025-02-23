#include "../Header Files/read_am.h"
/* this file includes the definitions of the functions processing code sentences in the assembly code into binary words */

errorType read_code_line(tables_host *host, char *line, int *IC, const int linecnt, boolean interpret_labels){
	errorType error_temp;
	char *token;

	for(token = strtok(line, ' '); token; token = strtok(NULL, ' ') ){
		if( token[strlen(token)-1] != ':' && !(IS_WHITESPACE(token[0])) )
			break; /*if the token does not comprise of whitespaces and does not end with a colon (a label definition), it is the operation.*/
	}

	/*YOU HAVE THE F*CKING OPERATION TEXT. NOW DO SOMETHING WITH IT.*/

}