#include "my_exits.h"

int main(void) {
    __pid_t child_pid;
    int status;
    child_pid = fork();
    if (child_pid == 0) {
        int Pwork = atexit(first_exit);
        printf("Child PID = %d\n", getpid());
        exit(EXIT_SUCCESS);
    } else {
        int Pwork = atexit(second_exit);
        printf("Parent PID = %d\n", getpid());
        wait(&status);
    }
    return 0;
}