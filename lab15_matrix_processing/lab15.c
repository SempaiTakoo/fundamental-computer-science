#include <stdio.h>

#define N (7)

typedef enum {
    RIGHT,
    UP,
    LEFT,
    DOWN
} Direction;

typedef struct {
    int i, j;
    Direction direction;
    int step_size;
    int step_count;

} Element;

void print_matrix();

Element rotate(size_t n, Element elem, int count) {
    for (int k = 0; k < count; ++k) {
        if ((elem.i == n - 1) && (elem.j == n - 1)) {
            elem.i = n / 2;
            elem.j = n / 2 + n % 2 - 1;
            elem.direction = RIGHT;
            elem.step_size = 1;
            elem.step_count = 0;
            continue;
        }
        if (elem.direction == RIGHT) ++elem.j;
        if (elem.direction == UP) --elem.i;
        if (elem.direction == LEFT) --elem.j;
        if (elem.direction == DOWN) ++elem.i;
        ++elem.step_count;
        if (elem.step_count % elem.step_size == 0) {
            elem.direction = elem.direction == DOWN ? RIGHT : elem.direction + 1;
        }
        if (elem.step_count == elem.step_size * 2) {
            ++elem.step_size;
            elem.step_count = 0;
        }
    }
    return elem;
}

void cyclic_shift(size_t n, int (*mat)[n]) {
    int buffer_mat[n][n];
    Element cur;
    Element shifted;
    cur.i = n / 2;
    cur.j = n / 2 + n % 2 - 1;
    cur.direction = RIGHT;
    cur.step_size = 1;
    cur.step_count = 0;

    for (int k = 0; k < n * n; ++k) {
        shifted = rotate(n, cur, 8);
        buffer_mat[shifted.i][shifted.j] = mat[cur.i][cur.j];
        cur = rotate(n, cur, 1);
    }
    
    print_matrix(n, (int (*)[n]) buffer_mat);
}

void input_matrix(size_t n, int (*mat)[n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
}

void print_matrix(size_t n, int (*mat)[n]) {
    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < n; ++column) {
            printf("%02d ", mat[row][column]);
        }
        putchar('\n');
    }
}

int main(void) {
    size_t n;
    scanf("%zu\n", &n);
    int mat[N * N];
    input_matrix(n, (int (*)[n]) mat);
    cyclic_shift(n, (int (*)[n]) mat);
    return 0;
}