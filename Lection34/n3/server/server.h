#ifndef __SERVER_H_
#define __SERVER_H_

#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <pthread.h>

#include "../general/list.h"
#include "../general/msgq_data.h"
#include "server.h"

extern void * all_messages;
extern sem_t * sem_gr;

int compare(void * data, void * goal);
void registration(int md, struct list * clients, struct msgbuf * message);
void interface(int md, struct msgbuf * message, struct list * clients, int * server_status);
void * for_exit_process(void * md);
void send_to_other(int md, struct list * clients, struct msgbuf * message, pid_t pid);
void get_users(int md, struct list * clients, struct msgbuf * message);
void client_delete(int md, struct list * clients, struct msgbuf * message);
void send_message(int md, struct list * clients, struct msgbuf * message);
void all_clients_exit(int md, struct list * clients, struct msgbuf * message);
void send_old_messages(int md, struct msgbuf * message);

#endif // __SERVER_H_