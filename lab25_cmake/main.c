#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "sort.h"

int main(void) {
    Stack *mystack = NULL;
    Data mydata1 = {8, 6};
    Data mydata2 = {4, 2};
    Data mydata3 = {9, 4};
    Data mydata4 = {5, 6};
    Data mydata5 = {1, 6};
    push(&mystack, mydata1);
    push(&mystack, mydata2);
    push(&mystack, mydata3);
    push(&mystack, mydata4);
    push(&mystack, mydata5);
    print(mystack);
    printf("---------------\n");
    selection_sort(&mystack);
    print(mystack);
    return 0;
}