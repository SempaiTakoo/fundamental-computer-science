#include <stdio.h>

typedef enum {
    OUTSIDE,
    NUM,
    LEADING_ZERO
} State;

void transfer(void);

int main(void) {
    transfer();
    return 0;
}

void transfer(void) {
    int count = 0;
    State status = OUTSIDE;
    for (char s = getchar(); s != EOF; s = getchar()) {
        switch (status) {
            case OUTSIDE:
                if (!isdigit(s)) {
                    putchar(s);
                    break;
                }
                if (s != '0') {
                    putchar(s);
                    status = NUM;
                    break;
                }
                // fallthrough
            case LEADING_ZERO:
                if (s == '0') {
                    ++count;
                    break;
                }
                if (!isdigit(s)) {
                    while (count > 0) {
                        putchar('0');
                        --count;
                    }
                    putchar(s);
                    break;
                }
                // fallthrough
            case NUM:
                if (isdigit(s)) {
                    putchar(s);
                    break;
                }
                while (count > 0) {
                    putchar('0');
                    --count;
                }
                putchar(s);
        }
    }
}