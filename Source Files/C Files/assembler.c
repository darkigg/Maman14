/* section for all of the #include */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header Files/tables.h"
#include "../Header Files/utilities.h"
#include "../Header Files/read_am.h"

/*this file includes the main function.*/

/*the program's main function*/
int main(int argc, char *argv[]){

	/*ADD ERROR FOR ATTEMPT AT OPENING AN ILLEGAL FILE*/

	/* Loop iterating over the arguments list; argc is decremented as it is used to iterate over all arguments from the last to the first, and as the first argument is the name of the ran file. */
	while( (--argc) > 0 && argc != 0){

		/* file access variable declarations */
		char *file_name;
		FILE *assembly_file;

		errorType recentErr;

		/* table declarations */
		tables_host tables;

		/* table initiations */
		initiate_tables_host(&tables);

		/* open macros */

		/*add .as to the file name string*/
		file_name = strcat(argv[argc], ".as");

		/*open the requested file*/
		assembly_file = fopen(file_name, "r");

		/*rid of all macros*/
		recentErr = 0 /*temporary*/;

		/* if no error was encountered, access the newly created .am file */
		file_name[strlen(file_name)-1] = 'm';
		assembly_file = fopen(file_name, "r");

		/* translate the .am file to machine code */
		if(recentErr == NONE) recentErr = translate_file(assembly_file, &tables);

		/*print errors if there were any*/
		if(recentErr != UNABLE_TO_ALLOCATE_MEMORY){

		}
		else /*if the assembler was unable to allocate enough memory, the error table is irrelevant*/;

		/* unload of tables from the heap */
		free_tables_host(&tables);

	}

	return 0;

}