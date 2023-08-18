#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

#define BUFFER_SIZE 10

struct msgbuf {
    long    mtype;
    char    mtext[BUFFER_SIZE];
};

int main(void) {
    __key_t key = ftok("server", 5);
    struct msgbuf message;
    int md = msgget(key, 0);
    msgrcv(md, (void *) &message, BUFFER_SIZE, 4, 0);
    printf("CLIENT: GET %s FROM SERVER\n", message.mtext);
    strcpy(message.mtext, "Hi!");
    message.mtype = 5;
    printf("CLIENT: SEND %s TO SERVER\n", message.mtext);
    msgsnd(md, (void *) &message, BUFFER_SIZE, 0);
    return 0;
}