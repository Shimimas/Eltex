#include <stdio.h>

#define N 5

int main() {
    int counter = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", counter++);
        }
        printf("\n");
    }
    return 0;
}