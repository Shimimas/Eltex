#include <stdio.h>

void print_numbers(int a) { // функция для побитового отображения числа (int)
    unsigned int mask = 0x80000000;
    for (int i = 0; i < 32; i++) {
        if (a & mask) {
            printf("1");
        } else {
            printf("0");
        }
        mask >>= 1;
    }
    printf("\n");
}

unsigned char get_byte(unsigned int a, int idx) { // func for getting byte by index(idx) [0..3]
    switch (idx) {
        case 0:
            return a >> 24;
        case 1:
            return (a << 8) >> 24;
        case 2:
            return (a << 16) >> 24;
        case 3:
            return (a << 24) >> 24;
        default:
            printf("Error, type int hasn't %d byte\n", idx);
            return 0;
    }
}


void set_byte(unsigned int * a, int idx, unsigned int val) { // func for setting byte by index(idx) [0..3]
    switch (idx) {
        case 0:
            *a = (*a & 0x00FFFFFF) | (val << 24);
            break;
        case 1:
            *a = (*a & 0xFF00FFFF) | (val << 16);
            break;
        case 2:
            *a = (*a & 0xFFFF00FF) | (val << 8);
            break;
        case 3:
            *a = (*a & 0xFFFFFF00) | val;
            break;
        default:
            printf("Error, type int hasn't %d byte\n", idx);
            break;
    }
}


int main() {
    int a = 0xDDCCBBAA;
    for (int i = 0; i < 4; i++) {
        printf("%d) byte = %u\n", i, get_byte(a, i));
    }
    set_byte(&a, 0, 25);
    set_byte(&a, 1, 200);
    set_byte(&a, 2, 245);
    set_byte(&a, 3, 24);
    for (int i = 0; i < 4; i++) {
        printf("%d) byte = %u\n", i, get_byte(a, i));
    }
    return 0;
}