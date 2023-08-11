#include "functions.h"

int main(void) {
    int fd[MAX_COMMANDS_AMOUNT][2];
    int status;
    char commands[BUFFER_SIZE];
    char * pars_commands_1[MAX_COMMANDS_AMOUNT];
    char * pars_commands_2[MAX_COMMANDS_AMOUNT];
    int comands_amount = 0;
    int comands_amount_for_copy = 0;

    while (1) {
        printf("Enter commands\n");
        fgets(commands, BUFFER_SIZE, stdin);
        parser(pars_commands_1, commands, &comands_amount, "|\n");
        comands_amount_for_copy = comands_amount;
        for (int i = 0; i < comands_amount_for_copy; i++) {
            parser(pars_commands_2, pars_commands_1[i], &comands_amount, " \n");
            if (i != comands_amount_for_copy - 1) {
                pipe(fd[i]);
            }
            execute(fd, i, pars_commands_2, &status, comands_amount_for_copy);
        }
    }
    return 0;
}