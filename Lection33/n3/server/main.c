#include "server.h"
#include "../general/list.h"
#include "../general/msgq_data.h"

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