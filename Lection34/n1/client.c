#include <stdio.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void) {
    __key_t key;
    __key_t key_sem;
    int page;
    int sem_gr;
    void * mem;
    struct sembuf lock[2] = {{0, 0, 0}, {0, 1, 0}};
    struct sembuf unlock = {0, -1, 0};


    key = ftok("server", 5);
    page = shmget(key, BUFFER_SIZE, 0);

    if (page < 0) {
        perror("shmget: ");
        return errno;
    }

    mem = shmat(page, NULL, 0);

    if (mem == NULL) {
        perror("shmat: ");
        shmctl(page, IPC_RMID, NULL);
        return errno;
    }

    key_sem = ftok("server", 6);
    sem_gr = semget(key_sem, 1, 0);

    if (sem_gr < 0) {
        perror("semget: ");
        shmdt(mem);
        shmctl(page, IPC_RMID, NULL);
        return errno;
    }

    if (semop(sem_gr, (struct sembuf *) &lock, 2) < 0) {
        perror("semop: ");
        shmdt(mem);
        shmctl(page, IPC_RMID, NULL);
        semctl(sem_gr, 0, IPC_RMID);
        return errno;
    }
    
    printf("SERVER: %s\n", (char *) mem);
    strcpy((char *) mem, "Hi!");
    
    shmdt(mem);
    shmctl(page, IPC_RMID, NULL);
    semctl(sem_gr, 0, IPC_RMID);

    return 0;
}