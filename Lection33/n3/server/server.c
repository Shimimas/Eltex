#include "../general/list.h"
#include "../general/msgq_data.h"
#include "server.h"

int compare(void * data, void * goal) {
    int * data_int = (int *) data;
    int * goal_int = (int *) goal;
    if (*data_int == *goal_int) {
        return 1;
    }
    return 0;
}

void registration(int md, struct list * clients, struct msgbuf * message) {
    struct user user;

    user.pid = message->data.pid;
    strcpy(user.name, message->data.mtext);
    push_back(clients, (void *) &user, sizeof(struct user));

    get_users(md, clients, message);
    send_to_other(md, clients, message, user.pid);
}

void send_to_other(int md, struct list * clients, struct msgbuf * message, pid_t pid) {
    message->data.type = ADD_NEW_USER;
    struct list_element * head = clients->head;
    while(head != NULL) {
        if (pid != ((struct user *)(head->data))->pid) {
            message->mtype = ((struct user *)(head->data))->pid;
            msgsnd(md, (void *) message, sizeof(struct data), 0);
        }
        head = head->next;
    }
}

void get_users(int md, struct list * clients, struct msgbuf * message) {
    message->mtype = message->data.pid;
    struct list_element * head = clients->head;
    message->data.type = GET_ALL_ACTIVE_USERS;
    while(head != NULL) {
        strcpy(message->data.mtext, ((struct user *)(head->data))->name);
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