#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE 81 /* including \n and \0 - That is the whole length */
typedef struct {
	char *name;
	char *content;
	} Macro;
