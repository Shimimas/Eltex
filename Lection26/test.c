#include <pthread.h>
#include <stdio.h>

int a = 0;

void * counter(void * ptr) {
    for (int i = 0; i < 100000; i++) {
        a++;
    }
}

int main(void) {
    pthread_t thread[1000];
    int * s;
    for (int i = 0; i < 1000; i++) {
        pthread_create(&thread[i], NULL, counter, NULL);
    }
    for (int i = 0; i < 1000; i++) {
        pthread_join(thread[i], (void **) &s);
    }
    printf("a = %d\n", a);
    return 0;
}