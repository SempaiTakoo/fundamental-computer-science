# Отчёт по курсовому проекту №7 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 11</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>23.06.23</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>удовл.</ins>

<b>Отчёт сдан</b> «23» <ins>июня</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins>3</ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема:
Разреженные матрицы

## 2. Цель работы:
Составить и отладить программу на языке Си для обработки разреженных матриц с элементами целого типа

## 3. Задание:
- Вариант схемы размещения матриц: (3)
    три вектора
- Вариант преобразований: (11)
    транспонировать разреженную матрицу относительно побочной диагонали
- Вариант физического представления: (1)
    отображение на массив

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
В первую очередь необходимо реализовать вектор. Далее реализовать разреженные матрицы на основе трёх векторов с основным функционалом (scan, get, set). В последнюю очередь реализовываем действие.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]:
Makefile:
```
CC=gcc
RM=rm -f
CFLAGS=-Wall -pedantic -std=c18
SOURCES=main.c vector.c matrix.c
OBJECTS=main.o vector.o matrix.o
TARGET=main.exe

all: ${SOURCES} $(TARGET)

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} *.o ${TARGET}
```
vector.h
```
#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int *data;
    size_t capacity, size;
} Vector;

Vector *vectorCreate();

void vectorClear(Vector *vector);

void vectorDestroy(Vector *vector);

bool vectorIsEmpty(Vector *vector);

int *vectorData(Vector *vector);

size_t vectorCapacity(Vector *vector);

size_t vectorSize(Vector *vector);

void vectorResize(Vector *vector, size_t newSize);

void vectorInsert(Vector *vector, size_t index, int value);

bool vectorPushBack(Vector *vector, int value);

void vectorPush(Vector *vector, size_t index, int value);

int vectorGet(Vector *vector, size_t index);

void vectorPrint(Vector *vector);

#endif
```
vector.c
```

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#include "vector.h"

static size_t newCapacity(size_t capacity) {
    if (capacity == 0) {
        return 1;
    }
    return 2 * capacity;
}

Vector *vectorCreate() {
    Vector *vector = malloc(sizeof(Vector));
    vector->size = 0;
    vector->capacity = 1;
    vector->data = malloc(vector->capacity * sizeof(int));
    return vector;
}

void vectorClear(Vector *vector) {
    vector->size = 0;
}

void vectorDestroy(Vector *vector) {
    free(vector->data);
    free(vector);
}

bool vectorIsEmpty(Vector *vector) {
    return vector->size == 0;
}

int *vectorData(Vector *vector) {
    return vector->data;
}

size_t vectorCapacity(Vector *vector) {
    return vector->capacity;
}

size_t vectorSize(Vector *vector) {
    return vector->size;
}

void vectorResize(Vector *vector, size_t newSize) {
    vector->size = newSize;
    if (newSize > vector->capacity) {
        vector->capacity = newSize;
        vector->data = realloc(vector->data, vector->capacity * sizeof(int));
    }
}

void vectorPush(Vector *vector, size_t index, int value) {
    vector->data[index] = value;
}

void vectorInsert(Vector *vector, size_t index, int value) {
    vectorResize(vector, vector->size + 1);
    for (size_t i = (vector->size - 1);i > index;i--) {
        vector->data[i] = vector->data[i - 1];
    }
    vector->data[index] = value;
}

bool vectorPushBack(Vector *vector, int value) {
    if (vector->capacity == vector->size) {
        size_t capacity = newCapacity(vector->capacity);
        int *data = realloc(vector->data, capacity * sizeof(int));
        if (data == NULL)
            return false;
        vector->data = data;
        vector->capacity = capacity;
    }
    vector->data[vector->size++] = value;
    return true;
}

int vectorGet(Vector *vector, size_t index) {
    if ((vector->size < (index  + 1)) || index < 0)
        return EINVAL;
    return vector->data[index];
}

void vectorPrint(Vector *vector) {
    for (int i = 0; i < vector->size; ++i) {
        printf("%d ", vectorGet(vector, i));
    }
    printf("\n");
}
```
matrix.h
```
#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Vector *CIP, *PI, *YE;
    size_t n, m;
} Matrix;

Matrix *matrixCreate();

void matrixClear(Matrix *matrix);

void matrixDestroy(Matrix *matrix);

bool matrixScan(Matrix *matrix, char *filename);

void matrixPrintTables(Matrix *matrix);

void matrixPrint(Matrix *matrix);

void matrixSet(Matrix *matrix, size_t i, size_t j, int value);

int matrixGet(Matrix *matrix, size_t i, size_t j);

void matrixMultNum(Matrix *matrix, int num);

Matrix *matrixTransposed(Matrix *matrix);

Matrix *matrixSideDiagTransposed(Matrix *matrix);

#endif
```
matrix.c
```

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#include "vector.h"
#include "matrix.h"


Matrix *matrixCreate() {
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->CIP = vectorCreate();
    matrix->PI = vectorCreate();
    matrix->YE = vectorCreate();
    matrix->n = 0;
    matrix->m = 0;
    return matrix;
}

void matrixClear(Matrix *matrix) {
    assert(matrix != NULL);
    matrix->n = 0;
    matrix->m = 0;
    vectorClear(matrix->CIP);
    vectorClear(matrix->PI);
    vectorClear(matrix->YE);
}

void matrixDestroy(Matrix *matrix) {
    if (matrix == NULL)
        return;
    vectorDestroy(matrix->CIP);
    vectorDestroy(matrix->PI);
    vectorDestroy(matrix->YE);
    free(matrix);
}

bool matrixScan(Matrix *matrix, char *filename) {
    FILE *input;
    if ((input = fopen(filename, "r")) == NULL) {
        return false;
    }
    int n, m;
    fscanf(input, "%d %d", &n, &m);
    Vector *cip = matrix->CIP, *pi = matrix->PI, *ye = matrix->YE;
    matrixClear(matrix);
    matrix->n = n;
    matrix->m = m;
    for (int i = 0;i < n;i++) {
        vectorPushBack(cip, (int)vectorSize(pi));
        for (int j = 1;j <= m;j++) {
            int cur;
            fscanf(input, "%d", &cur);
            if (cur != 0) {
                vectorPushBack(pi, j);
                vectorPushBack(ye, cur);
            }
        }
    }
    vectorPushBack(pi, 0);
    fclose(input);
    return true;
}

void matrixPrint(Matrix *matrix) {
    assert(matrix != NULL);
    int n = matrix->n, m = matrix->m;
    for (int i = 0;i < n;i++) {
        int ptr = 1;
        int curRowPiInd = matrix->CIP->data[i];
        int nextRowPiInd;
        if (i == (n - 1)) {
            nextRowPiInd = (vectorSize(matrix->PI) - 1);
        } else {
            nextRowPiInd = matrix->CIP->data[i + 1];
        }
        while (curRowPiInd != nextRowPiInd) {
            int curColumn = matrix->PI->data[curRowPiInd];
            int curValue = matrix->YE->data[curRowPiInd];
            while (ptr != curColumn) {
                printf("0\t");
                ptr++;
            }
            ptr++;
            printf("%d\t", curValue);
            curRowPiInd++;
        }
        while (ptr != (m + 1)) {
            printf("0\t");
            ptr++;
        }
        putchar('\n');
    }
}

void matrixPrintTables(Matrix *matrix) {
    assert(matrix != NULL);
    printf("Matrix %llux%llu\n", matrix->n, matrix->m);
    printf("CIP: ");
    vectorPrint(matrix->CIP);
    printf("PI: ");
    vectorPrint(matrix->PI);
    printf("YE: ");
    vectorPrint(matrix->YE);
}

void matrixSet(Matrix *matrix, size_t i, size_t j, int value) {
    assert(matrix != NULL && (int)i < matrix->n && (int)j < matrix->m);
    int n = matrix->n;
    int curRowPiInd = matrix->CIP->data[i];
    int nextRowPiInd;
    if ((int)i == (n - 1)) {
        nextRowPiInd = (int)(vectorSize(matrix->PI) - 1);
    } else {
        nextRowPiInd = matrix->CIP->data[i + 1];
    }
    if (curRowPiInd == nextRowPiInd) {
        j++;
        vectorInsert(matrix->PI, curRowPiInd, (int)j);
        vectorInsert(matrix->YE, curRowPiInd, value);
        for (size_t k = i + 1;(int)k < n;k++) matrix->CIP->data[k]++;
    } else {
        j++;
        while ((int)j > matrix->PI->data[curRowPiInd] && curRowPiInd != nextRowPiInd) {
            curRowPiInd++;
        }
        if ((int)j == matrix->PI->data[curRowPiInd] && curRowPiInd != nextRowPiInd) matrix->YE->data[curRowPiInd] = value;
        else {
            vectorInsert(matrix->PI, curRowPiInd, j);
            vectorInsert(matrix->YE, curRowPiInd, value);
            for (size_t k = i + 1;(int)k < n;k++) matrix->CIP->data[k]++;
        }
    }
}

int matrixGet(Matrix *matrix, size_t i, size_t j) {
    assert(matrix != NULL && (int)i < matrix->n && (int)j < matrix->m);
    int result = 0;
    int curRowPiInd = matrix->CIP->data[i];
    int nextRowPiInd;
    if ((int)i == (matrix->n - 1)) {
        nextRowPiInd = (int)(vectorSize(matrix->PI) - 1);
    } else {
        nextRowPiInd = matrix->CIP->data[i + 1];
    }
    j++;
    for (;curRowPiInd != nextRowPiInd;curRowPiInd++) {
        if (matrix->PI->data[curRowPiInd] == (int)j) result = matrix->YE->data[curRowPiInd];
    }
    return result;
}

void matrixMultNum(Matrix *matrix, int num) {
    for (int i = 0; i < matrix->YE->size; ++i) {
        int value = vectorGet(matrix->YE, i);
        vectorPush(matrix->YE, i, value * num);
    }
}

static Matrix *matrixCreateEmpty(size_t n, size_t m) {
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->CIP = vectorCreate();
    matrix->PI = vectorCreate();
    matrix->YE = vectorCreate();
    matrix->n = n;
    matrix->m = m;
    vectorPushBack(matrix->PI, 0);
    for (int i = 0; i < n; ++i) {
        vectorPushBack(matrix->CIP, 0);
    }
    return matrix;
}

Matrix *matrixSideDiagTransposed(Matrix *matrix) {
    Matrix *newMatrix = matrixCreateEmpty(matrix->m, matrix->n);
    for (size_t j = 0; j < matrix->m; ++j) {
        for (size_t i = 0; i < matrix->n; ++i) {
            int value = matrixGet(matrix, matrix->n - 1 - i, matrix->m - 1 - j);
            matrixSet(newMatrix, j, i, value);
        }
    }
    matrixDestroy(matrix);
    return newMatrix;
}

Matrix *matrixTransposed(Matrix *matrix) {
    Matrix *newMatrix = matrixCreateEmpty(matrix->m, matrix->n);
    for (size_t j = 0; j < matrix->m; ++j) {
        for (size_t i = 0; i < matrix->n; ++i) {
            int value = matrixGet(matrix, i, j);
            matrixSet(newMatrix, j, i, value);
        }
    }
    matrixDestroy(matrix);
    return newMatrix;
}
```
main.c
```
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#include "vector.h"
#include "matrix.h"

int main(void) {
    Matrix *matrix = matrixCreate();
    matrixScan(matrix, "mat.txt");
    matrixPrintTables(matrix);
    matrixPrint(matrix);
    printf("(0, 1): %d \n", matrixGet(matrix, 0, 1));
    matrixSet(matrix, 1, 2, 4);
    matrixMultNum(matrix, 2);
    matrixPrintTables(matrix);
    matrixPrint(matrix);
    return 0;
}
```


Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола:
```
idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp7
$ make all
gcc -Wall -pedantic -std=c18 -c main.c -o main.o
gcc -Wall -pedantic -std=c18 main.o vector.o matrix.o -o main.exe

idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp7
$ ./main.exe
Matrix 5x4
CIP: 0 2 2 3 4
PI: 2 4 2 3 2 3 0
YE: 1 7 4 3 1 9
0       1       0       7
0       0       0       0
0       4       0       0
0       0       3       0
0       1       9       0
(0, 1): 1
Matrix 5x4
CIP: 0 2 3 4 5
PI: 2 4 3 2 3 2 3 0
YE: 2 14 8 8 6 2 18
0       2       0       14
0       0       8       0
0       8       0       0
0       0       6       0
0       2       18      0
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы:

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 23.06.23 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
- [Решённый контест](https://codeforces.com/submissions/SempaiTakoo/contest/1837)

## 11. Выводы
Были получены навыки работы с разреженными матрицами, файлами, динамическими структурамии и указателями в Си. Также освоены базовые навыки устранения утечек памяти с помощью утилиты Valgrind.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________