#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void) {
    char message[6] = "Hello!";
    mkfifo("pipe1", 0666);
    int fd_fifo = open("pipe1", O_WRONLY);
    write(fd_fifo, message, 6);
    int fd_fifo1 = open("pipe2", O_RDONLY);
    char answer[256];
    read(fd_fifo1, answer, 256);
    printf("main1 get %s\n", answer);
    close(fd_fifo1);
    close(fd_fifo);
    return 0;
}