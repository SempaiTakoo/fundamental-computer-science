#include <stdio.h>

#define N (127)

void matrix_print(int n, int (*mat)[n], int top, int bot, int left, int right) {
    int up_mid = left + (bot - top) / 2;
    int side_mid = top + (right - left) / 2;
    if (bot - top == 1) {
        printf("%d ", mat[top][left]);
        return;
    }
    for (int i = top; i < bot; ++i) {
        printf("%d ", mat[i][up_mid]);
    }
    for (int j = left; j < right; ++j) {
        if (j == up_mid) continue;
        printf("%d ", mat[side_mid][j]);
    }
    matrix_print(n, mat, top, side_mid, left, up_mid);
    matrix_print(n, mat, side_mid + 1, bot, left, up_mid);
    matrix_print(n, mat, side_mid + 1, bot, up_mid + 1, right);
    matrix_print(n, mat, top, side_mid, up_mid + 1, right);
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
    matrix_print(n, (int (*)[n]) mat, 0, n, 0, n);
    return 0;
}