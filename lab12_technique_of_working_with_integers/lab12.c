#include <stdio.h>

int main(void) {
    char ch;
    int count = 0;
    while ((ch = getchar()) == '0') ++count;
    putchar(ch);
    while ((ch = getchar()) != '\n') putchar(ch);
    while (count > 0) {
        putchar('0');
        count -= 1;
    }
}