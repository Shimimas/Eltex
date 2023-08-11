#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int fd1[2], fd2[2];
    int status;
    pipe(fd1);
    pipe(fd2);
    if (!fork()) {
        close(fd1[0]);
        close(fd2[1]);
        char message[3] = "Hi!";
        char getting_message[255];
        write(fd1[1], message, 3);
        read(fd2[0], getting_message, 255);
        printf("Child get: %s\n", getting_message);
        exit(EXIT_SUCCESS);
    } else {
        close(fd1[1]);
        close(fd2[0]);
        char message[6] = "Hello!";
        char getting_message[255];
        write(fd2[1], message, 6);
        read(fd1[0], getting_message, 255);
        printf("Parent get: %s\n", getting_message);
        wait(&status);
    }
    return 0;
}