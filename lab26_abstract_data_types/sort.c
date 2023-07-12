#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "sort.h"

int dataComparator(Data *a, Data *b) {
    return a->key < b->key ? -1 : a->key > b->key;
}

Data stackPopMax(Stack *stack) {
    Stack newstack;
    stackCreate(&newstack);
    Data max = stackPop(stack);
    Data cur;
    int order = 0;
    while (!stackIsEmpty(stack)) {
        cur = stackPop(stack);
        switch (dataComparator(&cur, &max)) {
            case 1:
                stackPush(&newstack, &max);
                max = cur;
                break;
            case -1:
                stackPush(&newstack, &cur);
                break;
            case 0:
                stackPush(&newstack, &max);
                max = cur;
                order++;
                break;
        }
    }
    while (!stackIsEmpty(&newstack)) {
        cur = stackPop(&newstack);
        stackPush(stack, &cur);
        if ((dataComparator(&cur, &max) == 0) && (order > 0))
            order--;
    }
    return max;
}

void stackSelectionSort(Stack *stack) {
    Stack sorted_stack;
    stackCreate(&sorted_stack);
    Data max;
    while (!stackIsEmpty(stack)) {
        max = stackPopMax(stack);
        stackPush(&sorted_stack, &max);
    }
    *stack = sorted_stack;
}