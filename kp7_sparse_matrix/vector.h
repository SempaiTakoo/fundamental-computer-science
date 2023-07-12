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