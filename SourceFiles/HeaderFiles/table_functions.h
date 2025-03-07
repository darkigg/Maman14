/*This header contains prototypes for all functions related to table handling*/

#ifndef TABLE_FUNCTIONS
#define TABLE_FUNCTIONS

#include <stdlib.h>

#include "tables.h"

/**
 * Initiates all tables in the host.
 * @param host the host.
 */
void initiate_tables_host(tables_host *host);

/**
 * Frees all tables in the host.
 * @param host the host.
 */
void free_tables_host(tables_host *host);

#endif