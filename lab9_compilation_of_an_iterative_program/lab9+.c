#include <stdio.h>

int sign(int n) {
	return n > 0 ? 1 : n < 0 ? -1 : 0;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int abs(int a) {
	return a >= 0 ? a : -a;
}

typedef struct {
    int i;
    int j;
    int l;
} Point;

typedef struct {
    int a;
    int i;
    int j;
} Square;

int is_in_square(Square square, Point point) {
    return (abs(point.i + square.i) <= (square.a / 2)) && (abs(point.j + square.j) <= (square.a / 2));
}

Point move(Point prev, int k) {
    Point next;
    next.i = (abs(max(prev.i*(k + 5), prev.j*(k + 6))) - abs(min(prev.j*(k + 7), prev.l*(k + 8)))) % 20;
    next.j = (3 - sign(prev.i - prev.j)) * abs(min(prev.i*prev.l + 5, prev.j*prev.l - 3*prev.i*prev.j + 6)) % 25 - 7;
    next.l = prev.i % 10 + prev.j % 10 + prev.l % 10;
    return next;
}

int main(void) {
    Point point = {20, 10, -1};
    Square square = {10, 10, -10};
    for (int k = 0; k < 51; ++k) {
        printf("k = %d, i = %d, j = %d, l = %d \n", k, point.i, point.j, point.l);
        if (is_in_square(square, point)) {
            printf("Hit! k = %d, i = %d, j = %d, l = %d \n", k, point.i, point.j, point.l);
            break;
        }
        if (k == 50) {
            printf("Missing! i = %d, j = %d, l = %d \n", point.i, point.j, point.l);
        }
        point = move(point, k);
    }
    return 0;
}