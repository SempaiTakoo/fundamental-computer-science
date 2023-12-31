# Отчёт по лабораторной работе №11 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 13</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>«26» ноября 2022 г.</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>5 (отлично)</ins>

<b>Отчёт сдан</b> «26» <ins>ноября</ins> <ins>2022</ins> г., <b>итоговая оценка</b> <ins>5 (отлично)</ins>

<b>Подпись преподавателя:</b> ________________


## 1. Тема:  
Обработка последовательности литер входного текстового файла. Простейшие приёмы лексического анализа. Диаграммы состояний и переходов.

## 2. Цель работы:  
Составить программу на языке Си, выполняющую анализ и обработку вводимого текста.

## 3. Задание:  
Ко всем допустимым числам прибавить ведущие нули.

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
Необходимо чтение строки. В ходе выполнения программы требуется сохранять цифры в специальной переменной целочисленного типа. В конце слова следует учесть два слуая:
- если текущее слово является нечислом, то вывести сохранившиеся цифры и далее следующие символы,
- если текущее слово является числом, то вывести ноль, а затем сохранившиеся цифры.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]. 
- Просмотреть демонстрационный материал в лабораторной аудитории
- Написать программу:
~~~c
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
~~~

##### Тесты.
lab11_test1.txt
~~~
1234
wasd
~~~

lab11_test2.txt
~~~
&1231
1234wasd
~~~

lab11_test3.txt
~~~
0
00
~~~

lab11_test4.txt
~~~
  123 123  123   123
(98) ( 2348 )
-2347987
-29384&
~~~

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола.
~~~powershell
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> gcc -Wall -pedantic -std=c99 lab11.c -o lab11.exe
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab11_test1.txt | ./lab11.exe
01234
wasd
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab11_test2.txt | ./lab11.exe
&1231
1234wasd
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab11_test3.txt | ./lab11.exe
0
00
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> Get-Content lab11_test4.txt | ./lab11.exe
0123 0123  0123   0123
(98) ( 02348 )
-02347987
-29384&
~~~

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 26.11.22 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
Отсутствуют.

## 11. Выводы
Была составлена программа на языке Си, выполняющая анализ и обработку вводимого текста. В ходе выполнения задания были освоены навыки работы с оператором `switch` и перечисляемым типом данных `enum`. Были изучены основы написания более читаемого кода.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________