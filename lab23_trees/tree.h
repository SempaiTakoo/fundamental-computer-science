#ifndef TREE_H
#define TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
    struct TreeNode *parent, *leftBro, *rightBro, *son;
    int value;
};

typedef struct TreeNode TreeNode;

typedef struct {
    TreeNode *root;
    size_t size;
} Tree;

TreeNode *treeRoot(Tree *tree);
TreeNode *nodeParent(TreeNode *node);
TreeNode *nodeLeftBro(TreeNode *node);
TreeNode *nodeRightBro(TreeNode *node);
TreeNode *nodeLeftmostSon(TreeNode *node);

size_t treeSize(Tree *tree);

void treeCreate(Tree *tree);

bool treeInsert(Tree *tree, TreeNode *parent, int value);

void treeErase(Tree *tree, TreeNode *node);

void treePrintPreOrder(Tree *tree);

void treePrintPostOrder(Tree *tree);

int sonsCount(TreeNode *node);

bool IsMonotDecreasing(Tree *tree);

#endif