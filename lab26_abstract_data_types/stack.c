#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "stack.h"

void stackCreate(Stack *stack) {
    stack->head = NULL;
    stack->size = 0;
}

size_t stackGetSize(Stack *stack) {
    return stack->size;
}

bool stackIsEmpty(Stack *stack) {
    return stack->head == NULL;
}

bool stackPush(Stack *stack, Data *new_data) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (new_node == NULL)
        return false;
    new_node->data = *new_data;
    new_node->next = stack->head;
    stack->head = new_node;
    stack->size++;
    return true;
}

Data stackPeek(Stack *stack) {
    return stack->head->data;
}

Data stackPop(Stack *stack) {
    Data res = stack->head->data;
    Node *temp = stack->head->next;
    free(stack->head);
    stack->head = temp;
    stack->size--;
    return res;
}

void stackPrint(Stack *stack) {
    Node *p = stack->head;
    while (p != NULL) {
        printf("value = %d, ", p->data.value);
        printf("key = %d\n", p->data.key);
        p = p->next;
    }
}