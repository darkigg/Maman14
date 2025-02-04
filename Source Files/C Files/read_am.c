#include <stdio.h>
#include <stdlib.h>

#include "../Header Files/read_am.h"
#include "../Header Files/labels.h"
#include "../Header Files/utilities.h"

#define MAXLINE 80

void translate_file(FILE *file, assembler_error_table *errors){
	/* DECLARATIONS */
	char line[MAXLINE]; /*stores the current line*/
	label_table labels; /*table of labels*/
	int line_counter = 0; /*counter of lines read so far*/
	assembler_error_table errors; /*table of errors*/

	/*counters*/
	int IC = 0, DC = 0;
	
	/*instantiate in the heap memory*/
	labels = malloc(0);
	errors = malloc(0);

	/* STAGE 1 */
	while (fgets(line, MAXLINE, file) != NULL) {
		boolean was_label_encountered; /*stores whether or not a label was encountered*/

		was_label_encountered = scan_for_label( line, labels, errors );

		if(was_label_encountered){

		}

		line_counter++;
	}

	/* STAGE 2 */

	/*free all out of use objects from the heap*/
	free(labels);
	free(errors)

}