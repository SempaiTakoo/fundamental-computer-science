#include <math.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

#define MAX_EXPRESSION_LENGTH 100

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        printf("Use: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Can't open file\n");
        return 1;
    }

    stack* s1 = malloc(sizeof(stack));
    initStack(s1);
    char exp[MAX_EXPRESSION_LENGTH];
    if (fgets(exp, MAX_EXPRESSION_LENGTH, file) == NULL) {
        printf("Can't read file\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    node* expression = NULL;
    infixToPostfix(exp, &expression);
    Tree* tree = postfixToTree(expression);
    destroy(expression);
    printTree(tree, 0);
    
    printf("Task:\n");
    simplifyFraction(tree);
    printTree(tree, 0);
    treeToExpresion(tree);
    putchar('\n');

    clearTree(tree);
    stackDestroy(s1);
    return 0;
}
