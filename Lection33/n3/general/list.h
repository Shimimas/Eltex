#ifndef __LIST_H_
#define __LIST_H_

#include <stdio.h>
#include <malloc.h>

struct list_element {
    struct list_element * next;
    struct list_element * prv;
    void * data;
};

struct list {
    int size;
    struct list_element * head;
    struct list_element * tail;
};

void init(struct list * ptr);
void push_back(struct list * ptr, void * data, size_t size);
void clear(struct list * ptr);
struct list_element * find(const struct list * ptr, void * goal, int (*compare)(void *, void *));
void remove_list_element(struct list * ptr, struct list_element * head);

void _copy(void * from, void * to, size_t size);

#endif  // __LIST_H_