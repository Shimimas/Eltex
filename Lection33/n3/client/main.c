#include "client.h"
#include "../general/list.h"
#include "../general/msgq_data.h"

WINDOW * windows[WINDOWS_AMOUNT];
char nickname[NICKNAME_SIZE];

int main(void) {
    __key_t key;
    struct msgbuf message;
    int md;
    pid_t pid;

    init_start_screen();

    pid = getpid();
    key = ftok("../server/main", 5);
    md = msgget(key, 0);
    //printf("Enter your name\n");
    //scanf("%s", message.data.mtext);

    /*message.mtype = SERVER_INFORMATION;
    message.data.type = REGISTATION;
    message.data.pid = pid;

    msgsnd(md, (void *) &message, sizeof(struct data), 0);
    while(1) {
        msgrcv(md, (void *) &message, sizeof(struct data), pid, 0);
        switch (message.data.type) {
            case REGISTATION:
                break;
            case GET_ALL_ACTIVE_USERS:
                printf("was user %s\n", message.data.mtext);
                break;
            case DELETE:
                break;
            case ADD_NEW_USER:
                printf("add user %s\n", message.data.mtext);
                break;
            default:
                break;
        } 
    }
    return 0;*/
}