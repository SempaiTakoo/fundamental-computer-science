#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "tree.h"

#define MAXLEN 10

int main(void) {
    Tree mytree;
    treeCreate(&mytree);
    treeInsert(&mytree, NULL, 1);
    treeInsert(&mytree, treeRoot(&mytree), 4);
    treeInsert(&mytree, treeRoot(&mytree), 3);
    treeInsert(&mytree, treeRoot(&mytree), 2);
    treeInsert(&mytree, nodeLeftmostSon(treeRoot(&mytree)), 5);
    treeInsert(&mytree, nodeRightBro(nodeLeftmostSon(treeRoot(&mytree))), 7);
    treeInsert(&mytree, nodeRightBro(nodeLeftmostSon(treeRoot(&mytree))), 6);
    treeInsert(&mytree, nodeLeftmostSon(nodeRightBro(nodeLeftmostSon(treeRoot(&mytree)))), 11);
    treeInsert(&mytree, nodeLeftmostSon(nodeRightBro(nodeLeftmostSon(treeRoot(&mytree)))), 10);
    treeInsert(&mytree, nodeLeftmostSon(nodeRightBro(nodeLeftmostSon(treeRoot(&mytree)))), 9);
    treeInsert(&mytree, nodeRightBro(nodeRightBro(nodeLeftmostSon(treeRoot(&mytree)))), 8);
    printf("IsMonotDecreasing = %d \n", IsMonotDecreasing(&mytree));
    treeErase(&mytree, nodeRightBro(nodeLeftmostSon(treeRoot(&mytree))));
    printf("IsMonotDecreasing = %d \n", IsMonotDecreasing(&mytree));
    treePrintPreOrder(&mytree);
    printf("\n");
    treePrintPostOrder(&mytree);
    return 0;
}