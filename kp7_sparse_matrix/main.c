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