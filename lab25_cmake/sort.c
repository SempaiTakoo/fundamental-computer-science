#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "sort.h"

DataOrder get_max_order(Stack *p) {
    Data max = {0, 0};
    int order = 0;
    while (p) {
        if (p->data.key > max.key) {
            max = p->data;
            order = 0;
        } else if (p->data.key == max.key) {
            max = p->data;
            ++order;
        }
        p = p->next;
    }
    DataOrder max_order = {max, order};
    return max_order;
}

Data pop_max(Stack **stack) {
    DataOrder max_order = get_max_order(*stack);
    Data max = max_order.data;
    int order = max_order.order;
    if (peek(*stack).key == max.key && order == 0) {
        return pop(stack);
    }
    Stack *cur = *stack;
    Stack *prev = NULL;
    while (cur->next != NULL) {
        if (cur->data.key == max.key) {
            if (order > 0) --order;
            else break;
        }
        prev = cur; 
        cur = cur->next;
    }
    prev->next = cur->next;
    free(cur);
    return max;
}

void selection_sort(Stack **top) {
    Stack *sorted_stack = NULL;
    while (!is_empty(*top)) {
        push(&sorted_stack, pop_max(top));
    }
    *top = sorted_stack;
}