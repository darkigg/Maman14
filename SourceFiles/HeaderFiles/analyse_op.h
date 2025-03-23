/*This file contains functions for analysing code operations*/

#ifndef ANALYSE_OP
#define ANALYSE_OP

#include "string.h"

#include "constants.h"
#include "tables.h"
#include "utilities.h"

/**
 * This function, given a potentially viable operation, detects the function (if it is valid).
 * @param op_text text containing the operation; for proper functionality, mustn't include extraneous text.
 * @return the operation detected, by number (according to the values in operationType).
 */
operationType detect_op(char *op_text);

/**
 * @param type the operation type
 * @return the amount of arguments the operation matching the type provided expects.
 */
int op_arg_count(operationType type);

/**
 * This function, given an operation's opcode and the address method of which an attempted usage is made, will check whether or not the operation can accept that address method. 
 * The function expects valid values and error handling is not performed within it.
 * @param opcode the operation's opcode.
 * @param address_method the attempted addressing method.
 * @param arg_type the "index" of the argument among all the arguments the function receives.
 * @return whether or not the address method is acceptable for the operation.
 */
boolean is_address_method_valid(int opcode, int address_method, int arg_type);

/**
 * Given an operation type, the function returns the corresponding opcode matching the operation type.
 * @param op the operation type.
 * @return the opcode.
 */
int get_opcode(operationType op);

#endif