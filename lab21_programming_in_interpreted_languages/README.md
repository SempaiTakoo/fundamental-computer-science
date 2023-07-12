# Отчёт по лабораторной работе №21 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 11</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>01.04.23</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>5 (отлично)</ins>

<b>Отчёт сдан</b> «1» <ins>апреля</ins> <ins>2023</ins> г., <b>итоговая оценка</b> <ins>5 (отлично)</ins>

<b>Подпись преподавателя:</b> ________________

## 1. Тема:
Программирование на интерпретируемых языках

## 2. Цель работы:
Составить программу выполнения заданных действий над файлами на языках Bash и Python

## 3. Задание:
Генерация заданного числа копий указанного Файла. Имена копий генерировать добавлением к имени исходного файла следующей по порядку буквы или цифры, начиная с заданной буквы или цифры
<b>Дополнительные условия:</b>
- Если указан параметр "?", то выводится подсказка (спецификация программы)
- Если параметры опущены, то устанаваливаются некоторые стандартные значения параметров

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
- Изучить необходимую для лабораторной работы литературу по заданным языкам программирования
- Изучить лабораторный пример
- Написать тесты для программы
- Написать программу на Python
- Написать программу на Bash

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]:
Программы на bash и python по сути своего алгоритма идентичны:
- Сохранить введённые пользователем аргументы команды в переменные: имя файла, количество копий, символ начала нумерации
- Извлечь из имени файла имя и расширение
- При помощи встроенной в язык программирования команды копирования сгенерировать копию файла с новым именем и повторить заданное действие необходимое количество раз

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола:
Python:
```python
from shutil import copy
from sys import argv

def name_format(filename: str):
    return [i[::-1] for i in filename[::-1].split('.', 1)][::-1]

def next_char(s: str):
    if s.isdigit():
        return str(int(s) + 1)
    if s == 'z':
        return 'a'
    if s == 'Z':
        return 'A'
    return chr(ord(s) + 1)

def copying_file(argv: list):
    if len(argv) == 0:
        print("Error: Parameter [FILENAME] was not entered.")
        print("Try 'create_copies ?'")
        return
    if argv[0] == '?':
        print("\nThe command generates the specified number of copies of the file.")
        print("Copy names are created by adding the next letter/digit to the name of source file, starting with specified letter/digit.")
        print("create_copies [FILENAME] [NUMBER] [ENUMERATION]\n")
        return
    if len(argv) == 1:
        n, enum = 1, '1'
    else:
        n, enum = int(argv[1]), str(argv[2])
    filename = argv[0]
    name, format = name_format(filename)
    with open(filename) as f:
        for i in range(n):
            copy(filename, f"{name}{enum}.{format}")
            enum = next_char(enum)

if __name__ == '__main__':
    copying_file(argv[1:])
```
```powershell
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages> dir


    Каталог: C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages


Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----        31.03.2023     21:16           1218 create_copies.py
-a----        31.03.2023     21:04           1052 create_copies.sh
-a----        31.03.2023     20:44             11 file.txt
-a----        31.03.2023     21:17           8432 README.md


PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages> py create_copies.py
Error: Parameter [FILENAME] was not entered.
Try 'create_copies ?'
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages> py create_copies.py ?

The command generates the specified number of copies of the file.
Copy names are created by adding the next letter/digit to the name of source file, starting with specified letter/digit.
create_copies [FILENAME] [NUMBER] [ENUMERATION]

PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages> py create_copies.py file.txt
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages> dir


    Каталог: C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages


Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----        31.03.2023     21:16           1218 create_copies.py
-a----        31.03.2023     21:04           1052 create_copies.sh
-a----        31.03.2023     20:44             11 file.txt
-a----        31.03.2023     21:18             11 file1.txt
-a----        31.03.2023     21:17           8432 README.md


PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages> py create_copies.py file.txt 4 Z
PS C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages> dir


    Каталог: C:\Users\idl76\Рабочий стол\fundamental-computer-science-sempaitakoo\lab21_programming_in_interpreted_languages


Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
-a----        31.03.2023     21:16           1218 create_copies.py
-a----        31.03.2023     21:04           1052 create_copies.sh
-a----        31.03.2023     20:44             11 file.txt
-a----        31.03.2023     21:18             11 file1.txt
-a----        31.03.2023     21:18             11 fileA.txt
-a----        31.03.2023     21:18             11 fileB.txt
-a----        31.03.2023     21:18             11 fileC.txt
-a----        31.03.2023     21:18             11 fileZ.txt
-a----        31.03.2023     21:17           8432 README.md
```

Bash:
```bash
#!/usr/bin/bash

alpha=abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz
ALPHA=ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ

if [ "$1" = "?" ];
then
	echo -e "\nThe command generates the specified number of copies of the file.\nCopy names are created by adding the next letter/digit to the name of source file, starting with specified letter/digit.\n\ncreate_copies [FILENAME] [NUMBER] [ENUMERATION]\n"
	exit
fi
fname=$1
if [ -z $fname ]
then
	echo 'Error: Parameter [FILENAME] was not entered.'
	echo "Try 'create_copies ?'"
	exit
fi
name=${fname%.*}
ext=${fname##*.}
n=$2
if [ -z $n ]
then
	n=1
fi
enum=$3
if [ -z $enum ]
then
	enum=1
fi

case $enum in
	[a-z])
		for (( i=0; i < $n; ++i)) do
			cp $fname $name$enum.$ext
			enum=$(echo $enum | tr "${alpha:0:26}" "${alpha:1:26}")
		done
		;;
	[A-Z])
		for (( i=0; i < $n; ++i)) do
			cp $fname $name$enum.$ext
			enum=$(echo $enum | tr "${ALPHA:0:26}" "${ALPHA:1:26}")
		done
		;;
	[0-9])
		for (( i=0; i < $n; ++i)) do
			cp $fname $name$enum.$ext
			enum=$(($enum + 1))
		done
		;;
esac
```
```bash
takoo@takoo:~/Desktop$ ls
create_copies.sh  file.txt
takoo@takoo:~/Desktop$ bash create_copies.sh
Error: Parameter [FILENAME] was not entered.
Try 'create_copies ?'
takoo@takoo:~/Desktop$ bash create_copies.sh ?

The command generates the specified number of copies of the file.
Copy names are created by adding the next letter/digit to the name of source file, starting with specified letter/digit.

create_copies [FILENAME] [NUMBER] [ENUMERATION]

takoo@takoo:~/Desktop$ bash create_copies.sh file.txt
takoo@takoo:~/Desktop$ ls 
create_copies.sh  file1.txt  file.txt
takoo@takoo:~/Desktop$ bash create_copies.sh file1.txt 4 Z
takoo@takoo:~/Desktop$ ls
create_copies.sh  file1A.txt  file1B.txt  file1C.txt  file1.txt  file1Z.txt  file.txt
takoo@takoo:~/Desktop$ ^C
takoo@takoo:~/Desktop$
```

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы:

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 01.04.23 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
- [Решённый контест](https://codeforces.com/contest/1798)

## 11. Выводы
Было выяснено, что при помощи языков программирования можно создавать программы манипулирующие с файлами заданным образом. Очевидно, автоматизация любого процесса, в нашем случае процесса взаимодействия с файлами, приводит к ускорению выполнения работы и повышению удобства пользования компьютером.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________