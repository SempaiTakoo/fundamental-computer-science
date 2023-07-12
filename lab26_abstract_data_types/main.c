#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "sort.h"

int main(void) {
    Stack mystack;
    stackCreate(&mystack);
    printf("stackIsEmpty = %d\n", stackIsEmpty(&mystack));
    Data mydata1 = {4, 4};
    Data mydata2 = {8, 1};
    Data mydata3 = {3, 4};
    Data mydata4 = {2, 4};
    Data mydata5 = {1, 3};
    Data mydata6 = {6, 2};
    printf("stackPush = %d\n", stackPush(&mystack, &mydata1));
    printf("stackPush = %d\n", stackPush(&mystack, &mydata2));
    printf("stackPush = %d\n", stackPush(&mystack, &mydata3));
    printf("stackPush = %d\n", stackPush(&mystack, &mydata4));
    printf("stackPush = %d\n", stackPush(&mystack, &mydata5));
    printf("stackPush = %d\n", stackPush(&mystack, &mydata6));
    stackPrint(&mystack);
    printf("sorting...\n");
    stackSelectionSort(&mystack);
    stackPrint(&mystack);
    return 0;
}