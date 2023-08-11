#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

#define BUFFER_SIZE 255
#define ONE_COMAND_SIZE 50
#define MAX_COMMANDS_AMOUNT 10

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

void parser(char * pars_commands_1[MAX_COMMANDS_AMOUNT], char commands[BUFFER_SIZE], int * comands_amount, char expression[]);
void execute(int fd[MAX_COMMANDS_AMOUNT][2], int i, char * pars_commands_2[MAX_COMMANDS_AMOUNT], int * status, int comands_amount_for_copy);

#endif // __FUNCTIONS_H_