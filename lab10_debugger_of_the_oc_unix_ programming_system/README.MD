# Отчёт по лабораторной работе №10 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 13</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>«26» ноября  2022 г.</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>5 (отлично)</ins>

<b>Отчёт сдан</b> «26» <ins>ноября</ins> <ins>2022</ins> г., <b>итоговая оценка</b> <ins>4 (отлично)</ins>

<b>Подпись преподавателя:</b> ________________


## 1. Тема:  
Отладчик системы программирования OC UNIX.

## 2. Цель работы:
Получение навыков отладки программ.

## 3. Задание:  
Проделать и запротоколировать действия над программой, описанные в методическом пособии.

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
В качестве отлаживаемой программы взята программа из лабораторной работы №9.
Необходимо скомпилировать программу с флагом -g, запустить отладчик gdb и воспользоваться основными командами, приведёнными в пособии.

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]. 
- Просмотреть демонстрационный материал в лабораторной аудитории
- Самостоятельно отладить программу

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола.
~~~powershell
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> gcc -Wall -pedantic -std=c99 -g lab9.c -o lab9.exe
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop> gdb lab9.exe
c:\users\idl76\gcc\bin\gdb.exe: warning: Couldn't determine a path for the index cache directory.
GNU gdb (GDB) 10.1
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-w64-mingw32".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from lab9.exe...
(gdb) help
List of classes of commands:

aliases -- User-defined aliases of other commands.
breakpoints -- Making program stop at certain points.
data -- Examining data.
files -- Specifying and examining files.
internals -- Maintenance commands.
obscure -- Obscure features.
running -- Running the program.
stack -- Examining the stack.
status -- Status inquiries.
support -- Support facilities.
tracepoints -- Tracing of program execution without stopping the program.
user-defined -- User-defined commands.

Type "help" followed by a class name for a list of commands in that class.
Type "help all" for the list of all commands.
Type "help" followed by command name for full documentation.
Type "apropos word" to search for commands related to "word".
Type "apropos -v word" for full documentation of commands related to "word".
Command name abbreviations are allowed if unambiguous.
(gdb) list
7       int max(int a, int b) {
8               return a > b ? a : b;
9       }
10
11      int min(int a, int b) {
12              return a > b ? b : a;
13      }
14
15      int abs(int a) {
16              return a >= 0 ? a : -a;
(gdb) break main
Breakpoint 1 at 0x401609: file lab9.c, line 21.
(gdb) run
Starting program: C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\workshop\lab9.exe
[New Thread 15628.0x3fd8]
warning: Can not parse XML library list; XML support was disabled at compile time

Thread 1 hit Breakpoint 1, main () at lab9.c:21
21              i = 20;
(gdb) print 30 * 3
$1 = 90
(gdb) next
22              j = 10;
(gdb) step
23              l = -1;
(gdb)
24              for (k = 0; k < 51; k += 1) {
(gdb) set var k = 40
(gdb) ptype k
type = int
(gdb) backtrace
#0  main () at lab9.c:24
(gdb) continue
Continuing.
Missing! i = -6, j = -3, l = -17
[Thread 15628.0x3fd8 exited with code 0]
[Inferior 1 (process 15628) exited normally]
(gdb) quit
~~~

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 00.00.22 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
Дополнительное задание:  
Выполнить несколько команд, приведённых в методическом пособии. Поставить точку остонова с условием при помощи команды `break`.
~~~powershell
PS C:\Users\idl76\Desktop\fundamental-computer-science-sempaitakoo\workshop> gdb lab9.exe
C:\Users\idl76\gcc\bin\gdb.exe: warning: Couldn't determine a path for the index cache directory.
GNU gdb (GDB) 10.1
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-w64-mingw32".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<https://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from lab9.exe...
(gdb) list
7       int max(int a, int b) {
8               return a > b ? a : b;
9       }
10
11      int min(int a, int b) {
12              return a > b ? b : a;
13      }
14
15      int abs(int a) {
16              return a >= 0 ? a : -a;
(gdb)
17      }
18
19      int main(void) {
20              int i, j, l, k;
21              i = 20;
22              j = 10;
23              l = -1;
24              for (k = 0; k < 51; k += 1) {
25                      // printf("k = %d, i = %d, j = %d, l = %d \n", k, i, j, l);
26                      if ((abs(i - 10) <= 5) && (abs(j + 10) < 5)) {
(gdb) break 25 if k==3
Breakpoint 1 at 0x40162a: file lab9.c, line 26.
(gdb) run
Starting program: C:\Users\idl76\Desktop\fundamental-computer-science-sempaitakoo\workshop\lab9.exe
[New Thread 12864.0x35a8]
warning: Can not parse XML library list; XML support was disabled at compile time

Thread 1 hit Breakpoint 1, main () at lab9.c:26
26                      if ((abs(i - 10) <= 5) && (abs(j + 10) < 5)) {
(gdb) print i
$1 = 4
(gdb) print j
$2 = 3
(gdb) print k
$3 = 3
~~~

## 11. Выводы
Были проделаны и запротоколированы необходимые действия над программой. Изучены и освоены основные команды отладчика gdb, включая установку точек останова с условием `break ... if ...`.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________