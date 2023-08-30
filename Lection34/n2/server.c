#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(void) {
    int page;
    sem_t * sem_gr;
    void * mem;

    page = shm_open("/server1", O_RDWR | O_CREAT, 0777);

    if (page < 0) {
        perror("shm_open: ");
        printf("%d\n", errno);
        return errno;
    }

    if (ftruncate(page, BUFFER_SIZE) < 0) {
        perror("ftruncate: ");
        shm_unlink("/server1");
        return errno;
    }

    mem = mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, page, 0);

    if (mem == NULL) {
        perror("mmap: ");
        shm_unlink("/server1");
        return errno;
    }

    sem_gr = sem_open("/server2", O_CREAT, 0600, 0);

    if (sem_gr == SEM_FAILED) {
        perror("sem_open: ");
        munmap(mem, BUFFER_SIZE);
        shm_unlink("/server1");
        return errno;
    }
    
    strcpy((char *) mem, "Hello!");
    
    if (sem_wait(sem_gr) < 0) {
        perror("sem_wait: ");
        munmap(mem, BUFFER_SIZE);
        shm_unlink("/server1");
        sem_close(sem_gr);
        sem_unlink("/server2");
        return errno;
    }

    printf("CLIENT: %s\n", (char *) mem);

    munmap(mem, BUFFER_SIZE);
    shm_unlink("/server1");
    sem_close(sem_gr);
    sem_unlink("/server2");

    return 0;
}