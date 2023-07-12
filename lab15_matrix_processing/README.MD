# Отчёт по лабораторной работе №15 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 13</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>«3» декабря 2022 г.</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>5 (отлично)</ins>

<b>Отчёт сдан</b> «3» <ins>декабря</ins> <ins>2022</ins> г., <b>итоговая оценка</b> <ins>5 (отлично)</ins>

<b>Подпись преподавателя:</b> ________________


## 1. Тема:
Обработка матриц.

## 2. Цель работы:
Составление программы на языке Си, производящую обработку квадратной матрицы из целых чисел, вводимой из стандартного входного текстового файла.

## 3. Задание:
Циклический сдвиг элементов матрицы по спирали против часовой стрелки на 8 элементов.

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
Необходимо написать функцию, определяющую положение сдвига элементов в зависимости от количества шагов. Имеются две матрицы: исходная и конечная. Для каждого элемента исходной матрицы определить новое положение, т.е. индексы. По этим индексам ввести значения этих элементов уже в конечную матрицу. Далее вывести конечную матрицу.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]. 
- Просмотреть демонстрационный материал в лабораторной аудитории
- Написать программу:
~~~c
#include <stdio.h>

#define N (7)

typedef enum {
    RIGHT,
    UP,
    LEFT,
    DOWN
} Direction;

typedef struct {
    int i, j;
    Direction direction;
    int step_size;
    int step_count;

} Element;

void print_matrix();

Element rotate(size_t n, Element elem, int count) {
    for (int k = 0; k < count; ++k) {
        if ((elem.i == n - 1) && (elem.j == n - 1)) {
            elem.i = n / 2;
            elem.j = n / 2 + n % 2 - 1;
            elem.direction = RIGHT;
            elem.step_size = 1;
            elem.step_count = 0;
            continue;
        }
        if (elem.direction == RIGHT) ++elem.j;
        if (elem.direction == UP) --elem.i;
        if (elem.direction == LEFT) --elem.j;
        if (elem.direction == DOWN) ++elem.i;
        ++elem.step_count;
        if (elem.step_count % elem.step_size == 0) {
            elem.direction = elem.direction == DOWN ? RIGHT : elem.direction + 1;
        }
        if (elem.step_count == elem.step_size * 2) {
            ++elem.step_size;
            elem.step_count = 0;
        }
    }
    return elem;
}

void cyclic_shift(size_t n, int (*mat)[n]) {
    int buffer_mat[n][n];
    Element cur;
    Element shifted;
    cur.i = n / 2;
    cur.j = n / 2 + n % 2 - 1;
    cur.direction = RIGHT;
    cur.step_size = 1;
    cur.step_count = 0;

    for (int k = 0; k < n * n; ++k) {
        shifted = rotate(n, cur, 8);
        buffer_mat[shifted.i][shifted.j] = mat[cur.i][cur.j];
        cur = rotate(n, cur, 1);
    }
    
    print_matrix(n, (int (*)[n]) buffer_mat);
}

void input_matrix(size_t n, int (*mat)[n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
}

void print_matrix(size_t n, int (*mat)[n]) {
    for (int row = 0; row < n; ++row) {
        for (int column = 0; column < n; ++column) {
            printf("%02d ", mat[row][column]);
        }
        putchar('\n');
    }
}

int main(void) {
    size_t n;
    scanf("%zu\n", &n);
    int mat[N * N];
    input_matrix(n, (int (*)[n]) mat);
    cyclic_shift(n, (int (*)[n]) mat);
    return 0;
}
~~~

##### Тесты.

lab15_test1.txt
~~~
3
00 01 02 
10 11 12 
20 21 22 
~~~

lab15_test1.txt
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
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> gcc -Wall -pedantic -std=c99 lab15.c -o lab15.exe
PS C:\Users\idl76\Desktop\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab15_test1.txt | ./lab15.exe
04 01 02
07 06 03
08 09 05
PS C:\Users\idl76\Desktop\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab15_test2.txt | ./lab15.exe
33 32 31 21 11
34 41 40 30 12
24 42 10 20 13
14 43 44 22 23
04 03 02 01 00
~~~

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 03.12.22 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
Дополнительное задание:  
Для матрицы порядка N <= 8 вычислить максимальный минор третьего порядка.
##### Программа:
~~~c
#include <stdio.h>
#include <limits.h>

#define N (8)

void matrix_print(size_t n, int (*mat)[n]);

typedef struct {
    int i0;
    int i1;
    int i2;
    int j0;
    int j1;
    int j2;
} Indexes;

int determinant(size_t n, int (*mat)[n], Indexes ind) {
    return mat[ind.i0][ind.j0]*mat[ind.i1][ind.j1]*mat[ind.i2][ind.j2] \
         + mat[ind.i0][ind.j1]*mat[ind.i1][ind.j2]*mat[ind.i2][ind.j0] \
         + mat[ind.i0][ind.j2]*mat[ind.i1][ind.j0]*mat[ind.i2][ind.j1] \
         - mat[ind.i0][ind.j2]*mat[ind.i1][ind.j1]*mat[ind.i2][ind.j0] \
         - mat[ind.i0][ind.j0]*mat[ind.i1][ind.j2]*mat[ind.i2][ind.j1] \
         - mat[ind.i0][ind.j1]*mat[ind.i1][ind.j0]*mat[ind.i2][ind.j2];
}

void matrix_print_max_minor(size_t n, int (*mat)[n]) {
    int max_d = INT_MIN;
    Indexes ind;
    for (ind.i0 = 0; ind.i0 < n; ++ind.i0) {
        for (ind.i1 = ind.i0 + 1; ind.i1 < n; ++ind.i1) {
            for (ind.i2 = ind.i1 + 1; ind.i2 < n; ++ind.i2) {
                for (ind.j0 = 0; ind.j0 < n; ++ind.j0) {
                    for (ind.j1 = ind.j0 + 1; ind.j1 < n; ++ind.j1) {
                        for (ind.j2 = ind.j1 + 1; ind.j2 < n; ++ind.j2) {
                            if (determinant(n, mat, ind) > max_d) {
                                max_d = determinant(n, mat, ind);
                            }
                        }
                    }
                }
            }
        }
    }
    printf("%d", max_d);
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
    matrix_print_max_minor(n, (int (*)[n]) mat);
    return 0;
}
~~~

##### Тесты.
lab15+_test1.txt
~~~
4
1 2 0 5
2 4 -1 0
-2 -4 1 0
1 0 2 1
~~~

lab15+_test2.txt
~~~
5
01 01 02 03 04 
10 11 12 13 14 
20 21 22 23 24 
30 31 32 33 34 
40 41 42 43 440 
~~~

##### Распечатка протокола:
~~~powershell
PS C:\Users\idl76\Desktop\fundamental-computer-science-sempaitakoo\workshop> gcc -Wall -pedantic -std=c99 lab15+.c -o lab15+.exe
PS C:\Users\idl76\Desktop\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab15+_test1.txt | ./lab15+.exe
38
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab15+_test2.txt | ./lab15+.exe
366
~~~

## 11. Выводы
Были составлены программы на язык Си, производящие обработку квадратной матрицы из целых чисел, вводимой из стандартного входного текстового файла. В ходе выполнения заданий были расширены навыки работы с матрицами, а также указателями.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________