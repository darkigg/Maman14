/*  ☆   */ /*  ☆   */ /*  ☆   */ /*  ☆   */ /*  ☆   */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "../HeaderFiles/tables.h"
#include "../HeaderFiles/macros.h"
#include "../HeaderFiles/utilities.h"
#include "../HeaderFiles/error_handling.h"

int is_valid_macro(char*, macro_table*, int);
int is_already_mcro(char*, macro_table*, int);
int macro_final(char*, tables_host*);

int main(int argc, char *argv[])
{

	/* file access variable declarations */
	char file_name[MAXFILE];
	int report;


	/* table declarations */
	tables_host tables;


	/* Loop iterating over the arguments list;
	argc is decremented as it is used to iterate over all arguments from the last to the first,
	and as the first argument is the name of the ran file. */
	while((--argc) > 0 && argc != 0)
	{
		/* table initiations */
		initiate_tables_host(&tables);

		/* open macros */
		strcpy(file_name, argv[argc]);
		report = macro_final(file_name, &(tables));
		if(report == -1)
		{
			printf("the program can't advance without a valid preassembler run.\nNow going over the next file...\n");
			continue;
		}
		else if(report>0)
		{
			printf("There where %d errors during the preassembler.\nThus, it cant proceed. Now moving onto the next file...\n", report);
			continue;
		}
		else /* report == 0 */
			printf("There were no errors during the preassembler.\n");
	}
	return 1;
}

int macro_final(char *filename, tables_host *table)
/* This function gets a file and checks for macro definitions inside this file.
the macro definition starts with "mcro" and a name next to it, and ends with "mcroend".
all the content in between goes into the Macro Table where each content is conected to its name.
if there is an error that break the rule such as:
1- macro name syntax error
2- macro name is a language name
3- another label other then the ones specified for macro def
if one of these errors where found, the error goes into the error table, there it gets handled.
If an error is found, and the function can't proceed (for example, failure of dinamic allocation),
the function returns: -1.
if an error like this doesnt occur, it returns the error count of all the errors occured.

this function uses lines with a length of 81 chars, 
so handling it in the main function would be much easier
(because there you could check if it had passed the line length limit) */

{
	macro_table *mcroTable = &(table -> macros);
	error_table *errorTable = &(table -> errors);
	
	/* Variables for the loop: */
	
	/* for dinamic allocations */
	char *temp;
	 /* For errors lines */
	int lineCount = 0;
	/* for tokenizing */
	char lineOrg[MAXLINE + 1];
	char line[MAXLINE + 1];
	/* first string of the line (First Field): */
	char *firstField;
	/* second string of the line (Second Field): */
	char *secondField;
	/* third string of the line (Third Field): */
	char *thirdField;
	/* count of total macros each time found a new one */
	int countM = 0;
	int macroFlag = 0;
	/* if error in macro definition, skip the lines of this macro */
	int errorFlag = 0;
	/* check for number of fields */
	int t = 0;
	int errorCount = 0;
	int i;
	int tempG = 0;

	/* Step 1: opening each file;
	input file - read
	output file - write */
	
	char *filename_temp_i;
	char *filename_temp_o;
	FILE *input;
	FILE *output;
	
	if (filename == NULL)
	{
		if(add_error(errorTable, UNABLE_TO_OPEN_FILE , 0) == UNABLE_TO_ALLOCATE_MEMORY)
			end_prog(table);
		return -1;
	}
	if (!(filename_temp_i = malloc(strlen(filename) + 4)))
		/* ERROR - Memory allocation failed	☆	 */
		end_prog(table);
	if (!(filename_temp_o = malloc(strlen(filename) + 4)))
	{
		/* ERROR - Memory allocation failed		☆	 */
		free(filename_temp_i);
		end_prog(table);
	}
	sprintf(filename_temp_i, "%s.as", filename);
	sprintf(filename_temp_o, "%s.am", filename);
	
	input = fopen(filename_temp_i, "r");
	output = fopen(filename_temp_o, "w");
	
	free(filename_temp_i);
	free(filename_temp_o);
	
	if(!input)
	{
		/* ERROR - Error opening files		☆	 */
		if(add_error(errorTable, UNABLE_TO_OPEN_FILE , 0) == UNABLE_TO_ALLOCATE_MEMORY)
			end_prog(table);
		return -1;
	}
	if(!output)
	{
		fclose(input);
		/* ERROR - Error opening files		☆	 */
		if(add_error(errorTable, UNABLE_TO_OPEN_FILE , 0) == UNABLE_TO_ALLOCATE_MEMORY)
			end_prog(table);
		return -1;
	}
	
	/* allocate memory for the macro table */
	mcroTable = (macro_table*) malloc(sizeof(macro_table)*2);
	if(mcroTable == NULL)
		end_prog(table);
	
	
	
	/* check if reached EOF */
	while(True) /* FOREVER loop */
	{ 
		
		printf("***%d***\n", lineCount);
		/* Line Management: */
		
		/* if came along an EOF, break */
		if((firstField = strtok(lineOrg, WHITESPACES)) != NULL)
		{
			t = 1;
			if(strstr(firstField, "\n"))
			{	
				/* removing \n from substrings */
				firstField[strlen(firstField)-1] = '\0';
			}		
			if((secondField = strtok(NULL, WHITESPACES)) != NULL)
			{
				t = 2;
				if(strstr(secondField, "\n"))
				{	
					/* removing \n from substrings */
					secondField[strlen(secondField)-1] = '\0';
				}	
			}
				if((thirdField = strtok(NULL, WHITESPACES)) != NULL)
				{
					t = 3;
					if(strstr(thirdField, "\n"))
					{	
						/* removing \n from substrings */
						thirdField[strlen(thirdField)-1] = '\0';
					}	
				}
		}
		/* it is a whitespace line -
		next line (continue over the loop) */
		else
			continue;
		
		
		
		/* Step 2: if flag is on, copy the line into the table */
		
		
		/* MACRO FLAG IS ON */
		if(macroFlag)
		{
			if (strcmp(firstField, "mcroend") == 0)
			{
				if (t==1)
				{
					errorFlag = 0;
					macroFlag = 0;
					countM += 1;
					/* EXPAND TABLE 	☆	*/
					mcroTable = (macro_table*) realloc(mcroTable,(countM)*sizeof(macro_table));
					if(mcroTable == NULL)
						/* ERROR - dinamic allocation failed	☆	 */
						end_prog(table);
					free(temp);
					/* next line */
					continue;
				}
				else
				{
					/* ERROR - another label rather than that	☆	 */
					if(add_error(errorTable, ILLEGAL_MACRO_DEFINITION , lineCount) == UNABLE_TO_ALLOCATE_MEMORY)
						end_prog(table);
					errorCount++;
					free(mcroTable->table[countM].content);
					free(temp);
					mcroTable->table[countM].content = NULL;
					macroFlag = 0;
					errorFlag = 0;
					continue;
				}
			}
			/* copy the line into the table section */
			temp = (char*) realloc((mcroTable->table[countM]).content, (strlen((mcroTable->table[countM]).content) +1 + strlen(line)) * sizeof(char));
			if (temp == NULL)
				/* ERROR - dinamic allocation failed	☆	 */
				end_prog(table);
			mcroTable->table[countM].content = temp;
			strcat(mcroTable->table[countM].content, line);
			continue;
		}
		
		/* ERROR FLAG IS ON */
		if (errorFlag)
		{
			if (strcmp(firstField, "mcroend") == 0)
			{
				if (t==1)
				{
					macroFlag = 0;
					errorFlag = 0;
					
					/* next line */
					continue;
				}
				else
				{
					/* ERROR - another label rather than that	☆	 */
					if(add_error(errorTable, ILLEGAL_MACRO_DEFINITION , lineCount) == UNABLE_TO_ALLOCATE_MEMORY)
						end_prog(table);
					errorCount++;
					macroFlag = 0;
					errorFlag = 0;
					continue;
				}
			}
			/* skip line */
			continue;
		}

		


		/* Step 3:
		locate "mcro".
		check errors (if found - Error Flag ON),
		and turn flag on. */

		/* if found string "mcro", turn flag on */
		if(strcmp(firstField, "mcro") == 0)
		{
			if (t != 2)
			{
				/* ERROR - another label rather than that	☆	*/
				if(add_error(errorTable, ILLEGAL_MACRO_DEFINITION , lineCount) == UNABLE_TO_ALLOCATE_MEMORY)
					end_prog(table);
				errorCount++;
				errorFlag = 1;
				continue;
			}
			strcpy(mcroTable->table[countM].name, secondField);
			if(!is_valid_macro(secondField, &(table -> macros), countM))
			{
				/* ERROR - invalid macro name	☆	*/
				if(add_error(errorTable, INVALID_MACRO_NAME , lineCount) == UNABLE_TO_ALLOCATE_MEMORY)
					end_prog(table);
				errorCount++;
				errorFlag = 1;
				continue;
			}
			strncpy(mcroTable->table[countM].name, secondField, sizeof(mcroTable->table[countM].name));
			/* just for \0 character */
			temp = (char*) calloc(MAXLINE, sizeof(char));
			if (temp == NULL)
			{
				/* ERROR - dinamic allocation failed	☆	 */
				end_prog(table);
			}
			mcroTable->table[countM].content = temp;
			macroFlag = 1;
			continue;
		}
		
		
		
		/* Step 4: check if the first field is in the Macro Table - and replace it */

		/* writen in FORUM = 
		if a macro name is mentioned,
		assume there are no other chars in the line.
		(no need for another check) */
		for (i = 0; i < countM; i++)
		{
			/* if found succesfully, print and move onto the next line */
			if(strcmp(firstField, mcroTable->table[i].name) == 0)
			{
				fprintf(output, "%s", mcroTable->table[i].content);
				tempG = 1;
			}
		}
		if (tempG)
		{
			tempG = 0;
			continue;
		}

		/* Step 5: None of the steps occured =
		regular line (print it into the file):
		no need for error checking in pre-asembler */
		
		fprintf(output, "%s", line);
	}
	
	if (macroFlag)
	{
		countM += 1;
	}
	fclose(input);
	fclose(output);
	return errorCount;
}
	
int is_already_mcro(char *str, macro_table *mcroTable, int countM)
/* this function checks if the mentioned string is a macro
(in the table - by its name):
if it is - it returns its index in the Macro Table.
if it isnt - it returns -1 */
{
	int i;
	/* if no macros have been recognized so far */
	if (countM == 0)
		return -1;
	for (i = 0; i < countM; i++)
	{
		if (strcmp(str, mcroTable->table[i].name) == 0)
			return i;
	}
	return -1;
}

int is_valid_macro(char *str, macro_table *mcroTable, int countM)
/* check for macro name's errors:
 1 - syntax errors
 2 - a language word
if there are any errors, it returns 0.
if there are not errors, it returns 1. */
{
	int i;
	if(!((str[0]>='a' && str[0]<='z') || (str[0]>='A' && str[0]<='Z') || str[0]=='_'))
		return 0;

	for(i=1; i < strlen(str); i++)
	{
		if(!((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z') || str[i]=='_' || str[i]>='0' || str[i] <='9'))
			return 0;
	}
	return !(is_already_mcro(str, mcroTable, countM) && is_language_word(str)) && (strlen(str) <= MAX_MACRO);
}
