#include "functions.h"

void interface() {
    char commands[256];
    char * pars_commands[10];
    char path[] = "/bin/";
    int status;
    while(1) {
        printf("Enter command (max - 9 words):\n");
        fgets(commands, 256, stdin);
        char * lexems = strtok(commands, " \n");
        int idx = 0;
        while (lexems != NULL) {
            pars_commands[idx++] = lexems;
            lexems = strtok(NULL, " \n");
        }
        pars_commands[idx] = NULL;
        char * name = strcat(path, pars_commands[0]);
        pid_t child_pid = fork();
        if (child_pid == 0) {
            execv(name, pars_commands);
        } else {
            wait(&status);
        }
    }
}