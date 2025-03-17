#include "../Header Files/tables.h"
#include "macros.h"
#include "utilities.h"
#include "errorHandling.h"

#define WHITESPACES " \t" 

int is_already_mcro(char *str, macro_table mcroTable, int countM);

int *macro_final(char *filename, macro_table mcroTable)
{
    /* Step 1: opening each file */
    char filename_temp_i[MAX_LINE];
    char filename_temp_o[MAX_LINE];
    FILE *input, *output;
    
    /* preparing input filename */
    strcpy(filename_temp_i, filename);
    strcat(filename_temp_i, ".as"); 
    input = fopen(filename_temp_i, "r");
    if (input == NULL) {
        printf("Error opening input file: %s\n", filename_temp_i);
        return 0;
    }

    /* preparing output filename */
    strcpy(filename_temp_o, filename);
    strcat(filename_temp_o, ".am");
    output = fopen(filename_temp_o, "w");
    if (output == NULL) {
        printf("Error opening output file: %s\n", filename_temp_o);
        fclose(input);
        return 0;
    }

    char line[MAX_LINE + 1];
    char firstField[MAX_LINE] = "";
    char secondField[MAX_LINE] = "";
    char thirdField[MAX_LINE] = "";
    int countM = 0;
    int macroFlag = 0;
    int t = 0;
    int indexMcroTable;

    /* Step 2: Reading lines from input */
    while (fgets(line, sizeof(line), input))
    {
        /* if whitespace line - continue */
        if (isWhiteSpace(line))
            continue; 

        /* Tokenizing line */
        char *token = strtok(line, WHITESPACES);
        if (token) {
            strcpy(firstField, token);
            t = 1;
            token = strtok(NULL, WHITESPACES);
            if (token) {
                strcpy(secondField, token);
                t = 2;
                token = strtok(NULL, WHITESPACES);
                if (token) {
                    strcpy(thirdField, token);
                    t = 3;
                }
            }
        } else {
            continue;
        }

        /* Step 3: Copying lines to macro table if macroFlag is on */
        if (macroFlag) {
            if (strcmp(firstField, "mcroend") == 0) {
                if (t == 1) {
                    macroFlag = 0;
                    countM++;
                    continue;
                } else {
                    printf("Error: invalid syntax after mcroend\n");
                    fclose(input);
                    fclose(output);
                    return 0;
                }
            } else {
                /* Copy line into the macro table */
                strcat(mcroTable[countM].content, line);
                continue;
            }
        }

        /* Step 4: Start of new macro */
        if (strcmp(firstField, "mcro") == 0) {
            if (t != 2) {
                printf("Error: invalid macro definition\n");
                fclose(input);
                fclose(output);
                return 0;
            }
            /* Check for macro name errors */
            strcpy(mcroTable[countM].name, secondField);
            macroFlag = 1;
            continue;
        }

        /* Step 5: Check for macro name usage */
        indexMcroTable = is_already_mcro(firstField, mcroTable, countM);
        if (indexMcroTable != -1) {
            fprintf(output, "%s", mcroTable[indexMcroTable].content);
            continue;
        }

        /* Step 6: Regular line */
        fprintf(output, "%s", line);
    }

    fclose(input);
    fclose(output);
    return 1;
}

int is_already_mcro(char *str, macro_table mcroTable, int countM)
{
    int i;
    for (i = 0; i < countM; i++) {
        if (strcmp(str, mcroTable[i].name) == 0)
            return i;
    }
    return -1;
}

int isWhiteSpace(char *line)
{
    int i;
    for (i = 0; line[i] != '\0'; i++) {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return 0;
    }
    return 1;
}
