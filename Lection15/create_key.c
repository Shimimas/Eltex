#include <stdio.h>

int main() {
    FILE * fp = fopen("key.txt", "wb");
    putc('m', fp);
    putc('a', fp);
    putc('a', fp);
    putc('a', fp);
    putc('a', fp);
    putc('a', fp);
    putc('a', fp);
    putc('a', fp);
    putc('a', fp);
    putc('a', fp);
    putc('a', fp);
    putc('a', fp);
    putc('b', fp);
    putc('b', fp);
    putc('b', fp);
    putc('b', fp);
    putc('b', fp);
    putc('b', fp);
    putc('b', fp);
    putc('b', fp);
    putc(0xd2, fp);
    putc(0x11, fp);
    putc(0x40, fp);
    putc(0x00, fp);
    putc(0x00, fp);
    putc(0x00, fp);
    putc(0x00, fp);
    putc(0x00, fp);
    fclose(fp);
    return 0;
}