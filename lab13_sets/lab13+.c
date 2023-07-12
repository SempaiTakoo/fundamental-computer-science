#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void *memset();

typedef unsigned set_data_elem;
enum {
    bits_per_char = 8,
    bits_per_elem = sizeof(set_data_elem) * bits_per_char,
    datalen = (1 << bits_per_char) / bits_per_elem
};

typedef struct {
    set_data_elem data[datalen];
} set;

void set_clear(set *s) {
    memset(s->data, 0, sizeof(s->data));
}

void set_insert(set *s, int c) {
    s->data[c / bits_per_elem] |= 1u << (c % bits_per_elem);
}

bool set_in(const set *s, int c) {
    return (s->data[c / bits_per_elem] & (1u << c % bits_per_elem)) != 0;
}

void set_generate(set *s, bool indicator(int)) {
    set_clear(s);
    for (int i = 0; i != 1 << bits_per_char; ++i) {
        if (indicator(i)) {
            set_insert(s, i);
        }
    }
}

bool set_includes(const set *s1, const set *s2) {
    for (int i = 0; i != datalen; ++i) {
        if ((s1->data[i] | s2->data[i]) != s1->data[i]) {
            return false;
        }
    }
    return true;
}

set set_union(const set *s1, const set *s2) {
    set result;
    for (int i = 0; i != datalen; ++i) {
        result.data[i] = s1->data[i] | s2->data[i];
    }
    return result;
}

set set_intersection(const set *s1, const set *s2) {
    set result;
    for (int i = 0; i != datalen; ++i) {
        result.data[i] = s1->data[i] & s2->data[i];
    }
    return result;
}

void fill_consonants(set *s) {
    set_insert(s, 'b');
    set_insert(s, 'c');
    set_insert(s, 'd');
    set_insert(s, 'f');
    set_insert(s, 'g');
    set_insert(s, 'h');
    set_insert(s, 'j');
    set_insert(s, 'l');
    set_insert(s, 'k');
    set_insert(s, 'm');
    set_insert(s, 'n');
    set_insert(s, 'p');
    set_insert(s, 'q');
    set_insert(s, 'r');
    set_insert(s, 's');
    set_insert(s, 't');
    set_insert(s, 'v');
    set_insert(s, 'w');
    set_insert(s, 'x');
    set_insert(s, 'z');
}

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
    set chars_pool, cur_chars, consonants;
    fill_consonants(&consonants);
    set_clear(&chars_pool);
    set_clear(&cur_chars);
    for (char s = getchar(); s != EOF; s = getchar()) {
        state = get_state(s);
        switch (state) {
            case INSIDE:
                more_than_one_char = true;
                if (set_in(&consonants, s)) {
                    if (first_word == true) {
                        set_insert(&chars_pool, s);
                    } else {
                        set_insert(&cur_chars, s);
                    }
                }
                break;
            case OUTSIDE:
                if (more_than_one_char == true) {
                    if (first_word == true) {
                        first_word = false;
                    } else {
                        chars_pool = set_intersection(&chars_pool, &cur_chars);
                        set_clear(&cur_chars);
                    }
                    more_than_one_char = false;
                }
                break;
        }
    }
    for (int i = 0; i < datalen; ++i) {
        if (chars_pool.data[i] != 0) {
            return true;
        }
    }
    return false;
}


int main(void) {
    printf("%d", common_cons());
    return 0;
}