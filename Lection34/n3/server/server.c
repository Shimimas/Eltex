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
    send_old_messages(md, message);
}

void send_old_messages(int md, struct msgbuf * message) {
    char buf_for_copy[BUFFER_SIZE];
    int i;
    int j;
    int flag;

    message->mtype = message->data.pid;
    message->data.type = MESSAGE;
    j = 0;
    flag = 0;
    while (flag == 0) {
        for (i = 0; i < BUFFER_SIZE - 1; i++, j++) {
            if (((char *)all_messages)[j] == '\0') {
                flag = 1;
                break;
            } else {
                buf_for_copy[i] = ((char *)all_messages)[j];
            }
        }
        buf_for_copy[i] = '\0';
        strcpy(message->data.mtext, buf_for_copy);
        msgsnd(md, (void *) message, sizeof(struct data), 0);
    }
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
            all_clients_exit(md, clients, message);
            *server_status = 0;
            break;
        case MESSAGE:
            send_message(md, clients, message);
            break;
        case CLIENT_DELETE:
            client_delete(md, clients, message);
            break;
        default:
            break;
    }
}

void all_clients_exit(int md, struct list * clients, struct msgbuf * message) {
    struct list_element * head;

    head = clients->head;
    message->data.type = EXIT;
    while(head != NULL) {
        message->mtype = ((struct user *)(head->data))->pid;
        printf("SERVER: CLOSE SESSION FOR %s USER\n", ((struct user *)(head->data))->name);
        msgsnd(md, (void *) message, sizeof(struct data), 0);
        head = head->next;
    }
}

void send_message(int md, struct list * clients, struct msgbuf * message) {
    struct list_element * head;

    //strcat(all_messages, message->data.mtext);
    head = clients->head;
    while(head != NULL) {
        message->mtype = ((struct user *)(head->data))->pid;
        printf("SERVER: SEND MESSAGE %s TO %s USER\n", message->data.mtext, ((struct user *)(head->data))->name);
        printf("THE MESSAGES CONSIST %s\n", ((char *) all_messages));
        msgsnd(md, (void *) message, sizeof(struct data), 0);
        head = head->next;
    }
}

void client_delete(int md, struct list * clients, struct msgbuf * message) {
    struct list_element * head;

    remove_list_element(clients, find(clients, (void *) message, compare));
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