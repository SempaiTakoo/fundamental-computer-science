#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include <stdlib.h>

#include "list.h"

void listCreate(List *list) {
    list->barrier->prev = list->barrier;
    list->barrier->next = list->barrier;
    list->barrier->value = -1;
    list->size = 0;
}

bool listIsEmpty(List *list) {
    return list->size == 0;
}

bool listIterIsHead(ListIterator *iter) {
    return iter->node == iter->list->barrier->next;
}

bool listIterIsTail(ListIterator *iter) {
    return iter->node == iter->list->barrier->prev;
}

bool listIterIsBarrier(ListIterator *iter) {
    return iter->node == iter->list->barrier;
}

bool listIsSorted(List *list) {
    int cur = 0, prev = 0;
    for (ListIterator iter = listIterHead(list); !listIterIsBarrier(&iter); iter = listIterNext(&iter)) {
        cur = listIterGet(&iter);
        if (prev > cur)
            return false;
        prev = cur;
    }
    return true;
}

size_t listSize(List *list) {
    return list->size;
}

int listBack(List *list) {
    if (list->size == 0)
        return EINVAL;
    return list->barrier->prev->value;
}

int listFront(List *list) {
    if (list->size == 0)
        return EINVAL;
    return list->barrier->next->value;
}

ListIterator listIterHead(List *list) {
    return (ListIterator) {.node = list->barrier->next, .list = list};
}

ListIterator listIterTail(List *list) {
    return (ListIterator) {.node = list->barrier->prev, .list = list};
}

ListIterator listIterPrev(ListIterator *iter) {
    return (ListIterator) {.node = iter->node->prev, .list = iter->list};
}

ListIterator listIterNext(ListIterator *iter) {
    return (ListIterator) {.node = iter->node->next, .list = iter->list};
}

int listIterGet(ListIterator *iter) {
    return iter->node->value;
}

bool listIterEq(ListIterator *iter1, ListIterator *iter2) {
    return iter1->node == iter2->node;
}

void listPrint(List *list) {
    for (ListIterator iter = listIterHead(list); !listIterIsBarrier(&iter); iter = listIterNext(&iter)) {
        printf("%d ", listIterGet(&iter));
    }
    printf("\n");
}

bool listPushBack(List *list, int value) {
    ListNode *temp = (ListNode *) malloc(sizeof(ListNode));
    if (temp == NULL)
        return false;
    temp->value = value; 
    temp->prev = list->barrier->prev;
    temp->prev->next = temp;
    temp->next = list->barrier;
    temp->next->prev = temp;
    ++list->size;
    return true;
}

bool listPushFront(List *list, int value) {
    ListNode *temp = (ListNode *) malloc(sizeof(ListNode));
    if (temp == NULL)
        return false;
    temp->value = value; 
    temp->next = list->barrier->next;
    temp->next->prev = temp;
    temp->prev = list->barrier;
    temp->prev->next = temp;
    ++list->size;
    return true;
}

bool listPush(ListIterator *iter, int value) {
    iter->node->value = value;
    return true;
}

bool listPushAfter(ListIterator *iter, int value) {
    if (listIterIsTail(iter)) {
        listPushBack(iter->list, value);
        return true;
    }
    ListNode *temp = (ListNode *) malloc(sizeof(ListNode));
    if (temp == NULL)
        return false;
    temp->value = value;
    temp->prev = iter->node;
    temp->next = iter->node->next;
    iter->node->next = temp;
    ++iter->list->size;
    return true;
}

bool listPushBefore(ListIterator *iter, int value) {
    if (listIterIsHead(iter)) {
        listPushFront(iter->list, value);
        return true;
    }
    ListNode *temp = (ListNode *) malloc(sizeof(ListNode));
    if (temp == NULL)
        return false;
    temp->value = value;
    temp->prev = iter->node->prev;
    temp->next = iter->node;
    iter->node->prev = temp;
    ++iter->list->size;
    return true;
}

int listPopBack(List *list) {
    // size == 0
    ListNode *temp = list->barrier->prev;
    int res = temp->value;
    temp->prev->next = list->barrier;
    list->barrier->prev = temp->prev;
    free(temp);
    --list->size;
    return res;
}

int listPopFront(List *list) {
    ListNode *temp = list->barrier->next;
    int res = temp->value;
    temp->next->prev = list->barrier;
    list->barrier->next = temp->next;
    free(temp);
    --list->size;
    return res;
}

int listPop(ListIterator *iter) {
    int res = iter->node->value;
    iter->node->prev->next = iter->node->next;
    iter->node->next->prev = iter->node->prev;
    free(iter->node);
    return res;
}