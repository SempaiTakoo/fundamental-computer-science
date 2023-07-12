#include <stdio.h>
#include <float.h>
#include <math.h>
#include <assert.h>

#define MAX_ITER_COUNT (100)
#define K (1.0)

typedef struct {
    double sum;
    int iters_count;
} Taylor;

double epsilon(void) {
    double eps = 1.0;
    while (eps + 1.0 > 1.0) {
        eps /= 2.0;
    }
    return eps;
}

Taylor taylor_pow(double func_arg) {
    Taylor res;
    res.sum = 0.0;
    res.iters_count = 1;
    double ln3 = log(3), n = 1.0, term = 1.0, x = func_arg, error = epsilon() * K;
    
    if (res.sum + term == res.sum) {
        return res;
    }
    res.sum += term;
    for (int i = 1; (i < MAX_ITER_COUNT) && (term > error); ++i) {
        ++res.iters_count;
        term = (ln3 / n) * x;
        if (res.sum + term == res.sum) break;
        ln3 *= log(3);
        n *= i + 1;
        x *= func_arg;
        res.sum += term;
    }
    return res;
}

void print_table(double a, double b, int n) {
    double step = (b - a) / n, x;
    printf("      x          pow   taylor_pow  i\n");
    for (int i = 0; i < n; ++i) {
        x = a + i * step;
        printf("%.5lf %.10lf %.10lf %d \n", x, pow(3, x), taylor_pow(x).sum, taylor_pow(x).iters_count);
    }
}

int main(void) {
    const double a = 0.0, b = 1.0;
    const int n = 10;
    print_table(a, b, n);
    return 0;
}