#include "client.h"
#include "../general/list.h"
#include "../general/msgq_data.h"

WINDOW * windows[WINDOWS_AMOUNT];
char nickname[BUFFER_SIZE];
char write_message[BUFFER_SIZE];
char all_messages[MESSAGE_BUFFER_SIZE];
struct list users;

int main(void) {
    __key_t key;
    struct msgbuf message;
    int md;
    pid_t pid;
    pthread_t thread[2];
    int * s;
    struct pthread_info p_info;

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

    p_info.md = md;
    p_info.pid = pid;

    pthread_create(&thread[WRITE], NULL, write_pthread, (void *) &p_info);
    pthread_create(&thread[READ], NULL, read_pthread, (void *) &p_info);

    pthread_join(thread[WRITE], (void **) &s);
    pthread_join(thread[READ], (void **) &s);

    return 0;
}