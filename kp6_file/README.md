# Отчёт по курсовому проекту №6 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 11</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>23.06.23</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>удовл.</ins>

<b>Отчёт сдан</b> «23» <ins>июнь</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins>3</ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема:
Обработка последовательной файловой структуры на языке Си

## 2. Цель работы:
Разработать последовательную структуру данных для представления простейшей базы данных на
файлах в СП Си в соответствии с заданным вариантом

## 3. Задание:
##### Содержимое и структура файла:
Информация об успеваемости студентов данной группы по всем предметам: фамилия, инициалы, пол,
номер группы, отметки по экзаменам.
##### Действие:
Выяснить, сколько студентов группы p имеют больше двух троек.

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

## 6. Идея, метод, алгоритм решения задачи (в формах: словесной, псевдокода, графической [блок-схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями):
Необходимо реализовать структуру, являющуюся представлением данных о конкретном студенте. Далее требуется реализовать хранение в бинарном виде.
Также нужно написать программу для печати данных и выполнения действия по варианту.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]:
Makefile
```
CC=gcc
RM=rm -f
CFLAGS=-Wall -pedantic -std=c18
SOURCES=main.c student.c
OBJECTS=main.o student.o
TARGET=main.exe

all: ${SOURCES} $(TARGET)

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} *.o ${TARGET}
```
student.h
```
#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

#define LINE_SIZE (20)

typedef struct {
    char lastName[LINE_SIZE];
    char firstMiddle[2];
    int gender;
    int group;
    int marks[5];
} Student;

#endif
```
student.c
```
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "student.h"

bool readBase(Student *student, FILE *file) {
	char charGender;
	int res = fscanf(file, "%[^;];%c%c;%c;%d;%d;%d;%d;%d;%d\n",
                           student->lastName,
						   &student->firstMiddle[0],
						   &student->firstMiddle[1],
						   &charGender,
						   &student->group,
						   &student->marks[0],
						   &student->marks[1],
						   &student->marks[2],
						   &student->marks[3],
						   &student->marks[4]);
	if (res == 10) {
		if (charGender == 'M')
			student->gender = 0;
		else
			student->gender = 1;
		return true;
	}
	return false;
}

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");

	if (argc != 3) {
		printf("Input error\n");
		return 1;
	}
	Student student;
	memset(&student, '0', sizeof(Student));
	FILE *base = fopen(argv[1], "r");
	if (!base) {
		perror("Can't open the file\n");
		return 2;
	}
	FILE *bin = fopen(argv[2], "w");
	if (!bin) {
		perror("Can't open the file\n");
		fclose(base);
		return 2;
	}
	while (readBase(&student, base)) {
		fwrite(&student, sizeof(Student), 1, bin);
	}
	fclose(bin);
	fclose(base);
	return 0;
}
```
main.c
```
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale.h>
#include <stdbool.h>

#include "student.h"

char *stringComplement(char *str, int n) {
    int len = strlen(str);
    for (int ptr = len; ptr < n; ptr++) {
        str[ptr] = ' ';
        str[ptr + 1] = '\0';
    }
    return str;
}

void printBlank(int n) {
    for (int i = 0; i < n; i++)
        putchar(' ');
}

char* intToString(int val, int base) {
	static char buf[32] = {0};
    if (val == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }
	int i = 30;
    buf[31] = '\0';
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}

//20|8|3|12|7|7|7|7|7|
const char * HEADER = "|Last Name           |Initials|Gen|Group number|Mark 1 |Mark 2 |Mark 3 |Mark 4 |Mark 5 |\n";
const char * DELIM =  "|--------------------|--------|---|------------|-------|-------|-------|-------|-------|\n";

void printUsage() {
    printf("main <filename> -f - printing a table\n");
    printf("main <filename> -p <p> - calculating a function by task\n");
}

void studentPrint(Student *student) {
    putchar('|');
    char lastName[21];
    strcpy(lastName, student->lastName);
    printf("%s", stringComplement(lastName, 20));
    putchar('|');
    printf("%c%c      ", student->firstMiddle[0], student->firstMiddle[1]);
    putchar('|');
    char charStudentGender;
    if (student->gender)
        charStudentGender = 'M';
    else
        charStudentGender = 'F';
    printf("%c  ", charStudentGender);
    putchar('|');
    char *group = intToString(student->group, 10);
    printf("%s", stringComplement(group, 12));
    putchar('|');
    char mark1[8];
    strcpy(mark1, intToString(student->marks[0], 10));
    printf("%s", stringComplement(mark1, 7));
    putchar('|');
    char mark2[8];
    strcpy(mark2, intToString(student->marks[1], 10));
    printf("%s", stringComplement(mark2, 7));
    putchar('|');
    char mark3[8];
    strcpy(mark3, intToString(student->marks[2], 10));
    printf("%s", stringComplement(mark3, 7));
    putchar('|');
    char mark4[8];
    strcpy(mark4, intToString(student->marks[3], 10));
    printf("%s", stringComplement(mark4, 7));
    putchar('|');
    char mark5[8];
    strcpy(mark5, intToString(student->marks[4], 10));
    printf("%s", stringComplement(mark5, 7));
    putchar('|');   
    putchar('\n');
}

void printTable(FILE *file) {
    Student student;
    printf("%s", HEADER);
    printf("%s", DELIM);
    while (fread(&student, sizeof(Student), 1, file) == 1) {
        studentPrint(&student);
    }
    printf("%s", DELIM);
}

void func(FILE *file, int p) {
    Student student;
    int studcount = 0;
    int markscount;
    while (fread (&student, sizeof(Student), 1, file) == 1) {
        if (student.group != p)
            continue;
        markscount = 0;
        for (int i = 0; i < 5; ++i) {
            if (student.marks[i] == 3)
                ++markscount;
        }
        if (markscount > 2)
            ++studcount;
    }
    printf("The number of students with the number of triples greater than 2 in the group %d: %d", p, studcount);
}

int main(int argc, char **argv) {
    setlocale(LC_ALL, "Rus");

    if (argc == 1) {
        printUsage();
        return 0;
    }
    int p = -1; 
    int mode = 0; 
    bool wasFilename = false;
    bool wasPreviousP = false;
    char filename[40];
    for (int i = 1;i < argc;i++) {
        if (strcmp(argv[i], "-f") == 0) {
            if (mode == 0)
                mode = 1;
            else
                mode = 3;
        } else if (strcmp(argv[i], "-p") == 0) {
            wasPreviousP = true;
        } else if (wasPreviousP) {
            if (mode == 0)
                mode = 2;
            else
                mode = 3;
            p = atoi(argv[3]);
        } else {
            wasFilename = true;
            strcpy(filename, argv[i]);
        }
        if (wasPreviousP && strcmp(argv[i], "-p") != 0)
            wasPreviousP = false;
    }
    if (wasFilename && mode == 1) {
        FILE *bin = fopen(filename, "r");
        if (bin)
            printTable(bin);
        else
            printf("Input error\n");
        fclose(bin);
    } else if (wasFilename && mode == 2) {
        FILE *bin = fopen(filename, "r");
        if (bin)
            func(bin, p);
        else
            printf("Input error\n");
        fclose(bin);
    } else {
        printUsage();
    }

    return 0;
}
```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола:
```
idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp6
$ make student
gcc   student.o   -o student

idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp6
$ ./student.exe data.txt data_bin

idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp6
$ make main
gcc -Wall -pedantic -std=c18 -c main.c -o main.o
gcc   main.o   -o main

idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp6
$ ./main.exe
main <filename> -f - printing a table
main <filename> -p <p> - calculating a function by task

idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp6
$ ./main.exe data_bin -f
|Last Name           |Initials|Gen|Group number|Mark 1 |Mark 2 |Mark 3 |Mark 4 |Mark 5 |
|--------------------|--------|---|------------|-------|-------|-------|-------|-------|
|Margaret            |AA      |M  |101         |5      |4      |4      |5      |2      |
|Sue                 |BB      |F  |101         |4      |2      |3      |3      |3      |
|Deborah             |CC      |M  |101         |4      |5      |4      |3      |2      |
|Matthew             |DD      |F  |101         |3      |5      |2      |2      |2      |
|Ricky               |FF      |F  |101         |3      |4      |4      |5      |3      |
|Sara                |GG      |M  |102         |2      |5      |4      |3      |4      |
|Donna               |HH      |M  |102         |4      |4      |4      |5      |3      |
|Marie               |II      |M  |102         |4      |4      |3      |4      |4      |
|Anne                |JJ      |M  |102         |5      |2      |4      |3      |3      |
|Gary                |KK      |F  |103         |4      |4      |5      |2      |3      |
|Bruce               |LL      |F  |103         |2      |2      |4      |5      |2      |
|Gladys              |MM      |F  |103         |3      |4      |2      |4      |3      |
|William             |OO      |F  |104         |3      |3      |2      |4      |2      |
|Alan                |PP      |F  |104         |4      |4      |4      |3      |4      |
|Gina                |QQ      |M  |104         |4      |5      |5      |2      |5      |
|Debra               |RR      |M  |104         |5      |4      |5      |2      |4      |
|Wayne               |SS      |F  |105         |3      |5      |2      |2      |3      |
|Diana               |TT      |M  |105         |3      |2      |2      |5      |4      |
|David               |VV      |F  |105         |2      |3      |5      |2      |2      |
|--------------------|--------|---|------------|-------|-------|-------|-------|-------|

idl76@takoo_desktop /cygdrive/c/Users/idl76/Рабочий стол/fundamental-computer-science-sempaitakoo/kp6
$ ./main.exe data_bin -p 101
The number of students with the number of triples greater than 2 in the group 101: 1
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы:

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 23.06.23 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
- [Решённый контест](https://codeforces.com/submissions/SempaiTakoo/contest/1841)

## 11. Выводы
Были получены навыки работы с файловыми структуруми и бинарным кодом в Си. Также были получены навыки реализоации пользовательского интерфейса.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________