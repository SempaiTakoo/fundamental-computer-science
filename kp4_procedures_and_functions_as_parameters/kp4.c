#include <stdio.h>
#include <math.h>
#include <assert.h>

#define E (0.000001)

// F(x) = lnx - x + 1.8
// f(x) = lnx + 1.8 
// f'(x) = 1/x

double f(double x) {
    return log(x) + 1.8;
}

double f_der(double x) {
    return 1/x;
}

double iteration_method(double a, double b, double x0, double (*f)(double), double (*f_der)(double)) {
    double x1 = f(x0), x2 = f(x1);

    assert(abs(f_der(x0)) < 1);
    if (abs(x0 - x1) < E) {
        return x1;
    }
    while ((x1 > a) && (x1 < b) && (x2 > a) && (x2 < b)) {
        assert(abs(f_der(x1)) < 1);
        assert(abs(f_der(x2)) < 1);
        if (abs(x1 - x2) < E) {
            return x1;
        }
        x1 = x2;
        x2 = f(x2);
    }
    return NAN;
}

int main(void) {
    double a = 2.0, b = 3.0, x0 = 2.8459;
    printf("%lg", iteration_method(a, b, x0, f, f_der));
    return 0;
}