#include "../HeaderFiles/read_am.h"
/*this file includes definitions for central and fundumental operations performed during the interpertation process of the .am file*/

errorType translate_file(FILE *file, tables_host *host, int *ICF, int *DCF){
	/* DECLARATIONS */
	char line[MAXLINE]; /*stores the current line*/
	int line_counter = 0; /*counter of lines read so far*/
	errorType error_temp; /*a variable naming convention throughout the .am file analysis, for variables containing the most recent error*/

	/*counters*/
	int IC = 0, DC = 0;

	/* STAGE 1 */
	error_temp = first_passage(file, host, ICF, DCF);
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host); /* the most urgent error, with it there is both a practical and a theoretical impossibility of the compilitation process proceeding */

	/* STAGE 2 */
	error_temp = second_passage(host);
	if(error_temp == UNABLE_TO_ALLOCATE_MEMORY) end_prog(host);

	(*ICF) -= 100; /*as the ICF equals the instruction counter minus 100*/

	return error_temp;
}

