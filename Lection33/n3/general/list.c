#include "list.h"

void init(struct list * ptr) {
    ptr->head = NULL;
    ptr->tail = NULL;
    ptr->size = 0;
}

void _copy(void * from, void * to, size_t size) {
    char * from_char = (char *) from;
    char * to_char = (char *) to;
    for (int i = 0; i < size; i++) {
        to_char[i] = from_char[i];
    }
}

void push_back(struct list * ptr, void * data, size_t size) {
    struct list_element * element = malloc(sizeof(struct list_element));
    element->data = malloc(size);
    _copy(data, element->data, size);
    if (ptr->size == 0) {
        ptr->head = element;
        element->prv = NULL;
    } else {
        element->prv = ptr->tail;
        ptr->tail->next = element;
    }
    element->next = NULL;
    ptr->tail = element;
    ptr->size++;
}

struct list_element * find(const struct list * ptr, void * goal, int (*compare)(void *, void *)) {
    struct list_element * head = ptr->head;
    while (head != NULL) {
        if (compare(head->data, goal)) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void remove_list_element(struct list * ptr, struct list_element * head) {
    if (ptr->size == 1) {
        ptr->head = NULL;
        ptr->tail = NULL;
    } else if (head == ptr->head) {
        ptr->head = ptr->head->next;
        ptr->head->prv = NULL;
    } else if (head == ptr->tail) {
        ptr->tail = ptr->tail->prv;
        ptr->tail->next = NULL;
    } else {
        head->prv->next = head->next;
        head->next->prv = head->prv;
    }
    ptr->size--;
    free(head->data);
    free(head);
}

void list_clear(struct list * ptr) {
    struct list_element * head = ptr->head;
    while (head != NULL) {
        struct list_element * next_el = head->next;
        free(head->data);
        free(head);
        head = next_el;
    }
}