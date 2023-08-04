#include "functions.h"

int main(void) {
    __pid_t child_pid;
    int status;
    child_pid = fork();
    if (child_pid == 0) {
        child_pid = fork();
        if (child_pid == 0) {
            print_pids();
            exit(EXIT_SUCCESS);
        } else {
            child_pid = fork();
            if (child_pid == 0) {
                print_pids();
                exit(EXIT_SUCCESS);
            } else {
                print_pids();
                wait(&status);
                wait(&status);
            }
        }
    } else {
        child_pid = fork();
        if (child_pid == 0) {
            child_pid = fork();
            if (child_pid == 0) {
                print_pids();
                exit(EXIT_SUCCESS);
            } else {
                print_pids();
                wait(&status);
            }
        } else {
            print_pids();
            wait(&status);
            wait(&status);
        }
    }
    return 0;
}