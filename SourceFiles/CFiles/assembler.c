/* section for all of the #include */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../HeaderFiles/constants.h"
#include "../HeaderFiles/tables.h"
#include "../HeaderFiles/table_functions.h"
#include "../HeaderFiles/read_am.h"
#include "../HeaderFiles/error_handling.h"
#include "../HeaderFiles/output_files_creation.h"

/*this file includes the main function.*/

/*the program's main function*/
int main(int argc, char *argv[]){

	/* file access variable declarations */
	char file_name[MAXFILE];
	FILE *assembly_file;

	errorType error_temp;

	/* table declarations */
	tables_host tables;

	int ICF, DCF;

	/* Loop iterating over the arguments list; argc is decremented as it is used to iterate over all arguments from the last to the first, and as the first argument is the name of the ran file. */
	while( (--argc) > 0 && argc != 0){
		
		/* table initiations */
		initiate_tables_host(&tables);

		/* open macros */

		/*add .as to the file name string*/
		strcpy(file_name, argv[argc]);
		strcat(file_name, ".as");

		/*open the requested .as file*/
		assembly_file = fopen(file_name, "r");
		
		if(assembly_file == NULL){ /*if the file cannot be opened, report to the user and...*/
			fprintf(stderr, "File %s cannot be opened.\n", file_name);			
			continue; /*...to the next file*/
		}
		
		/*rid of all macros*/
		error_temp = NONE;

		/* if no error was encountered, access the newly created .am file */
		fclose(assembly_file);
		file_name[strlen(file_name)-1] = 'm';
		assembly_file = fopen(file_name, "r");

		/* translate the .am file to machine code */
		if(error_temp == NONE) error_temp = translate_file(assembly_file, &tables, &ICF, &DCF);
		
		strcpy(file_name, argv[argc]);

		printf("tables consensus report:\n \tMACROS -> len:%d, validity:%d, first item:%d\n \tLABELS -> len:%d, validity:%d, first item:%d\n \tWORDS -> len:%d, validity:%d, first item:%d\n \tDATA_WORDS -> len:%d, validity:%d, first item:%d\n \tERRORS -> len:%d, validity:%d, first item:%d\n \tLAB_ARGS -> len:%d, validity:%d, first item:%d\n",
		tables.macros.length, tables.macros.valid, 0, tables.labels.length, tables.labels.valid, tables.labels.table->value, tables.words.length, tables.words.valid, tables.words.table->word.value, tables.data_words.length, tables.data_words.valid, tables.data_words.table->address, tables.errors.length, tables.errors.valid, tables.errors.table->error, tables.lab_args.length, tables.lab_args.valid, tables.lab_args.table->line);

		/* create the output files */
		if(!print_err(&(tables.errors), file_name)){ /*print_err will return 0 if no errors were printed, meaning none were encountered, meaning the output files shall be created; therefore they will be.*/
			fprintf(stdout, "\nend\n");
			create_obj_file(tables.words, ICF, DCF, file_name);
		}
		
		printf("any way the wind blows %d\n", tables.errors.length);
		/* unload of tables from the heap */
		free_tables_host(&tables);
		printf("end of file\n");

		fclose(assembly_file);
	}

	return 0;

}