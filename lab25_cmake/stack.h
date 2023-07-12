#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    int value;
    int key;
} Data;

typedef struct Node {
    Data data;
    struct Node *next;
} Stack;

bool is_empty(Stack *top);

void push(Stack **top, Data new_data);

void print(Stack *top);

Data peek(Stack *top);

Data pop(Stack **top);

#endif