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
    message.mtype = 4;
    strcpy(message.mtext, "Hello!");
    int md = msgget(key, IPC_CREAT | 0600);
    printf("SERVER: SEND %s TO CLIENT\n", message.mtext);
    msgsnd(md, (void *) &message, BUFFER_SIZE, 0);
    msgrcv(md, (void *) &message, BUFFER_SIZE, 5, 0);
    printf("SERVER: GET %s FROM CLIENT\n", message.mtext);
    msgctl(md, IPC_RMID, NULL);
    return 0;
}