#include "lifeemulation.h"

int shops[5];
pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
int status = 0;

int main(void) {
    pthread_t thread[4];
    struct buyer buyers[3];
    buyers_inizialization(buyers);
    int * s;
    for (int i = 0; i < 3; i++) {
        pthread_create(&thread[i], NULL, buyer_move, (void *) &buyers[i]);
    }
    pthread_create(&thread[3], NULL, loader, NULL);
    for (int i = 0; i < 4; i++) {
        pthread_join(thread[i], (void **) &s);
    }
    for (int i = 0; i < 3; i++) {
        printf("%d) Buyer has %d\n", i, buyers[i].need);
    }
    return 0;
}