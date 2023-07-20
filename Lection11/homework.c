#include "homework.h"

void menu() {
    printf("-----------------\n");
    printf("1: Add abonent\n");
    printf("2: Find abonent\n");
    printf("3: Abonent's list print\n");
    printf("4: Delete abonent\n");
    printf("5: Stop\n");
    printf("-----------------\n");
}

void init(struct abonents_book * ptr) {
    ptr->head = NULL;
    ptr->tail = NULL;
    ptr->size = 0;
}

void abonent_print(const struct abonent * abonent_) {
    printf("Name: ");
    for (int i = 0; i < NAME_SIZE; i++) {
        printf("%c", abonent_->name[i]);
    }
    printf("\n");
    printf("Lastname: ");
    for (int i = 0; i < LASTNAME_SIZE; i++) {
        printf("%c", abonent_->lastname[i]);
    }
    printf("\n");
    printf("%ld\n", abonent_->number);
}

void list_print(const struct abonents_book * ptr) {
    struct abonent * head = ptr->head;
    while (head != NULL) {
        abonent_print(head);
        head = head->next;
    }
}

void add_element(struct abonents_book * ptr) {
    struct abonent * element = malloc(sizeof(struct abonent));
    printf("Name:\n");
    scanf("%s", element->name);
    printf("Lastname:\n");
    scanf("%s", element->lastname);
    printf("Number:\n");
    scanf("%ld", &element->number);
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

int strings_equal(char name1[10], char name2[10]) {
    for (int i = 0; i < NAME_SIZE; i++) {
        if (name1[i] != name2[i]) {
            return 0;
        }
    }
    return 1;
}

void abonent_find(const struct abonents_book * ptr) {
    char name[10];
    printf("Name:\n");
    scanf("%s", name);
    struct abonent * head = ptr->head;
    while (head != NULL) {
        if (strings_equal(name, head->name)) {
            abonent_print(head);
        }
        head = head->next;
    }
}

void abonent_delete(struct abonents_book * ptr) {
    char name[10];
    printf("Name:\n");
    scanf("%s", name);
    struct abonent * head = ptr->head;
    while (head != NULL) {
        if (strings_equal(name, head->name)) {
            delete_el(ptr, head);
        }
        head = head->next;
    }
}

void delete_el(struct abonents_book * ptr, struct abonent * head) {
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
    free(head);
}

void list_clear(struct abonents_book * ptr) {
    struct abonent * head = ptr->head;
    while (head != NULL) {
        struct abonent * next_el = head->next;
        free(head);
        head = next_el;
    }
}

void interface() {
    struct abonents_book * ptr = malloc(sizeof(struct abonents_book));
    init(ptr);
    int stop = 1;
    while (stop) {
        menu();
        int number;
        scanf("%d", &number);
        switch (number) {
            case 1:
                add_element(ptr);
                break;
            case 2:
                abonent_find(ptr);
                break;
            case 3:
                list_print(ptr);
                break;
            case 4:
                abonent_delete(ptr);
                break;
            case 5:
                stop = 0;
                list_clear(ptr);
                break;
            default:
                printf("Incorrect input!\nTry again!\n");
                break;
        }
    }
}