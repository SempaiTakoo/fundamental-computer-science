#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    int value;
    int key;
} Data;

typedef struct Node Node;

struct Node {
    Data data;
    Node *next;
};

typedef struct {
    Node *head;
    size_t size;
} Stack;

void stackCreate(Stack *stack);

size_t stackGetSize(Stack *stack);

bool stackIsEmpty(Stack *stack);

bool stackPush(Stack *stack, Data *new_data);

void stackPrint(Stack *stack);

Data stackPeek(Stack *stack);

Data stackPop(Stack *stack);

#endif