#include <stdio.h>
#include <limits.h>

#define N (8)

void matrix_print(size_t n, int (*mat)[n]);

typedef struct {
    int i0;
    int i1;
    int i2;
    int j0;
    int j1;
    int j2;
} Indexes;

int determinant(size_t n, int (*mat)[n], Indexes ind) {
    return mat[ind.i0][ind.j0]*mat[ind.i1][ind.j1]*mat[ind.i2][ind.j2] \
         + mat[ind.i0][ind.j1]*mat[ind.i1][ind.j2]*mat[ind.i2][ind.j0] \
         + mat[ind.i0][ind.j2]*mat[ind.i1][ind.j0]*mat[ind.i2][ind.j1] \
         - mat[ind.i0][ind.j2]*mat[ind.i1][ind.j1]*mat[ind.i2][ind.j0] \
         - mat[ind.i0][ind.j0]*mat[ind.i1][ind.j2]*mat[ind.i2][ind.j1] \
         - mat[ind.i0][ind.j1]*mat[ind.i1][ind.j0]*mat[ind.i2][ind.j2];
}

void matrix_print_max_minor(size_t n, int (*mat)[n]) {
    int max_d = INT_MIN;
    Indexes ind;
    for (ind.i0 = 0; ind.i0 < n; ++ind.i0) {
        for (ind.i1 = ind.i0 + 1; ind.i1 < n; ++ind.i1) {
            for (ind.i2 = ind.i1 + 1; ind.i2 < n; ++ind.i2) {
                for (ind.j0 = 0; ind.j0 < n; ++ind.j0) {
                    for (ind.j1 = ind.j0 + 1; ind.j1 < n; ++ind.j1) {
                        for (ind.j2 = ind.j1 + 1; ind.j2 < n; ++ind.j2) {
                            if (determinant(n, mat, ind) > max_d) {
                                max_d = determinant(n, mat, ind);
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d", max_d);
}

void matrix_input(size_t n, int (*mat)[n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
}

int main(void) {
    int mat[N * N];
    size_t n;
    scanf("%zu\n", &n);
    matrix_input(n, (int (*)[n]) mat); 
    matrix_print_max_minor(n, (int (*)[n]) mat);
    return 0;
}