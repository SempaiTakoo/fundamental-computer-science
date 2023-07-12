# Отчёт по курсовому проекту №9 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 11</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>23.06.23</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>удовл.</ins>

<b>Отчёт сдан</b> «23» <ins>июнь</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins>3</ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема:
Сортировка и поиск

## 2. Цель работы:
Составить программу на языке Си с использованием процедур и функций для сортировки таблицы заданным методом
и двоичного поиска по ключу в таблице.

## 3. Задание:
Метод сортировки:
    - быстрая сортировка Хоара (рекурсивный вариант)
Структура таблицы:
    - тип ключа: комбинированный (строка + целое)
    - длина ключа в байтах: 32
    - хранение данных и ключей: вместе
    - минимальное число элементов таблицы: 18

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
Необходимо реализовать структуру таблиц с ключами и данными и основной функционал. Далее требуется реализовать сортировку по варианту и двоичный поиск.
В последнюю очередь нужно реализовать простейший пользовательский интерфейс.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]:
table.h
```
#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define KEY_LENGHT 20

typedef struct {
    char charKey[KEY_LENGHT];
    int intKey;
} Key;

typedef struct {
    Key key;
    char *value;
} Item;

typedef struct {
    Item *data;
    size_t size;
} Table;

Table tableCreate();

Table tableCopy(Table table);

void tablePush(Table *table, char *charKey, int intKey, char *value);

Table tableQSort(Table table);

char *tableBinarySearch(Table table, char *charKey, int intKey);

void tablePrint(Table table);

void tableDestroy(Table *table);

#endif
```
table.c
```

#include "table.h"

Table tableCreate() {
    Table table;
    table.data = (Item*) calloc(0, sizeof(Item));
    table.size = 0;
    return table;
}

Table tableCopy(Table table) {
    Table temp = tableCreate();
    for (int i = 0; i < table.size; ++i) {
        char *value = (char*) calloc(256, sizeof(char));
        strcpy(value, table.data[i].value);
        tablePush(&temp, table.data[i].key.charKey, table.data[i].key.intKey, value);
    }
    return temp;
}

void tablePush(Table *table, char *charKey, int intKey, char *value) {
    Key ck = { .intKey = intKey };
    for (int i = 0; i < KEY_LENGHT && i < (int) strlen(charKey); ++i) {
        ck.charKey[i] = charKey[i];
    }
    Item i = { .key = ck, .value = value };
    table->data = (Item*) realloc(table->data, sizeof(Item) * (table->size + 1));
    table->size++;
    table->data[table->size - 1] = i;
}

static void tableQuickSort(Table *table, uint64_t l, uint64_t r) {
    char *pivot_value = table->data[l].value;
    Key pivot_key = table->data[l].key;
    int l_init = l, r_init = r;
    while (l < r) {
        while (
            (
                strcmp(pivot_key.charKey, table->data[r].key.charKey) < 0 ||
                (
                    strcmp(pivot_key.charKey, table->data[r].key.charKey) == 0 &&
                    pivot_key.intKey <= table->data[r].key.intKey
                )
            ) && (l < r)
        ) r--;
        if (l != r) {
            table->data[l].value = table->data[r].value;
            table->data[l].key = table->data[r].key;
            l++;
        }
        while (
            strcmp(pivot_key.charKey, table->data[l].key.charKey) > 0 &&
            (l < r)
        ) l++;
        if (l != r) {
            table->data[r].value = table->data[l].value;
            table->data[r].key = table->data[l].key;
            r--;
        }
    }
    table->data[l].key = pivot_key;
    table->data[l].value = pivot_value;
    int pivot = l;
    l = l_init;
    r = r_init;
    if (l < pivot) tableQuickSort(table, l, pivot - 1);
    if (r > pivot) tableQuickSort(table, pivot + 1, r);
}

Table tableQSort(Table table) {
    Table temp = tableCopy(table);
    tableQuickSort(&temp, 0, temp.size - 1);
    return temp;
}

char *tableBinarySearch(Table table, char *charKey, int intKey) {
    int l = 0, r = table.size - 1, m = (l + r) / 2;
    while (l <= r) {
        m = (l + r)/2;
        char *curCharKey = table.data[m].key.charKey;
        int curIntKey = table.data[m].key.intKey;
        if (strcmp(charKey, curCharKey) == 0 && intKey == curIntKey)
            return table.data[m].value;
        if (strcmp(charKey, curCharKey) > 0 || (strcmp(charKey, curCharKey) == 0 && intKey < curIntKey))
            l = m + 1;
        else
            r = m - 1;
    }
    return NULL;
}


void tablePrint(Table table) {
    printf("| Key%*s| Value\n", KEY_LENGHT + 11 - 3, "");
    for (int i = 0; i < table.size; ++i) {
        printf("| %*s%11d| %s\n", KEY_LENGHT, table.data[i].key.charKey, table.data[i].key.intKey, table.data[i].value);
    }
}


void tableDestroy(Table *table) {
    for (uint64_t i = 0; i < table->size; ++i) {
        table->data[i].key.charKey[0] = '\0';
        table->data[i].key.intKey = 0;
        free(table->data[i].value);
    }
    free(table->data);
}
```
main.c
```

#include "table.h"

int main() {
    Table table = tableCreate();

    int count = 0;
    printf("Input how many rows do you want to insert: ");
    scanf("%d", &count);

    for (int i = 0; i < count; ++i) {
        printf("Row %d:\n", i);

        char *charKey = (char*) calloc(256, sizeof(char));
        printf("Input key string: \n");
        scanf("%s", charKey);

        int intKey = 0;
        printf("Input key int: \n");
        scanf("%d", &intKey);

        char *value = (char*) calloc(256, sizeof(char));
        printf("Input value string: \n");
        scanf("%s", value);

        tablePush(&table, charKey, intKey, value);

        free(charKey);

        printf("\n");
    }

    tablePrint(table);
    printf("\n");
    table = tableQSort(table);
    tablePrint(table);

    int search = 1;
    while (search) {
        char *charKey = (char*) calloc(256, sizeof(char));
        int intKey = 0;
        printf("\n Search for: \n");
        scanf("%s", charKey);
        scanf("%d", &intKey);

        printf("Found string: %s\n", tableBinarySearch(table, charKey, intKey));
        free(charKey);

        printf("Do you want to continue the search? (0/1): \n");
        scanf("%d", &search);
    }

    tableDestroy(&table);
}
```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола:
```
takoo@takoo:~/Desktop/kp9$ make all
gcc -Wall -pedantic -std=c18 -g -c main.c -o main.o
gcc -Wall -pedantic -std=c18 -g -c table.c -o table.o
gcc -Wall -pedantic -std=c18 -g main.o table.o -o main.out
takoo@takoo:~/Desktop/kp9$ valgrind ./main.exe < data.txt
==9300== Memcheck, a memory error detector
==9300== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==9300== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==9300== Command: ./main.exe
==9300== 
Input how many rows do you want to insert: Row 0:
Input key string: 
Input key int: 
Input value string: 

Row 1:
Input key string: 
Input key int: 
Input value string: 

Row 2:
Input key string: 
Input key int: 
Input value string: 

Row 3:
Input key string: 
Input key int: 
Input value string: 

Row 4:
Input key string: 
Input key int: 
Input value string: 

Row 5:
Input key string: 
Input key int: 
Input value string: 

Row 6:
Input key string: 
Input key int: 
Input value string: 

Row 7:
Input key string: 
Input key int: 
Input value string: 

Row 8:
Input key string: 
Input key int: 
Input value string: 

Row 9:
Input key string: 
Input key int: 
Input value string: 

Row 10:
Input key string: 
Input key int: 
Input value string: 

Row 11:
Input key string: 
Input key int: 
Input value string: 

Row 12:
Input key string: 
Input key int: 
Input value string: 

Row 13:
Input key string: 
Input key int: 
Input value string: 

Row 14:
Input key string: 
Input key int: 
Input value string: 

Row 15:
Input key string: 
Input key int: 
Input value string: 

Row 16:
Input key string: 
Input key int: 
Input value string: 

Row 17:
Input key string: 
Input key int: 
Input value string: 

Row 18:
Input key string: 
Input key int: 
Input value string: 

Row 19:
Input key string: 
Input key int: 
Input value string: 

Row 20:
Input key string: 
Input key int: 
Input value string: 

Row 21:
Input key string: 
Input key int: 
Input value string: 

Row 22:
Input key string: 
Input key int: 
Input value string: 

Row 23:
Input key string: 
Input key int: 
Input value string: 

Row 24:
Input key string: 
Input key int: 
Input value string: 

Row 25:
Input key string: 
Input key int: 
Input value string: 

Row 26:
Input key string: 
Input key int: 
Input value string: 

Row 27:
Input key string: 
Input key int: 
Input value string: 

Row 28:
Input key string: 
Input key int: 
Input value string: 

Row 29:
Input key string: 
Input key int: 
Input value string: 

Row 30:
Input key string: 
Input key int: 
Input value string: 

Row 31:
Input key string: 
Input key int: 
Input value string: 

Row 32:
Input key string: 
Input key int: 
Input value string: 

Row 33:
Input key string: 
Input key int: 
Input value string: 

Row 34:
Input key string: 
Input key int: 
Input value string: 

Row 35:
Input key string: 
Input key int: 
Input value string: 

Row 36:
Input key string: 
Input key int: 
Input value string: 

Row 37:
Input key string: 
Input key int: 
Input value string: 

Row 38:
Input key string: 
Input key int: 
Input value string: 

Row 39:
Input key string: 
Input key int: 
Input value string: 

Row 40:
Input key string: 
Input key int: 
Input value string: 

Row 41:
Input key string: 
Input key int: 
Input value string: 

Row 42:
Input key string: 
Input key int: 
Input value string: 

Row 43:
Input key string: 
Input key int: 
Input value string: 

Row 44:
Input key string: 
Input key int: 
Input value string: 

Row 45:
Input key string: 
Input key int: 
Input value string: 

| Key                            | Value
|                gssua        965| _______________________¶_________¶¶
|                rwjsi        885| ________________¶_____¶_¶_______¶_¶
|                fhvrc        374| ________¶______¶¶¶¶___¶__¶____¶¶__¶________¶¶
|                ugjlb        174| ________¶¶¶¶¶__¶¶_¶__¶____¶_¶¶¶___¶¶____¶¶¶¶¶
|                gezuk        494| ________¶¶__¶¶¶¶___¶¶¶_____¶¶_____¶¶_¶¶¶¶__¶¶
|                jlcth        118| _________¶_____¶____¶______________¶¶¶_____¶
|                xzyml        751| __________¶________________________________¶
|                hxnas        364| __¶¶¶_¶¶__¶¶______________________________¶¶
|                rnicc        774| __¶¶¶__¶__________________________________¶¶¶¶
|                bllvy        273| ____¶¶_______________________________________¶¶¶¶¶
|                zuhqf        982| _____¶¶_________________________________________¶¶¶
|                dsogz        220| _______¶¶________________________________¶¶__¶¶¶
|                kiewo        244| ___¶¶¶¶¶¶___________________________¶____¶¶¶¶
|                nogda        329| _¶¶¶_______________________¶¶¶¶¶___¶¶___¶¶¶¶¶
|                snusx        168| _¶¶___________________¶¶¶¶¶¶¶¶¶¶__¶¶¶___¶¶¶_¶¶
|                qkknf        162| ___¶¶¶____________¶¶¶¶¶¶¶¶¶¶_¶¶¶_¶¶¶¶¶_¶¶¶__¶¶¶
|                bwlrt        859| ____¶¶______¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶_¶¶¶
|                unagy        780| __¶¶_______¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶__¶
|                mkfns        733| _¶¶______¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                omatt        895| _¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                zejee        312| ____¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                qdkiv        827| ____¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶__¶_________¶¶¶¶¶¶¶
|                fdldl        655| ______¶¶¶¶¶¶¶¶_____¶¶¶¶_____¶________¶¶¶¶__¶
|                lwqyy        434| ______¶¶¶¶________¶¶__¶¶___¶¶_________¶¶¶__¶
|                ydjlu        614| _______¶¶¶________¶_¶__¶¶__¶___________¶___¶
|                cqwjc        856| _______¶¶¶________¶_¶__¶¶_¶¶___¶¶¶¶¶¶_______¶
|                kvhys        690| ______¶¶¶¶________¶¶_¶¶¶¶¶¶_¶¶¶¶¶¶___________¶
|                cumxt        519| ______¶¶¶¶_________¶¶_¶__¶¶_______¶¶¶_________¶
|                fbtnb        932| ______¶¶¶¶__________¶¶________¶¶¶¶_________¶¶¶
|                qjhei        891| _____¶¶¶¶¶_________¶__¶¶¶_____¶___¶¶_______¶¶
|                jcqqu        266| _____¶¶¶¶¶¶______¶¶¶____¶¶_____¶¶¶_____¶¶¶¶¶
|                nnrsd        495| _____¶¶¶¶¶¶___¶¶¶¶¶¶_____¶¶___¶¶__________¶
|                wyapr        117| ____¶¶¶¶¶_¶__¶__¶_________¶¶_____________¶
|                rfmji        804| ____¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶_____________________¶
|                usloz        863| ____¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_____________¶¶
|                smvyh        805| ___¶¶¶¶¶¶_¶¶_¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶
|                zpicd        697| ___¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                xcwiw        940| ___¶¶¶¶¶__¶¶¶¶¶_¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                ihles        289| __¶¶¶_¶¶_¶¶¶¶¶¶¶¶¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                gjhlo        164| __¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                duwlg        815| __¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                eztxi        143| _¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶
|                dgrhf        573| _¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶
|                bkujn        854| ¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                kdxsl        542| ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                fjekl        211| ___¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶

| Key                            | Value
|                bkujn        854| ¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                bllvy        273| ____¶¶_______________________________________¶¶¶¶¶
|                bwlrt        859| ____¶¶______¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶_¶¶¶
|                cqwjc        856| _______¶¶¶________¶_¶__¶¶_¶¶___¶¶¶¶¶¶_______¶
|                cumxt        519| ______¶¶¶¶_________¶¶_¶__¶¶_______¶¶¶_________¶
|                dgrhf        573| _¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶
|                dsogz        220| _______¶¶________________________________¶¶__¶¶¶
|                duwlg        815| __¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                eztxi        143| _¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶
|                fbtnb        932| ______¶¶¶¶__________¶¶________¶¶¶¶_________¶¶¶
|                fdldl        655| ______¶¶¶¶¶¶¶¶_____¶¶¶¶_____¶________¶¶¶¶__¶
|                fhvrc        374| ________¶______¶¶¶¶___¶__¶____¶¶__¶________¶¶
|                fjekl        211| ___¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                gezuk        494| ________¶¶__¶¶¶¶___¶¶¶_____¶¶_____¶¶_¶¶¶¶__¶¶
|                gjhlo        164| __¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                gssua        965| _______________________¶_________¶¶
|                hxnas        364| __¶¶¶_¶¶__¶¶______________________________¶¶
|                ihles        289| __¶¶¶_¶¶_¶¶¶¶¶¶¶¶¶__¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                jcqqu        266| _____¶¶¶¶¶¶______¶¶¶____¶¶_____¶¶¶_____¶¶¶¶¶
|                jlcth        118| _________¶_____¶____¶______________¶¶¶_____¶
|                kdxsl        542| ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                kiewo        244| ___¶¶¶¶¶¶___________________________¶____¶¶¶¶
|                kvhys        690| ______¶¶¶¶________¶¶_¶¶¶¶¶¶_¶¶¶¶¶¶___________¶
|                lwqyy        434| ______¶¶¶¶________¶¶__¶¶___¶¶_________¶¶¶__¶
|                mkfns        733| _¶¶______¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                nnrsd        495| _____¶¶¶¶¶¶___¶¶¶¶¶¶_____¶¶___¶¶__________¶
|                nogda        329| _¶¶¶_______________________¶¶¶¶¶___¶¶___¶¶¶¶¶
|                omatt        895| _¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                qdkiv        827| ____¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶__¶_________¶¶¶¶¶¶¶
|                qjhei        891| _____¶¶¶¶¶_________¶__¶¶¶_____¶___¶¶_______¶¶
|                qkknf        162| ___¶¶¶____________¶¶¶¶¶¶¶¶¶¶_¶¶¶_¶¶¶¶¶_¶¶¶__¶¶¶
|                rfmji        804| ____¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶_____________________¶
|                rnicc        774| __¶¶¶__¶__________________________________¶¶¶¶
|                rwjsi        885| ________________¶_____¶_¶_______¶_¶
|                smvyh        805| ___¶¶¶¶¶¶_¶¶_¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶¶¶¶
|                snusx        168| _¶¶___________________¶¶¶¶¶¶¶¶¶¶__¶¶¶___¶¶¶_¶¶
|                ugjlb        174| ________¶¶¶¶¶__¶¶_¶__¶____¶_¶¶¶___¶¶____¶¶¶¶¶
|                unagy        780| __¶¶_______¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_¶¶¶__¶
|                usloz        863| ____¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶_____________¶¶
|                wyapr        117| ____¶¶¶¶¶_¶__¶__¶_________¶¶_____________¶
|                xcwiw        940| ___¶¶¶¶¶__¶¶¶¶¶_¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                xzyml        751| __________¶________________________________¶
|                ydjlu        614| _______¶¶¶________¶_¶__¶¶__¶___________¶___¶
|                zejee        312| ____¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                zpicd        697| ___¶¶¶¶¶¶_¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶
|                zuhqf        982| _____¶¶_________________________________________¶¶¶

 Search for: 
Found string: _____¶¶¶¶¶_________¶__¶¶¶_____¶___¶¶_______¶¶
Do you want to continue the search? (0/1): 

 Search for: 
Found string: _______________________¶_________¶¶
Do you want to continue the search? (0/1): 
==9300== 
==9300== HEAP SUMMARY:
==9300==     in use at exit: 13,248 bytes in 47 blocks
==9300==   total heap usage: 236 allocs, 236 frees, 110,144 bytes allocated
==9300==
==9300== All heap blocks were freed -- no leaks are possible
==9300==
==9300== For lists of detected and suppressed errors, rerun with: -s
==9300== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы:

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 23.06.23 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
- [Решённый контест](https://codeforces.com/submissions/SempaiTakoo/contest/1843)

## 11. Выводы
В ходе выполнения работы были получены навыки работы с простейшими базами данных. Также были изучены методы сортировки и поиска.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________