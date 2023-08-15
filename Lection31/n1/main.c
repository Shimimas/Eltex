#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    open("text.txt", O_CREAT, 0600);
    int fd = open("text.txt", O_WRONLY);
    write(fd, "Hello, World!!!\n", 16);
    close(fd);
    fd = open("text.txt", O_RDONLY);
    char buf[255];
    read(fd, buf, 16);
    close(fd);
    printf("string = %s", buf);
    unlink("text.txt");
    return 0;
}