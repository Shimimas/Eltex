#include <stdio.h>

#define N 6

void print_array(const int array[N]) {
    for (int i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void elements_swap(int array[N]) {
    for (int i = 0; i < N / 2; i++) {
        int tmp = array[i];
        array[i] = array[N - i - 1];
        array[N - i - 1] = tmp;
    }
}

int main() {
    int array[N] = {1, 2, 3, 4, 5, 6};
    elements_swap(array);
    print_array(array);
    return 0;
}