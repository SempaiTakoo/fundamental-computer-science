# Отчёт по лабораторной работе №13 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 13</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>«26» ноября 2022 г.</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>5 (отлично)</ins>

<b>Отчёт сдан</b> «26» <ins>ноября</ins> <ins>2022</ins> г., <b>итоговая оценка</b> <ins>5 (отлично)</ins>

<b>Подпись преподавателя:</b> ________________


## 1. Тема:
Множества.

## 2. Цель работы:
Составить программу проверки характеристик введенных последовательностей слов и печати развёрнутого ответа.

## 3. Задание:
Есть ли согласная, входящая в состав всех слов?

## 4. Оборудование:
<b>Процессор:</b> 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz<br/>
<b>ОП:</b> 8 ГБ <br/>
<b>SSD:</b> 256 ГБ<br/>

## 5. Программное обеспечение:
<b>Операционная система семейства:</b> Windows 11 10.0.22000 <br/>
<b>Интерпретатор команд:</b> Powershell 5.1.22000.832 <br/>
<b>Система программирования:</b> gcc.exe (GCC) 10.3.0 <br/>
<b>Текстовый редактор:</b> Visual Studio Code версия 1.73.1 <br/>
<b>Местонахождение и имена файлов программ и данных на домашнем компьютере:</b> C:\Users\idl76> <br/>

## 6. Идея, метод, алгоритм решения задачи (в формах: словесной, псевдокода, графической [блок-схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями).
Необходимо посимвольно считывать строку. Для первого слова требуется запомнить все его согласные буквы - `chars_pool`. Для последующих слов следует проверять наличие согласных букв, полученных из первого слова. Выводом программы будет выражение `chars_pool > 0`.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]. 
- Просмотреть демонстрационный материал в лабораторной аудитории
- Написать программу:
~~~c
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
~~~

##### Тесты.
lab13_test1.txt
~~~
aaaadddd aaaddd aaaadd
iiiiiiiiddd
~~~

lab13_test2.txt
~~~
aaaadddd aaaddd aaaa
iiiiiiiiddd
~~~

lab13_test3.txt
~~~
    aaaassssddd    asdddsa

    asdfddf
asdffg
~~~

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола.
<<<<<<< HEAD
lab13_input.txt
~~~
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaad
 aaaaaaaaaaaaaaaaaadd    aaaaaaaaaaaaaddddddddaaaaa                   ssaaaaaaaaaaaaaaaaaadddddddddaaaaaaaaaaaa
=======
~~~powershell
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> gcc -Wall -pedantic -std=c99 lab13.c -o lab13.exe
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab13_test1.txt | ./lab13.exe
1
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab13_test2.txt | ./lab13.exe
0
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab13_test3.txt | ./lab13.exe
1
~~~
## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 26.11.22 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
Дополнительное задание:  
Переделать программу с использованием более совершенного представления множеств.
##### Программа:
~~~c
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
~~~
>>>>>>> f823e75425ed7770325d4dc18196afa2d9278746

##### Тесты.
lab13+_test1.txt
~~~
aaaadddd aaaddd aaaadd
iiiiiiiiddd
~~~

lab13+_test2.txt
~~~
aaaadddd aaaddd aaaa
iiiiiiiiddd
~~~

lab13+_test3.txt
~~~
    aaaassssddd    asdddsa

    asdfddf
asdffg
~~~

~~~powershell
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> gcc -Wall -pedantic -std=c99 lab13+.c -o lab13+.exe
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab13+_test1.txt | ./lab13+.exe
1
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab13+_test2.txt | ./lab13+.exe
0
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab13+_test3.txt | ./lab13+.exe
1
~~~
<<<<<<< HEAD
## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 26.11.22 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
Дополнительное задание:

=======
>>>>>>> f823e75425ed7770325d4dc18196afa2d9278746

## 11. Выводы
Была составлена программа проверки характеристик введённых последовательностей слов и печати развёрнутого ответа. В ходе работы были освоены навыки работы со множествами в базовом и более совершенном представлениях.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________