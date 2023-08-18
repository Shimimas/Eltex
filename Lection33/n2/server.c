#include <stdio.h>
#include <fcntl.h>
#include <mqueue.h>

#define MAX_MESSAGE 10
#define MAX_MESSAGE_SIZE 10

int main(void) {
    struct mq_attr attr;
    mqd_t msg_q_s;
    mqd_t msg_q_c;
    char buffer[MAX_MESSAGE_SIZE] = "Hello!";
    int priority;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGE;
    attr.mq_msgsize = MAX_MESSAGE_SIZE;
    attr.mq_curmsgs = 0;
    msg_q_s = mq_open("/server", O_CREAT | O_WRONLY, 0600, &attr);
    msg_q_c = mq_open("/client", O_CREAT | O_RDONLY, 0600, &attr);
    printf("SERVER: SEND %s TO CLIENT\n", buffer);
    mq_send(msg_q_s, buffer, MAX_MESSAGE_SIZE, 4);
    mq_receive(msg_q_c, buffer, MAX_MESSAGE_SIZE, &priority);
    printf("SERVER: GET %s FROM CLIENT\n", buffer);
    mq_close(msg_q_c);
    mq_close(msg_q_s);
    mq_unlink("/server");
    mq_unlink("/client");
    return 0;
}