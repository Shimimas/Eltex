#include <stdio.h>

#define N 4

void print_matrix(int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j < N - 1 - i) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = 1;
            }
        }
    }
    print_matrix(matrix);
    return 0;
}