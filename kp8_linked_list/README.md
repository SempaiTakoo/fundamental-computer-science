# Отчёт по курсовому проекту №8 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 11</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>25.05.23</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>"отлично"</ins>

<b>Отчёт сдан</b> «20» <ins>апреля</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins>5</ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема:
Линейные списки

## 2. Цель работы:
Составить и отладить программу на языке Си для обработки линейного списка заданной организации с отображением
списка на динамические структуры

## 3. Задание:
1. Стандартные действия:
- Печать списка
- Вставка нового элемента в список
- Удаление элемента из списка
- Подсчёт длины списка

2. Вид списка:
- Линейныцй двунаправленный с барьерным элементом

3. Нестандартное действие:
- Проверка упорядоченности элементов списка

## 4. Оборудование:
<b>Процессор:</b> 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz<br/>
<b>ОП:</b> 8 ГБ <br/>
<b>SSD:</b> 256 ГБ<br/>

## 5. Программное обеспечение:
<b>Операционная система семейства:</b> Windows 11 10.0.22000 <br/>
<b>Интерпретатор команд:</b> Powershell 5.1.22000.832 <br/>
<b>Система программирования:</b> gcc.exe (GCC) 10.3.0 <br/>
<b>Текстовый редактор:</b> Visual Studio Code версия 1.73.1 <br/>
<b>Местонахождение и имена файлов программ и данных на домашнем компьютере:</b> C:\Users\idl76> <br/>

## 6. Идея, метод, алгоритм решения задачи (в формах: словесной, псевдокода, графической [блок-схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями):
Необходимо реализовать основные функции, для взаимодействия со списком: создание списка, вставка, удаление элемента и т. д. Также требуется реализовать итератор для совершения более специфичных и удобных действий, вроде вставки или удаления определённого по счёту элемента списка.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]:
list.h
```c
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

ListIterator listIterNext(ListIterator *iter);

ListIterator listIterPrev(ListIterator *iter);

int listIterGet(ListIterator *iter);

bool listIterEq(ListIterator *iter1, ListIterator *iter2);

bool listPushBack(List *list, int value);

bool listPushFront(List *list, int value);

bool listPush(ListIterator *iter, int value);

bool listPushAfter(ListIterator *iter, int value);

bool listPushBefore(ListIterator *iter, int value);

int listPopBack(List *list);

int listPopFront(List *list);

void listPrint(List *list);

#endif
```

list.c
```c
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
```

main.c
```c
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
```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола:
```bash
idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp8_linked_list
$ make clean all
rm -f *.o main.exe
gcc -Wall -pedantic -std=c18 -c main.c -o main.o
gcc -Wall -pedantic -std=c18 -c list.c -o list.o
gcc -Wall -pedantic -std=c18 main.o list.o -o main.exe

idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp8_linked_list
$ ./main.exe
is empty = 1
size = 0
push front = 1
push front = 1
push front = 1
push front = 1
push back = 1
push back = 1
push back = 1
push back = 1
is empty = 0
size = 8
front = 8
front = 1
list: 1 2 3 4 5 6 7 8
pop back = 8
pop front = 7
list: 1 2 3 4 5 6

iter -> head
push before iter = 1
iter -> tail
push iter = 1
iter -> prev
push after iter = 1
iter -> prev
pop iter = 6
list: 0 1 2 3 4 100

list: 0 1 2 3 4 100
is sorted = 1
push back = 1
list: 0 1 2 3 4 100 -1000
is sorted = 0
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы:

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 25.05.23 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
- [Решённый контест](https://codeforces.com/submissions/SempaiTakoo/contest/1821)

## 11. Выводы
В ходе выполнения работы были освоены навыки работы со связными списками. Также были получены знания о работе барьерных элементов и итераторов, принципах их реализации и использования.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________