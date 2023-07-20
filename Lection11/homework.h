#ifndef LECTION_11_HOMEWORK_H_
#define LECTION_11_HOMEWORK_H_

#define NAME_SIZE 10
#define LASTNAME_SIZE 10

#include <stdio.h>
#include <stdlib.h>

struct abonent {
    char name[NAME_SIZE];
    char lastname[LASTNAME_SIZE];
    long number;
    struct abonent * next;
    struct abonent * prv;
};

struct abonents_book {
    int size;
    struct abonent * head;
    struct abonent * tail;
};

void menu();
void interface();
void abonent_print(const struct abonent * abonent_);
void init(struct abonents_book * ptr);
void add_element(struct abonents_book * ptr);
void list_print(const struct abonents_book * ptr);
void abonent_find(const struct abonents_book * ptr);
int strings_equal(char name1[10], char name2[10]);
void delete_el(struct abonents_book * ptr, struct abonent * head);

#endif  // LECTION_11_HOMEWORK_H_
