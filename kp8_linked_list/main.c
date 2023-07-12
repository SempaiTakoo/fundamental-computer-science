#include <stdio.h>
#include <stdbool.h>

#include "list.h"

int main(void) {
    List mylist;
    listCreate(&mylist);
    printf("is empty = %d \n", listIsEmpty(&mylist));
    printf("size = %lld \n", listSize(&mylist));
    printf("push front = %d \n", listPushFront(&mylist, 4));
    printf("push front = %d \n", listPushFront(&mylist, 3));
    printf("push front = %d \n", listPushFront(&mylist, 2));
    printf("push front = %d \n", listPushFront(&mylist, 1));  
    printf("push back = %d \n", listPushBack(&mylist, 5));
    printf("push back = %d \n", listPushBack(&mylist, 6));
    printf("push back = %d \n", listPushBack(&mylist, 7));
    printf("push back = %d \n", listPushBack(&mylist, 8));
    printf("is empty = %d \n", listIsEmpty(&mylist));
    printf("size = %lld \n", listSize(&mylist));
    printf("front = %d \n", listBack(&mylist));
    printf("front = %d \n", listFront(&mylist));
    printf("list: ");
    listPrint(&mylist);
    printf("pop back = %d \n", listPopBack(&mylist));
    printf("pop front = %d \n", listPopBack(&mylist));
    printf("list: ");
    listPrint(&mylist);

    printf("\n");
    ListIterator myiter = listIterHead(&mylist);
    printf("iter -> head \n");
    printf("push before iter = %d \n", listPushBefore(&myiter, 0));
    myiter = listIterTail(&mylist);
    printf("iter -> tail \n");
    printf("push iter = %d \n", listPush(&myiter, 100));
    myiter = listIterPrev(&myiter); 
    printf("iter -> prev \n");
    printf("push after iter = %d \n", listPush(&myiter, 6));
    printf("iter -> prev \n");
    printf("pop iter = %d \n", listPop(&myiter));
    printf("list: ");
    listPrint(&mylist);

    printf("\n");
    printf("list: ");
    listPrint(&mylist);
    printf("is sorted = %d \n", listIsSorted(&mylist));
    printf("push back = %d \n", listPushBack(&mylist, -1000));
    printf("list: ");
    listPrint(&mylist);
    printf("is sorted = %d \n", listIsSorted(&mylist));
    return 0;
}