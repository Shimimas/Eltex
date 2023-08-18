#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>

#define MAX_MESSAGE_SIZE 10

int main(void) {
    mqd_t msg_q_c;
    mqd_t msg_q_s;
    char buffer[MAX_MESSAGE_SIZE];
    int priority;

    msg_q_s = mq_open("/server", O_RDONLY);
    msg_q_c = mq_open("/client", O_WRONLY);
    mq_receive(msg_q_s, buffer, MAX_MESSAGE_SIZE, &priority);
    printf("CLIENT: GET %s FROM SERVER\n", buffer);
    strcpy(buffer, "Hi!");
    printf("CLIENT: SEND %s TO SERVER\n", buffer);
    mq_send(msg_q_c, buffer, MAX_MESSAGE_SIZE, 5);
    return 0;
}