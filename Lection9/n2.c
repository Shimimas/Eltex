#include <stdio.h>

#define N 5

int main() {
    int array[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }
    for (int i = N - 1; i >= 0; i--) {
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}