#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tree.h"
#include "stack.h"

size_t treeSize(Tree *tree) {
    return tree->size;
}

TreeNode *treeRoot(Tree *tree) {
    return tree->root;
}

TreeNode *nodeParent(TreeNode *node) {
    return node->parent;
}

TreeNode *nodeLeftBro(TreeNode *node) {
    return node->leftBro;
}

TreeNode *nodeRightBro(TreeNode *node) {
    return node->rightBro;
}

TreeNode *nodeLeftmostSon(TreeNode *node) {
    return node->son;
}

void treeCreate(Tree *tree) {
    tree->root = NULL;
    tree->size = 0;
}

bool treeInsert(Tree *tree, TreeNode *parent, int value) {
    TreeNode *node = (TreeNode *) malloc(sizeof(TreeNode));
    if (node == NULL)
        return false;
    node->parent = parent;
    node->leftBro = NULL;
    node->son = NULL;
    node->value = value;
    if (parent != NULL) {
        node->rightBro = parent->son; 
        if (parent->son != NULL) {
            parent->son->leftBro = node;
        }
        parent->son = node;
    } else {
        node->rightBro = NULL;
        tree->root = node;
    }
    ++tree->size;
    return true;
}

static size_t nodeDelete(TreeNode *node) {
    size_t count = 1;
    TreeNode **cur = &node->son;
    while (*cur != NULL) {
        count += nodeDelete(*cur);
        cur = &(*cur)->rightBro;
    }
    free(node);
    return count;
}

void treeErase(Tree *tree, TreeNode *node) {
    if (node->leftBro != NULL) {
        node->leftBro->rightBro = node->rightBro;
    } else if (node->parent != NULL) {
        node->parent->son = node->rightBro;
    } else {
        tree->root = NULL;
    }
    if (node->rightBro != NULL) {
        node->rightBro->leftBro = node->leftBro;
    }
    tree->size -= nodeDelete(node);
}

static void postOrder(TreeNode *node, int spaces) {
    if (node == NULL)
        return;
    postOrder(node->son, spaces + 2);
    for (int i = 0; i < spaces; ++i)
        printf(" ");
    printf("%d\n", node->value);
    postOrder(node->rightBro, spaces);
}

static void preOrder(TreeNode *node, int spaces) {
    if (node == NULL)
        return;
    for (int i = 0; i < spaces; ++i)
        printf(" ");
    printf("%d\n", node->value);
    preOrder(node->son, spaces + 2);
    preOrder(node->rightBro, spaces);
}

void treePrintPreOrder(Tree *tree) {
    preOrder(tree->root, 0);
}

void treePrintPostOrder(Tree *tree) {
    postOrder(tree->root, 0);
}

int nodeDepth(TreeNode *node) {
    TreeNode **cur = &node;
    int depth = 0;
    while (*cur != NULL) {
        ++depth;
        cur = &(*cur)->parent;
    }
    return depth;
}

int sonsCount(TreeNode *node) {
    TreeNode **cur = &node->son;
    int count = 0;
    while (*cur != NULL) {
        ++count;
        cur = &(*cur)->rightBro;
    }
    return count;
}

static int levelWidth(TreeNode *node, int level) {
    if (level == nodeDepth(node))
        return sonsCount(node);
    TreeNode **cur = &node->son;
    int sum = 0;
    while (*cur != NULL) {
        sum += levelWidth(*cur, level);
        cur = &(*cur)->rightBro;
    }
    return sum;
}

bool IsMonotDecreasing(Tree *tree) {
    int prev = sonsCount(tree->root), cur = prev;
    for (int level = 1; cur != 0; ++level) {
        prev = cur;
        cur = levelWidth(tree->root, level);
        if (cur > prev)
            return false;
    }
    return true;
}