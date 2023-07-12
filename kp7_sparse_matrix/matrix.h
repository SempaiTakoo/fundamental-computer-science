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