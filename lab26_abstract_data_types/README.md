# Отчёт по лабораторной работе №26 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 11</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>15.04.23</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>5 (отлично)</ins>

<b>Отчёт сдан</b> «15» <ins>апреля</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins>5 (отлично)</ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема:
Абстрактные типы данных. Рекурсия. Модульное программирование на языке Си

## 2. Цель работы:
Составить и отладить модуль определений и модуль реализации по заданной схеме модуля определений для абстрактного типа данных

## 3. Задание:
Реализовать стек, процедуру поиска и удаления максимального элемента и сортировку линейным выбором

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
1. Написать модуль определений и реализации стека.
2. Написать модуль определений и реализации процедуры и метода.
3. Произвести сборку и отладку модульной программы.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]:
__stack.h:__
```c
#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    int value;
    int key;
} Data;

typedef struct Node Node;

struct Node {
    Data data;
    Node *next;
};

typedef struct {
    Node *head;
    size_t size;
} Stack;

void stackCreate(Stack *stack);

size_t stackGetSize(Stack *stack);

bool stackIsEmpty(Stack *stack);

bool stackPush(Stack *stack, Data *new_data);

void stackPrint(Stack *stack);

Data stackPeek(Stack *stack);

Data stackPop(Stack *stack);

#endif
```

__stack.c:__
```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "stack.h"

void stackCreate(Stack *stack) {
    stack->head = NULL;
    stack->size = 0;
}

size_t stackGetSize(Stack *stack) {
    return stack->size;
}

bool stackIsEmpty(Stack *stack) {
    return stack->head == NULL;
}

bool stackPush(Stack *stack, Data *new_data) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (new_node == NULL)
        return false;
    new_node->data = *new_data;
    new_node->next = stack->head;
    stack->head = new_node;
    stack->size++;
    return true;
}

Data stackPeek(Stack *stack) {
    return stack->head->data;
}

Data stackPop(Stack *stack) {
    Data res = stack->head->data;
    Node *temp = stack->head->next;
    free(stack->head);
    stack->head = temp;
    stack->size--;
    return res;
}

void stackPrint(Stack *stack) {
    Node *p = stack->head;
    while (p != NULL) {
        printf("value = %d, ", p->data.value);
        printf("key = %d\n", p->data.key);
        p = p->next;
    }
}
```

__sort.h:__
```c
#ifndef SORT_H
#define SORT_H

#include "stack.h"

Data stackPopMax(Stack *stack);

void stackSelectionSort(Stack *stack);

#endif
```

__sort.c:__
```c
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "sort.h"

Data stackPopMax(Stack *stack) {
    Node *cur = stack->head;
    Data max = {0, 0};
    int order = 0;
    while (cur != NULL) {
        if (cur->data.key > max.key) {
            max = cur->data;
            order = 0;
        } else if (cur->data.key == max.key) {
            max = cur->data;
            order++;
        }
        cur = cur->next;
    }
    if ((stackPeek(stack).key == max.key) && (order == 0)) {
        return stackPop(stack);
    }
    cur = stack->head;
    Node *prev;
    while (cur->next != NULL) {
        if (cur->data.key == max.key) {
            if (order > 0) {
                order--;
            }
            else {
                break;
            }
        }
        prev = cur;
        cur = cur->next;
    }
    prev->next = cur->next;
    free(cur);
    stack->size--;
    return max;
}

void stackSelectionSort(Stack *stack) {
    Stack sorted_stack;
    stackCreate(&sorted_stack);
    Data max;
    while (!stackIsEmpty(stack)) {
        max = stackPopMax(stack);
        stackPush(&sorted_stack, &max);
    }
    *stack = sorted_stack;
}
```

__main.c:__
```c
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
    printf("stackIsEmpty = %d\n", stackIsEmpty(&mystack));
    printf("stackPop = %d\n", stackPop(&mystack).value);
    stackPrint(&mystack);
    printf("stackPeek = %d\n", stackPeek(&mystack).value);
    printf("sorting...\n");
    stackSelectionSort(&mystack);
    stackPrint(&mystack);
    printf("stackGetSize = %lld\n", stackGetSize(&mystack));
    printf("stackPopMax = %d\n", stackPopMax(&mystack).value);
    printf("stackGetSize = %lld\n", stackGetSize(&mystack));
    return 0;
}
```
__Консоль:__
```bash
idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/lab26_abstract_data_types/main
$ make all
gcc -Wall -pedantic -std=c18 -c main.c -o main.o
gcc -Wall -pedantic -std=c18 main.o stack.o sort.o -o main.exe

idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/lab26_abstract_data_types/main
$ ./main.exe
stackIsEmpty = 1
stackPush = 1
stackPush = 1
stackPush = 1
stackPush = 1
stackPush = 1
stackPush = 1
stackIsEmpty = 0
stackPop = 6
value = 1, key = 3
value = 2, key = 4
value = 3, key = 4
value = 8, key = 1
value = 4, key = 4
stackPeek = 1
sorting...
value = 8, key = 1
value = 1, key = 3
value = 2, key = 4
value = 3, key = 4
value = 4, key = 4
stackGetSize = 5
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы:

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 15.04.23| 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
- [Решённый контест](https://codeforces.com/contest/1810/my)

## 11. Выводы
Были получены навыки написания модульных программ: написание модулей определений, реализации и дальнейшей сборки при помощи утилиты make. Также в ходе выполнения лабораторной работы активно использовались указатали для реализации многих процедур. Навыки работы с динамическим выделением памяти также были получены.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________