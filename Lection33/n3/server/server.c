#include "../general/list.h"
#include "../general/msgq_data.h"
#include "server.h"

int compare(void * data, void * goal) {
    struct msgbuf * message;
    struct user * user;

    message = (struct msgbuf *) goal;
    user = (struct user *) data;
    if (message->data.pid == user->pid) {
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
    struct list_element * head;

    message->data.type = ADD_NEW_USER;
    message->data.pid = pid;
    head = clients->head;
    while(head != NULL) {
        if (pid != ((struct user *)(head->data))->pid) {
            message->mtype = ((struct user *)(head->data))->pid;
            printf("SEND %s\n", message->data.mtext);
            msgsnd(md, (void *) message, sizeof(struct data), 0);
        }
        head = head->next;
    }
}

void get_users(int md, struct list * clients, struct msgbuf * message) {
    message->mtype = message->data.pid;
    struct list_element * head = clients->head;
    message->data.type = ADD_NEW_USER;
    while(head != NULL) {
        strcpy(message->data.mtext, ((struct user *)(head->data))->name);
        message->data.pid = ((struct user *)(head->data))->pid;
        printf("SEND %s\n", message->data.mtext);
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
        case MESSAGE:
            break;
        case CLIENT_DELETE:
            client_delete(md, clients, message);
            break;
        default:
            break;
    }
}

void client_delete(int md, struct list * clients, struct msgbuf * message) {
    struct list_element * head;

    remove_list_element(clients, find(clients, (void *) message, compare));
    printf("END_RM\n");
    message->data.type = CLIENT_DELETE;
    head = clients->head;
    while(head != NULL) {
        message->mtype = ((struct user *)(head->data))->pid;
        printf("DELETE PID %d\n", message->data.pid);
        msgsnd(md, (void *) message, sizeof(struct data), 0);
        head = head->next;
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