
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