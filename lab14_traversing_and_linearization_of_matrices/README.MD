# Отчёт по лабораторной работе №14 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 13</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>«3» декабря 2022 г.</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>5 (отлично)</ins>

<b>Отчёт сдан</b> «3» <ins>декабря</ins> <ins>2022</ins> г., <b>итоговая оценка</b> <ins>5 (отлично)</ins>

<b>Подпись преподавателя:</b> ________________


## 1. Тема:
Вложенные циклы с параметрами. Обход и линеаризация матриц.

## 2. Цель работы:
Написание программы ввода квадратной матрицы и печати в строку всех её элементов в заданном порядке обхода.

## 3. Задание:
Написать программу для обхода матрицы змейкой с левого верхнего угла до правого нижнего.

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
Необходимо написать цикл, который будет постепенно считывать элементы матрицы. Требуется регулировать значения индексов i, j, чтобы выводить элементы змейкой и не выходить за пределы матрицы. Заметим, что условия выхода за пределы матрицы до и после прохождения через побочную диагональ отличаются. Стало быть, нужно учесть два различных случая с разными условиями.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]. 
- Просмотреть демонстрационный материал в лабораторной аудитории
- Написать программу:
~~~c#include <stdio.h>
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
#include <stdio.h>

#define N (7)

typedef enum {
    AFTER_SIDE_DIAG,
    BEFORE_SIDE_DIAG
}   Location;

Location get_state(int i, int j, Location state, size_t n) {
    if (((i == n - 1) && (j == 0)) || ((j == n - 1) && (i == 0))) {
        state = AFTER_SIDE_DIAG;
    }
    return state;
}

void matrix_print(size_t n, int (*mat)[n]) {
    Location state = BEFORE_SIDE_DIAG;
    int direction = 1;
    int i = 0, j = 0;
    while ((i != n) && (j != n)) {
        printf("%02d ", mat[i][j]);
        state = get_state(i, j, state, n);
        switch(state) {
            case BEFORE_SIDE_DIAG:
                if ((j == 0) || (j == n - 1)) {
                    ++i;
                    direction *= -1;
                    printf("%02d ", mat[i][j]);
                    i = i + direction;
                    j = j - direction;
                    break;
                }
                if ((i == 0) || (i == n - 1)) {
                    ++j;
                    direction *= -1;
                    printf("%02d ", mat[i][j]);
                    i = i + direction;
                    j = j - direction;
                    break;
                }
                i = i + direction;
                j = j - direction;
                break;
            case AFTER_SIDE_DIAG:
                if (j == n - 1) {
                    ++i;
                    direction *= -1;
                    printf("%02d ", mat[i][j]);
                    i = i + direction;
                    j = j - direction;
                    break;
                }
                if (i == n - 1) {
                    ++j;
                    direction *= -1;
                    printf("%02d ", mat[i][j]);
                    i = i + direction;
                    j = j - direction;
                    break;
                }
                i = i + direction;
                j = j - direction;
                break;
        }
    }
}

void matrix_input(size_t n, int (*mat)[n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
}

int main(void) {
    size_t n;
    scanf("%zu", &n);
    int mat[N * N];
    matrix_input(n, (int (*)[n]) mat);
    matrix_print(n, (int (*)[n]) mat);
    return 0;
}
~~~

##### Тесты.
lab14_test1.txt
~~~
3
00 01 02 
10 11 12 
20 21 22 
~~~

lab14_test2.txt
~~~
4
00 01 02 03 
10 11 12 13 
20 21 22 23 
30 31 32 33 
~~~

lab14_test3.txt
~~~
5
00 01 02 03 04 
10 11 12 13 14 
20 21 22 23 24 
30 31 32 33 34 
40 41 42 43 44 
~~~

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола.
~~~powershell
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> gcc -Wall -pedantic -std=c99 lab14.c -o lab14.exe
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab14_test1.txt | ./lab14.exe
00 10 01 02 11 20 21 12 22
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab14_test2.txt | ./lab14.exe
00 10 01 02 11 20 30 21 12 03 13 22 31 32 23 33
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab14_test3.txt | ./lab14.exe
00 10 01 02 11 20 30 21 12 03 04 13 22 31 40 41 32 23 14 24 33 42 43 34 44
~~~

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 03.12.22 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
Дополнительное задание:  
Подаётся матрица порядка 2^n - 1. Требуется вывести элементы "плюсиком" (центральный элемент не дублируется). Затем сделать то же самое с элементами в углу и т. д.
##### Программа:
~~~c
#include <stdio.h>

#define N (127)

void matrix_print(int n, int (*mat)[n], int top, int bot, int left, int right) {
    int up_mid = left + (bot - top) / 2;
    int side_mid = top + (right - left) / 2;
    if (bot - top == 1) {
        printf("%d ", mat[top][left]);
        return;
    }
    for (int i = top; i < bot; ++i) {
        printf("%d ", mat[i][up_mid]);
    }
    for (int j = left; j < right; ++j) {
        if (j == up_mid) continue;
        printf("%d ", mat[side_mid][j]);
    }
    matrix_print(n, mat, top, side_mid, left, up_mid);
    matrix_print(n, mat, side_mid + 1, bot, left, up_mid);
    matrix_print(n, mat, side_mid + 1, bot, up_mid + 1, right);
    matrix_print(n, mat, top, side_mid, up_mid + 1, right);
}

void matrix_input(size_t n, int (*mat)[n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
}

int main(void) {
    int mat[N * N];
    size_t n;
    scanf("%zu\n", &n);
    matrix_input(n, (int (*)[n]) mat);
    matrix_print(n, (int (*)[n]) mat, 0, n, 0, n);
    return 0;
}
~~~

##### Тесты.
lab14+_test1.txt
~~~
3
00 01 02 
10 11 12 
20 21 22 
~~~

lab14+_test1.txt
~~~
7
00 01 02 03 04 05 06 
10 11 12 13 14 15 16 
20 21 22 23 24 25 26 
30 31 32 33 34 35 36 
40 41 42 43 44 45 46 
50 51 52 53 54 55 56 
60 61 62 63 64 65 66 
~~~

lab14+_test1.txt
~~~
15
00 01 02 03 04 05 06 07 08 09 010 011 012 013 014 
10 11 12 13 14 15 16 17 18 19 110 111 112 113 114 
20 21 22 23 24 25 26 27 28 29 210 211 212 213 214 
30 31 32 33 34 35 36 37 38 39 310 311 312 313 314 
40 41 42 43 44 45 46 47 48 49 410 411 412 413 414 
50 51 52 53 54 55 56 57 58 59 510 511 512 513 514 
60 61 62 63 64 65 66 67 68 69 610 611 612 613 614 
70 71 72 73 74 75 76 77 78 79 710 711 712 713 714 
80 81 82 83 84 85 86 87 88 89 810 811 812 813 814 
90 91 92 93 94 95 96 97 98 99 910 911 912 913 914 
100 101 102 103 104 105 106 107 108 109 1010 1011 1012 1013 1014 
110 111 112 113 114 115 116 117 118 119 1110 1111 1112 1113 1114 
120 121 122 123 124 125 126 127 128 129 1210 1211 1212 1213 1214 
130 131 132 133 134 135 136 137 138 139 1310 1311 1312 1313 1314 
140 141 142 143 144 145 146 147 148 149 1410 1411 1412 1413 1414 
~~~

##### Распечатка протокола.

~~~powershell
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> gcc -Wall -pedantic -std=c99 lab14+.c -o lab14+.exe
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab14+_test1.txt | ./lab14+.exe
1 11 21 10 12 0 20 22 2
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab14+_test2.txt | ./lab14+.exe
3 13 23 33 43 53 63 30 31 32 34 35 36 1 11 21 10 12 0 20 22 2 41 51 61 50 52 40 60 62 42 45 55 65 54 56 44 64 66 46 5 15 25 14 16 4 24 26 6
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab14+_test3.txt | ./lab14+.exe
7 17 27 37 47 57 67 77 87 97 107 117 127 137 147 70 71 72 73 74 75 76 78 79 710 711 712 713 714 3 13 23 33 43 53 63 30 31 32 34 35 36 1 11 21 10 12 0 20 22 2 41 51 61 50 52 40 60 62 42 45 55 65 54 56 44 64 66 46 5 15 25 14 16 4 24 26 6 83 93 103 113 123 133 143 110 111 112 114 115 116 81 91 101 90 92 80 100 102 82 121 131 141 130 132 120 140 142 122 125 135 145 134 136 124 144 146 126 85 95 105 94 96 84 104 106 86 811 911 1011 1111 1211 1311 1411 118 119 1110 1112 1113 1114 89 99 109 98 910 88 108 1010 810 129 139 149 138 1310 128 148 1410 1210 1213 1313 1413 1312 1314 1212 1412 1414 1214 813 913 1013 912 914 812 1012 1014 814 11 111 211 311 411 511 611 38 39 310 312 313 314 9 19 29 18 110 8 28 210 10 49 59 69 58 510 48 68 610 410 413 513 613 512 514 412 612 614 414 13 113 213 112 114 12 212 214 14
~~~

## 11. Выводы
Удалось написать программы ввода квадратной матрицы и печати в строку всех её элементов в заданном порядке обхода. В ходе работы опытным путём были изучены рекурсивные функции.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________