#include "client.h"
#include "../general/list.h"
#include "../general/msgq_data.h"

WINDOW * windows[WINDOWS_AMOUNT];
char nickname[BUFFER_SIZE];
struct list users;

int main(void) {
    __key_t key;
    struct msgbuf message;
    int md;
    pid_t pid;

    init_start_screen();
    strcpy(message.data.mtext, nickname);
    init_main_screen();
    pid = getpid();
    key = ftok("../server/main", 5);
    md = msgget(key, 0);

    message.mtype = SERVER_INFORMATION;
    message.data.type = REGISTATION;
    message.data.pid = pid;

    msgsnd(md, (void *) &message, sizeof(struct data), 0);
    while(1) {
        msgrcv(md, (void *) &message, sizeof(struct data), pid, 0);
        switch (message.data.type) {
            case REGISTATION:
                break;
            case DELETE:
                break;
            case ADD_NEW_USER:
                add_user(message.data.mtext);
                users_content_refresh();
                message.data.type = TO_DEFAULT;
                break;
            default:
                break;
        } 
    }
    return 0;
}