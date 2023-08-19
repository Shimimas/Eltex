#include "client.h"
#include "../general/list.h"
#include "../general/msgq_data.h"

int main(void) {
    __key_t key;
    struct msgbuf message;
    int md;
    pid_t pid;

    pid = getpid();
    key = ftok("../server/main", 5);
    printf("key = %d\n", key);
    md = msgget(key, 0);
    printf("Enter your name\n");
    scanf("%s", message.data.mtext);
    printf("END SCAN\n");

    message.mtype = SERVER_INFORMATION;
    message.data.type = REGISTATION;
    printf("pid = %d\n", pid);
    message.data.pid = pid;

    msgsnd(md, (void *) &message, sizeof(struct data), 0);
    printf("CLIENT SEND\n");
    while(1) {
        printf("WAIT MESSAGE %d PID\n", pid);
        msgrcv(md, (void *) &message, sizeof(struct data), pid, 0);
        printf("CLIENT GET\n");
        switch (message.data.type) {
            case REGISTATION:
                printf("add user %s\n", message.data.mtext);
                break;
            case DELETE:
                break;
            default:
                break;
        } 
    }
    return 0;
}