/* section for all of the #include */
#include "stdio.h"
#include "string.h"

/*the program's main function*/
int main(int argc, char *argv[]){

	/* Loop iterating over the arguments list; argc is decremented as it is used to iterate over all arguments from the last to the first, and as the first argument is the name of the ran file. */
	while( (--argc) > 0 && argc != 0){
		char *file_name;
		FILE *assembly_file;

		/*add .as to the file name string*/
		file_name = strcat(argv[argc], ".as");

		/*open the requested file*/
		assembly_file = fopen(file_name, "r");

	}

	return 0;

}