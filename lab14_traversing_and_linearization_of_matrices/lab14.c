#include <stdio.h>

#define N (7)

typedef enum {
    AFTER_SIDE_DIAG,
    BEFORE_SIDE_DIAG
}   Location;

Location get_state(int i, int j, Location state, size_t n) {
    if (((i == n - 1) && (j == 0)) || ((j == n - 1) && (i == 0))) {
        state = AFTER_SIDE_DIAG;
    }
    return state;
}

int isdigit();

void matrix_print(size_t n, int (*mat)[n]) {
    Location state = BEFORE_SIDE_DIAG;
    int direction = 1;
    int i = 0, j = 0;
    while ((i != n) && (j != n)) {
        printf("%02d ", mat[i][j]);
        state = get_state(i, j, state, n);
        switch(state) {
            case BEFORE_SIDE_DIAG:
                if ((j == 0) || (j == n - 1)) {
                    ++i;
                    direction *= -1;
                    printf("%02d ", mat[i][j]);
                    i = i + direction;
                    j = j - direction;
                    break;
                }
                if ((i == 0) || (i == n - 1)) {
                    ++j;
                    direction *= -1;
                    printf("%02d ", mat[i][j]);
                    i = i + direction;
                    j = j - direction;
                    break;
                }
                i = i + direction;
                j = j - direction;
                break;
            case AFTER_SIDE_DIAG:
                if (j == n - 1) {
                    ++i;
                    direction *= -1;
                    printf("%02d ", mat[i][j]);
                    i = i + direction;
                    j = j - direction;
                    break;
                }
                if (i == n - 1) {
                    ++j;
                    direction *= -1;
                    printf("%02d ", mat[i][j]);
                    i = i + direction;
                    j = j - direction;
                    break;
                }
                i = i + direction;
                j = j - direction;
                break;
        }
    }
}

void matrix_input(size_t n, int (*mat)[n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
}

int main(void) {
    size_t n;
    scanf("%zu", &n);
    int mat[N * N];
    matrix_input(n, (int (*)[n]) mat);
    matrix_print(n, (int (*)[n]) mat);
    return 0;
}