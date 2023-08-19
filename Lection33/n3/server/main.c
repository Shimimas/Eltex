#include "server.h"
#include "../general/list.h"
#include "../general/msgq_data.h"

void registration(int md, struct list * clients, struct msgbuf * message) {
    push_back(clients, (void *) &message->data.pid, sizeof(message->data.pid));
    struct list_element * head = clients->head;
    while(head != NULL) {
        message->mtype = *((int *)(head->data));
        message->data.type = REGISTATION;
        msgsnd(md, (void *) message, sizeof(struct data), 0);
        head = head->next;
    }
}

void interface(int md, struct msgbuf * message, struct list * clients, int * server_status) {
    switch (message->data.type) {
        case REGISTATION:
            registration(md, clients, message);
            break;
        case DELETE:
            break;
        case EXIT:
            *server_status = 0;
            break;
        default:
            break;
    }
}

void * for_exit_process(void * md) {
    int md_int = *((int *) md);
    char input;
    struct msgbuf message;

    do {
        fscanf(stdin, "%c", &input);
    } while (input != 'q');
    
    message.mtype = SERVER_INFORMATION;
    message.data.type = EXIT;
    msgsnd(md_int, (void *) &message, sizeof(struct data), 0);
}

int main(void) {
    __key_t key;
    struct msgbuf message;
    struct list clients;
    int md;
    int server_status = 1;

    pthread_t thread;
    int * s;

    key = ftok("main", 5);
    md = msgget(key, IPC_CREAT | 0600);
    
    pthread_create(&thread, NULL, for_exit_process, (void *) &md);

    while(server_status) {
        msgrcv(md, (void *) &message, sizeof(struct data), SERVER_INFORMATION, 0);
        interface(md, &message, &clients, &server_status);
    }

    pthread_join(thread, (void **) &s);

    clear(&clients);
    msgctl(md, IPC_RMID, NULL);
    return 0;
}