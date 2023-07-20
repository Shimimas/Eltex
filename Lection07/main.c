#include <stdio.h>

int main() {
    volatile int a = 5;
    switch (a) {
        case 1:
            printf("1\n");
            break;
        case 2:
            printf("2\n");
        case 3:
            printf("3\n");
        case 4:
            printf("4\n");
            break;
        case 100:
            printf("100\n");
            break;
        case 1000:
            printf("1000\n");
            break;
        default:
            printf("default\n");
            break;
    }
    return 0;
}