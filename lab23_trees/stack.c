#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "stack.h"
#include "tree.h"

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

bool stackPush(Stack *stack, TreeNode *treenode) {
    StackNode *new_node = (StackNode *) malloc(sizeof(StackNode));
    if (new_node == NULL)
        return false;
    new_node->treeNode = treenode;
    new_node->next = stack->head;
    stack->head = new_node;
    stack->size++;
    return true;
}

TreeNode *stackPeek(Stack *stack) {
    return stack->head->treeNode;
}

TreeNode *stackPop(Stack *stack) {
    TreeNode *res = stack->head->treeNode;
    StackNode *temp = stack->head->next;
    free(stack->head);
    stack->head = temp;
    stack->size--;
    return res;
}

void stackPrint(Stack *stack) {
    StackNode *treeNode = stack->head;
    while (treeNode != NULL) {
        printf("treeNode = %p, ", (void *) treeNode->treeNode);
        treeNode = treeNode->next;
    }
}