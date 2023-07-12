#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"

bool is_empty(Stack *top) {
    return top == NULL ? true : false;
}

// Функция получает на вход указатель на адрес стек-указателя
void push(Stack **top, Data new_data) {
    Stack *new_top = (Stack *) malloc(sizeof(Stack)); // Создаём стек-указатель на некоторый участок памяти
    new_top->data = new_data; // В value по новому указателю записываем значение
    new_top->next = *top; // В next по новому указателю записываем адрес стек-указателя, указывающий на вершину (разыменование)
    *top = new_top; // В адрес стек-указателя, указывающий на вершину, записываем указатель на новую вершину
}

// Функция получает стек-указатель
Data peek(Stack *top) {
    return top->data;
}

// Функция получает на вход указатель на адрес стек-указателя
Data pop(Stack **top) {
    Data res = (*top)->data; // Сохраняем значение с вершины стека
    Stack *tmp = *top; // Создаём временный второй указатель на вершину стека
    *top = (*top)->next; // Теперь указатель на вершину указывает на следующий за вершиной узел
    free(tmp); // Используем временный указатель на предыдущую вершину, чтобы освободить тамошнюю память
    return res;
}

void print(Stack *top) {
    while (top != NULL) {
        printf("value = %d, key = %d \n", top->data.value, top->data.key);
        top = top->next;
    }
}