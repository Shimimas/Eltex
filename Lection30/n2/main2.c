#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void) {
    mkfifo("pipe2", 0666);
    int fd_fifo = open("pipe1", O_RDONLY);
    char answer[256];
    read(fd_fifo, answer, 256);
    printf("main2 get %s\n", answer);
    char message[3] = "Hi!";
    int fd_fifo1 = open("pipe2", O_WRONLY);
    write(fd_fifo1, message, 3);
    close(fd_fifo1);
    close(fd_fifo);
    return 0;
}