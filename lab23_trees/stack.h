#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#include "tree.h"

typedef struct StackNode StackNode;

struct StackNode {
    TreeNode *treeNode;
    StackNode *next;
};

typedef struct {
    StackNode *head;
    size_t size;
} Stack;

void stackCreate(Stack *stack);

size_t stackGetSize(Stack *stack);

bool stackIsEmpty(Stack *stack);

bool stackPush(Stack *stack, TreeNode *new_node);

void stackPrint(Stack *stack);

TreeNode *stackPeek(Stack *stack);

TreeNode *stackPop(Stack *stack);

#endif