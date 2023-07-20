#include <stdio.h>

#define N 5
#define LEFT 0
#define DOWN 1
#define RIGHT 2
#define UP 3

void right_go(int matrix[N][N], int borders[4], int * number) {
    for (int i = borders[LEFT]; i <= borders[RIGHT]; i++) {
        matrix[borders[UP]][i] = (*number)++;
    }
    borders[UP]++;
}

void down_go(int matrix[N][N], int borders[4], int * number) {
    for (int i = borders[UP]; i <= borders[DOWN]; i++) {
        matrix[i][borders[RIGHT]] = (*number)++;
    }
    borders[RIGHT]--;
}

void left_go(int matrix[N][N], int borders[4], int * number) {
    for (int i = borders[RIGHT]; i >= borders[LEFT]; i--) {
        matrix[borders[DOWN]][i] = (*number)++;
    }
    borders[DOWN]--;
}

void up_go(int matrix[N][N], int borders[4], int * number) {
    for (int i = borders[DOWN]; i >= borders[UP]; i--) {
        matrix[i][borders[LEFT]] = (*number)++;
    }
    borders[LEFT]++;
}

void print_matrix(const int matrix[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrix[N][N];
    int flag = 0, number = 1;
    int borders[4] = {0, N - 1, N - 1, 0};
    while (number != N * N + 1) {
        switch (flag) {
            case 0:
                right_go(matrix, borders, &number);
                flag = 1;
                break;
            case 1:
                down_go(matrix, borders, &number);
                flag = 2;
                break;
            case 2:
                left_go(matrix, borders, &number);
                flag = 3;
                break;
            case 3:
                up_go(matrix, borders, &number);
                flag = 0;
                break;
            default:
                break;
        }
    }
    print_matrix(matrix);
    return 0;
}