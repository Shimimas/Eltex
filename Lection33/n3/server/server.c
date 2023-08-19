#include "server.h"

int compare(void * data, void * goal) {
    int * data_int = (int *) data;
    int * goal_int = (int *) goal;
    if (*data_int == *goal_int) {
        return 1;
    }
    return 0;
}