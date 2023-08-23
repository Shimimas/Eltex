#ifndef __MSGQ_DATA_H_
#define __MSGQ_DATA_H_

#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

#define BUFFER_SIZE 255
#define MESSAGE_BUFFER_SIZE 1024
#define TO_DEFAULT -1
#define SERVER_INFORMATION 1
#define REGISTATION 0
#define DELETE 1
#define EXIT 2
#define END_USERS 3
#define ADD_NEW_USER 4
#define MESSAGE 5
#define CLIENT_DELETE 6

struct data {
    long type;
    pid_t pid;
    char mtext[BUFFER_SIZE];
};

struct msgbuf {
    long mtype;
    struct data data;
};

struct user {
    pid_t pid;
    char name[20];
};

#endif // __MSGQ_DATA_H_