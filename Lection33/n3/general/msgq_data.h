#ifndef __MSGQ_DATA_H_
#define __MSGQ_DATA_H_

#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

#define NICKNAME_SIZE 20
#define BUFFER_SIZE 255
#define SERVER_INFORMATION 1
#define REGISTATION 0
#define DELETE 1
#define EXIT 2
#define GET_ALL_ACTIVE_USERS 3
#define END_USERS 4
#define ADD_NEW_USER 5

struct data {
    long type;
    long pid;
    char mtext[BUFFER_SIZE];
};

struct msgbuf {
    long mtype;
    struct data data;
};

#endif // __MSGQ_DATA_H_