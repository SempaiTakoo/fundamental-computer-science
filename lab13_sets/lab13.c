#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define CONSONANTS (1u << ('b' - 'a') | 1u << ('c' - 'a') | 1u << ('d' - 'a') | 1u << ('f' - 'a') | 1u << ('g' - 'a') | \
                    1u << ('h' - 'a') | 1u << ('j' - 'a') | 1u << ('k' - 'a') | 1u << ('l' - 'a') | 1u << ('m' - 'a') | \
                    1u << ('n' - 'a') | 1u << ('p' - 'a') | 1u << ('q' - 'a') | 1u << ('r' - 'a') | 1u << ('s' - 'a') | \
                    1u << ('t' - 'a') | 1u << ('v' - 'a') | 1u << ('w' - 'a') | 1u << ('x' - 'a') | 1u << ('z' - 'a'))

typedef enum {
    INSIDE,
    OUTSIDE
} State;

State get_state(char s) {
    return (s == ' ') || (s == '\n') || (s == ',') || (s == EOF) ? OUTSIDE : INSIDE;
}

bool common_cons(void) {
    State state;
    bool first_word = true, more_than_one_char = false;
    unsigned int chars_pool = 0, cur_chars = 0;
    for (char s = getchar(); s != EOF; s = getchar()) {
        state = get_state(s);
        switch (state) {
            case INSIDE:
                more_than_one_char = true;
                if (CONSONANTS & 1u << (s - 'a')) {
                    if (first_word == true) {
                        chars_pool = chars_pool | 1u << (s - 'a');
                    } else {
                        cur_chars = cur_chars | 1u << (s - 'a');
                    }
                }
                break;
            case OUTSIDE:
                if (more_than_one_char == true) {
                    if (first_word == true) {
                        first_word = false;
                    } else {
                        chars_pool = chars_pool & cur_chars;
                        cur_chars = 0;
                    }
                    more_than_one_char = false;
                }
                break;
        }
    }
    return chars_pool > 0;
}


int main(void) {
    printf("%d", common_cons());
    return 0;
}