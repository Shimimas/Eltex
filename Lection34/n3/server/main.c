#include "server.h"
#include "../general/list.h"
#include "../general/msgq_data.h"

void * all_messages;
sem_t * sem_gr;

int main(void) {
    int page;

    __key_t key;
    struct msgbuf message;
    struct list clients;
    int md;
    int server_status = 1;

    pthread_t thread;
    int * s;

    key = ftok("main", 5);
    md = msgget(key, IPC_CREAT | 0600);
    
    page = shm_open("/server1", O_RDWR | O_CREAT, 0777);

    if (page < 0) {
        perror("shm_open: ");
        return errno;
    }

    if (ftruncate(page, BUFFER_SIZE) < 0) {
        perror("ftruncate: ");
        shm_unlink("/server1");
        return errno;
    }

    all_messages = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, page, 0);

    if (all_messages == NULL) {
        perror("mmap: ");
        shm_unlink("/server1");
        return errno;
    }

    sem_gr = sem_open("/server2", O_CREAT, 0600, 0);

    if (sem_gr == SEM_FAILED) {
        perror("sem_open: ");
        munmap(all_messages, BUFFER_SIZE);
        shm_unlink("/server1");
        return errno;
    }

    sem_post(sem_gr);

    pthread_create(&thread, NULL, for_exit_process, (void *) &md);

    while(server_status) {
        msgrcv(md, (void *) &message, sizeof(struct data), SERVER_INFORMATION, 0);
        interface(md, &message, &clients, &server_status);
    }

    pthread_join(thread, (void **) &s);

    list_clear(&clients);
    msgctl(md, IPC_RMID, NULL);
    munmap(all_messages, BUFFER_SIZE);
    shm_unlink("/server1");
    sem_close(sem_gr);
    sem_unlink("/server2");
    return 0;
}