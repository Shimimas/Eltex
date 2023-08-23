#ifndef __SERVER_H_
#define __SERVER_H_

#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <pthread.h>

#include "../general/list.h"
#include "../general/msgq_data.h"
#include "server.h"

int compare(void * data, void * goal);
void registration(int md, struct list * clients, struct msgbuf * message);
void interface(int md, struct msgbuf * message, struct list * clients, int * server_status);
void * for_exit_process(void * md);
void send_to_other(int md, struct list * clients, struct msgbuf * message, pid_t pid);
void get_users(int md, struct list * clients, struct msgbuf * message);
void client_delete(int md, struct list * clients, struct msgbuf * message);

#endif // __SERVER_H_