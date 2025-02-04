/*  ☆   */ /*  ☆   */ /*  ☆   */ /*  ☆   */ /*  ☆   */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE 81 /* including \n and \0 - That is the whole length */
typedef struct {
	char *name;
	char *content;
	} Macro;
Macro mcroTable[];
char *macro_final(char *fileName)
{

	/* Step 1: opening each file
	input - read only, output - write only */
	
	char *filename_temp_i;
	strcpy(filename_temp_i, filename);
	/* adding the ending to input file */
	strcat(filename_temp_i, ".as"); 
	FILE *input = fopen(filename_temp_i, "r");
	char *filename_temp_o;
	strcpy(filename_temp_o, filename);
	/* adding the ending to output file */
	strcat(filename_temp_o, ".am");
	FILE *output = fopen(filename_temp_o, "w");
	fseek(input, 0, SEEK_SET);
	fseek(output, 0, SEEK_SET);
	
	
	char line[MAX_LINE];
	char c;
	int macroFlag = 0;
	/* check if reached EOF */
	while(1) /* FOREVER loop */
	{
		/* Line Management: */
		
		c = fgetc(input);
		if (c == EOF)
			return (output);
		/* moving back 1 char after fgetc */
		fseek(input, -1, SEEK_CUR); 
		fgets(line, sizeof(line), input);
		/* first string of the line (First Field): */
		char firstField[MAX_LINE] = "";
		/* if whitespace line - next line (continue over the loop) */
		if (!sscanf(line, "%s", firstField))
			continue; 
		
		
		/* Step 2: check if found a name that is in the Macro Table - and replace it */
		
		/* writen in FORUM = 
		if there macro is mentioned, there are no other chars in the line
		so using sscanf is useful */
		int indexMcroTable;
		indexMcroTable = is_already_mcro(firstField);
		if(indexMcroTable != -1)
			fprintf(output, mcroTable[indexMcroTable]);
			/* if found succesfully, move onto the next line */
			continue;
		
		
		/* Step 3: locate "mcro" and manage it into the Macro Table 
		using a flag to copy the string */
		
		/* if found string "mcro", turn flag on */
		if(strcmp(firstField, "mcro") == 0)
			macroFlag = 1;
		while (flag)
			/* copy the line to a string (☆ create function) */
			 
			
			
			
			
		/* none of the steps occured = regular line (print it into the file) */
		
		/* no need for error checking now */
		fprintf(output, line);
	}	
		
}

int is_already_mcro(char *str)
/* this function checks if the mentioned string is a macro (in the table):
if it is - it returns its index in the Macro Table.
if it isnt - it returns -1 */
{
	
}
