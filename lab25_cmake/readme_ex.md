# Отчёт по лабораторной работе №25 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 11</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>08.04.23</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>5 (отлично)</ins>

<b>Отчёт сдан</b> «8» <ins>апреля</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins>5 (отлично)</ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема:
Автоматизация сборки программ модульной структуры на языке Си с использованием утилиты make

## 2. Цель работы:
Получение навыков автоматизации сборки программ модульной структуры

## 3. Задание:
Составить Makefile для модульной программы из лабораторной работы №26

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
1. Изучить принципы работы утилиты make по книгам или данному руководству.
2. Составить Makefile для модульной программы из лабораторной работы №26.
3. Оттестировать Makefile и убедиться в его работоспособности для различных ситуаций.
4. Распечатать протокол с текстом Makefile и результат его работы в несколькхи различных ситуациях с исходными объектными файлами (не менее, чем в трёх).

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]:
```makefile
CC=gcc
RM=rm -f
CFLAGS=-Wall -pedantic -std=c18
SOURCES=main.c stack.c sort.c
OBJECTS=main.o stack.o sort.o
TARGET=main.exe

all: ${SOURCES} $(TARGET)

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола:
__Makefile:__
```Makefile
CC=gcc
RM=rm -f
CFLAGS=-Wall -pedantic -std=c18
SOURCES=main.c stack.c sort.c
OBJECTS=main.o stack.o sort.o
TARGET=main.exe

all: ${SOURCES} $(TARGET)

${TARGET}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
```

__Powershell:__
```powershell
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> ls


    Каталог: C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main


Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----        07.04.2023     21:25            631 main.c
-a----        07.04.2023     21:25            259 Makefile
-a----        07.04.2023     21:25           1211 sort.c
-a----        07.04.2023     21:24            234 sort.h
-a----        07.04.2023     19:25           1980 stack.c
-a----        07.04.2023     14:57            351 stack.h


PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> make all
gcc -Wall -pedantic -std=c18 -c main.c -o main.o
gcc -Wall -pedantic -std=c18 -c stack.c -o stack.o
gcc -Wall -pedantic -std=c18 -c sort.c -o sort.o
gcc -Wall -pedantic -std=c18 main.o stack.o sort.o -o main.exe
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> ./main.exe
---------------
value = 1, key = 6
value = 5, key = 6
value = 9, key = 4
value = 4, key = 2
value = 8, key = 6
---------------
value = 4, key = 2
value = 9, key = 4
value = 1, key = 6
value = 5, key = 6
value = 8, key = 6
---------------
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> ls


    Каталог: C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main


Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----        07.04.2023     21:25            631 main.c
-a----        08.04.2023     10:11          85624 main.exe
-a----        08.04.2023     10:11           1478 main.o
-a----        07.04.2023     21:25            259 Makefile
-a----        07.04.2023     21:25           1211 sort.c
-a----        07.04.2023     21:24            234 sort.h
-a----        08.04.2023     10:11           1437 sort.o
-a----        07.04.2023     19:25           1980 stack.c
-a----        07.04.2023     14:57            351 stack.h
-a----        08.04.2023     10:11           1633 stack.o


PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> rm sort.o
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> ls


    Каталог: C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main


Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----        07.04.2023     21:25            631 main.c
-a----        08.04.2023     10:11          85624 main.exe
-a----        08.04.2023     10:11           1478 main.o
-a----        07.04.2023     21:25            259 Makefile
-a----        07.04.2023     21:25           1211 sort.c
-a----        07.04.2023     21:24            234 sort.h
-a----        07.04.2023     19:25           1980 stack.c
-a----        07.04.2023     14:57            351 stack.h
-a----        08.04.2023     10:11           1633 stack.o


PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> make
gcc -Wall -pedantic -std=c18 -c sort.c -o sort.o
gcc -Wall -pedantic -std=c18 main.o stack.o sort.o -o main.exe
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> ./main.exe
---------------
value = 1, key = 6
value = 5, key = 6
value = 9, key = 4
value = 4, key = 2
value = 8, key = 6
---------------
value = 4, key = 2
value = 9, key = 4
value = 1, key = 6
value = 5, key = 6
value = 8, key = 6
---------------
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> notepad main.c
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> make
gcc -Wall -pedantic -std=c18 -c main.c -o main.o
gcc -Wall -pedantic -std=c18 main.o stack.o sort.o -o main.exe
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab25_make\main> ./main.exe
value = 1, key = 6
value = 5, key = 6
value = 9, key = 4
value = 4, key = 2
value = 8, key = 6
---------------
value = 4, key = 2
value = 9, key = 4
value = 1, key = 6
value = 5, key = 6
value = 8, key = 6
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы:

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 08.04.23| 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
- [Решённый контест](https://codeforces.com/contest/1798/my)

## 11. Выводы
Было выяснено, что утилита make существенно упрощяет процесс сборки модульных программ. Благодаря заранее написанным сценариям работы и компиляции только изменённых частей программы возможна удобная и быстрая линковка одной командой.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________