#include "functions.h"

void parser(char * pars_commands_1[MAX_COMMANDS_AMOUNT], char commands[BUFFER_SIZE], int * comands_amount, char expression[]) {
    char * lexems = strtok(commands, expression);
    int idx = 0;
    while (lexems != NULL) {
        pars_commands_1[idx++] = lexems;
        lexems = strtok(NULL, expression);
    }
    *comands_amount = idx;
    pars_commands_1[idx] = NULL;
}

void execute(int fd[MAX_COMMANDS_AMOUNT][2], int i, char * pars_commands_2[MAX_COMMANDS_AMOUNT], int * status, int comands_amount_for_copy) {
    char path[BUFFER_SIZE] = "/bin/";
    char * name = strcat(path, pars_commands_2[0]);
    if (!fork()) {
        if (i == 0) {
            dup2(fd[i][1], 1);
            close(fd[i][0]);
            close(fd[i][1]);
        } else if (i == comands_amount_for_copy - 1) {
            dup2(fd[i - 1][0], 0);
            close(fd[i][0]);
        } else {
            dup2(fd[i - 1][0], 0);
            dup2(fd[i][1], 1);
            close(fd[i - 0][0]);
            close(fd[i][1]);
            close(fd[i][0]);
        }
        execv(name, pars_commands_2);
    } else {
        if (i == 0) {
            close(fd[i][1]);
        } else if (i == comands_amount_for_copy - 1) {
            printf("here end\n");
            close(fd[i - 1][0]);
        } else {
            close(fd[i - 1][0]);
            close(fd[i][1]);
        }
        wait(status);
    }
}