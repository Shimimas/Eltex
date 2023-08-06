#include "lifeemulation.h"

void * buyer_move(void * ptr) {
    struct buyer * b = (struct buyer *) ptr;
    while (1) {
        for (int i = 0; i < 5; i++) {
            pthread_mutex_lock(&m1);
            if (shops[i] > 0) {
                (*b).need -= shops[i];
                printf("Buyer %d, takes %d needs from %d shop\n", (*b).number, shops[i], i);
                if ((*b).need == 0) {
                    status++;
                    pthread_mutex_unlock(&m1);
                    printf("Buyer %d, finished\n", (*b).number);
                    pthread_exit(0);
                }
                shops[i] = 0;
            } else {
                printf("Buyer %d, not found needs in %d shop\n", (*b).number, i);
            }
            pthread_mutex_unlock(&m1);
            sleep(1);
        }
    }
}

void * loader(void * ptr) {
    while (1) {
        for (int i = 0; i < 3; i++) {
            pthread_mutex_lock(&m1);
            if (status == 3) {
                pthread_mutex_unlock(&m1);
                printf("Loader finished work!\n");
                pthread_exit(0);
            }
            printf("Loader set 500 needs to %d shop!\n", i);
            shops[i] += 500;
            pthread_mutex_unlock(&m1);
            sleep(2);
        }
    }
}

void buyers_inizialization(struct buyer buyers[3]) {
    for (int i = 0; i < 3; i++) {
        buyers[i].number = i;
        buyers[i].need = 10000;
    }
}