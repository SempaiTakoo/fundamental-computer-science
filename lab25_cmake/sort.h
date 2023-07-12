#ifndef SORT_H
#define SORT_H

#include "stack.h"

typedef struct{
    Data data;
    int order;
} DataOrder;

DataOrder get_max_order(Stack *p);

Data pop_max(Stack **stack);

void selection_sort(Stack **top);

#endif