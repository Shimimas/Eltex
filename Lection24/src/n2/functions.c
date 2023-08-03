#include "functions.h"

void print_pids() {
    printf("PID = %d\tPPID = %d\n", getpid(), getppid());
}