#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdbool.h>

typedef struct ListNode {
    struct ListNode *prev, *next;
    int value;
} ListNode;

typedef struct List {
    ListNode *barrier;
    size_t size;
} List;

typedef struct ListIterator {
    ListNode *node;
    List *list;
} ListIterator;

void listCreate(List *list);

bool listIsEmpty(List *list);

size_t listSize(List *list);

bool listIterIsHead(ListIterator *iter);

bool listIterIsTail(ListIterator *iter);

bool listIterIsBarrier(ListIterator *iter);

bool listIsSorted(List *list);

int listBack(List *list);

int listFront(List *list);

ListIterator listIterHead(List *list);

ListIterator listIterTail(List *list);

ListIterator listIterPrev(ListIterator *iter);

ListIterator listIterNext(ListIterator *iter);

int listIterGet(ListIterator *iter);

bool listIterEq(ListIterator *iter1, ListIterator *iter2);

bool listPushBack(List *list, int value);

bool listPushFront(List *list, int value);

bool listPush(ListIterator *iter, int value);

bool listPushAfter(ListIterator *iter, int value);

bool listPushBefore(ListIterator *iter, int value);

int listPopBack(List *list);

int listPopFront(List *list);

int listPop(ListIterator *iter);

void listPrint(List *list);

#endif