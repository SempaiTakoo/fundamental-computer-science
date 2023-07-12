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