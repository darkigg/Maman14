/* section for all of the #include */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Header Files/utilities.h"
#include "../Header Files/read_am.h"


/*the program's main function*/
int main(int argc, char *argv[]){

	/*ADD ERROR FOR ATTEMPT AT OPENING AN ILLEGAL FILE*/

	/* Loop iterating over the arguments list; argc is decremented as it is used to iterate over all arguments from the last to the first, and as the first argument is the name of the ran file. */
	while( (--argc) > 0 && argc != 0){

		/* file access variable declarations */
		char *file_name;
		FILE *assembly_file;

		/* table declarations */
		macro_table macros;

		/* table initiations */
		macros = malloc(0);

		/* open macros */

		/*add .as to the file name string*/
		file_name = strcat(argv[argc], ".as");

		/*open the requested file*/
		assembly_file = fopen(file_name, "r");

		/*rid of all macros*/
		/**********/

		/* if no error was encountered, access the newly created .am file */
		file_name[SIZE_OF_ARR(file_name)-1] = 'm';
		assembly_file = fopen(file_name, "r");

		/* translate the .am file to machine code */

		/* unload of tables from the heap */

	}

	return 0;

}