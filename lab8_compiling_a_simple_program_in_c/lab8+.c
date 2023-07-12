#include <stdio.h>
#include <string.h>

int transform(char str[]) {
    int total = 0, len = strlen(str);
    for (int i = 0; i < len; ++i) {
        total *= 26;
        total += (str[i] - 'A' + 1);
    }
    return total;
}

int main(void) {
    char str[10];
    scanf("%s", str);
    printf("%d\n", transform(str));
    return 0;
}