#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

void loop() {
    int a = 1;
    while (a != 0) {
        a++;
    }
}

int main(void) {
    int status;
    pid_t child_pid = fork();
    if (child_pid == 0) {
        //setpriority(PRIO_PROCESS, getpid(), 19);
        loop();
        loop();
        loop();
        loop();
        loop();
        loop();
        printf("Child PID = %d\n", getpid());
    } else {
        setpriority(PRIO_PROCESS, getpid(), 15);
        loop();
        loop();
        loop();
        loop();
        loop();
        loop();
        printf("Parent PID = %d\n", getpid());
        wait(&status);   
    }
    return 0;
}