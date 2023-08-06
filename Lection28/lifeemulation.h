#ifndef __LIFEEMULATION_H_
#define __LIFEEMULATION_H_

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

struct buyer {
    int number;
    int need;
};

extern int shops[5];
extern pthread_mutex_t m1;
extern int status;

void * buyer_move(void * ptr);
void * loader(void * ptr);
void buyers_inizialization(struct buyer buyers[3]);

#endif // __LIFEEMULATION_H_