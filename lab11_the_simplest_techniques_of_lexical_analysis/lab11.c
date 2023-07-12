#include <stdio.h>

typedef enum {
    NUM,
    NOT_NUM
} State;

int isdigit();

void leading_zero(void) {
    State status = NUM;
    long cur_n = 0;
    for (char s = getchar(); s != EOF; s = getchar()) {
        switch (status) {
            case NUM:
                if ((s == '0') || (s == '+') || (s == '-')) {
                    putchar(s);
                    break;
                }
                if (((s == '\n') || (s == ' ')) && (cur_n != 0)) {
                    printf("0%ld", cur_n);
                    putchar(s);
                    cur_n = 0;
                    break;
                }
                if (!isdigit(s)) {
                    if (cur_n != 0) printf("%ld", cur_n);
                    if (s != ' ') status = NOT_NUM;
                    putchar(s);
                    break;
                }
                cur_n = cur_n * 10 + (int) s - 48;
                break;
            case NOT_NUM:
                putchar(s);
                if ((s == '\n') || (s == ' ')) {
                    cur_n = 0;
                    status = NUM;
                }
                break;
        }
    }
}

int main(void) {
    leading_zero();
    return 0;
}