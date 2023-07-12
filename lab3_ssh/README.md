# Отчёт по лабораторной работе №3 по курсу «Фундаментальная информатика»

<b>Студент группы:</b> <ins>М8О-108Б-22 Караев Тариел Жоомартбекович, № по списку 12</ins>

<b>Контакты e-mail:</b> <ins>idl76h@gmail.com</ins>

<b>Работа выполнена:</b> <ins>«8» октября 2022 г.</ins>

<b>Преподаватель:</b> <ins>асп. каф. 806 Сахарин Никита Александрович</ins>

<b>Выходной контроль знаний с оценкой:</b> <ins>5 (отлично)</ins>

<b>Отчёт сдан</b> «8» <ins>октября</ins> <ins>2022</ins> г., <b>итоговая оценка</b> <ins>5 (отлично)</ins>

<b>Подпись преподавателя:</b> ________________


## 1. Тема:  
Сети и телекоммуникации в ОС UNIX.

## 2. Цель работы:  
Освоение навыков работы в сети.

## 3. Задание:  
Построить локальную компьютерную сеть и произвести файловые манипуляции.

## 4. Оборудование:
<b>Процессор:</b> 11th Gen Intel(R) Core(TM) i3-1115G4 @ 3.00GHz<br/>
<b>ОП:</b> 8 ГБ<br/>
<b>SSD:</b> 256 ГБ<br/>
<b>Адрес:</b> 89.179.105.231<br/>
<b>Монитор:</b> 15,6-дюймовый (1920 х 1080)<br/>
<b>Графика:</b> Intel(R) UHD Graphics<br/>

## 5. Программное обеспечение:
<b>Операционная система семейства:</b> VirtualBox 6.1.38 - Ubuntu 22.04.01 LTS<br/>
<b>Интерпретатор команд:</b> bash версия 4.4.19<br/>
<b>Местонахождение и имена файлов программ и данных на домашнем компьютере:</b> /home/takoo<br/>

## 6. Идея, метод, алгоритм решения задачи (в формах: словесной, псевдокода, графической [блок-схема, диаграмма, рисунок, таблица] или формальные спецификации с пред- и постусловиями).
Изучить основы владения сетевыми средствами.
Ввод команд:
1. `ssh` - подключение к удалённой машине
2. `scp` - копирование файлов и директорий
3. `rsync` - синхронизация каталогов
4. `ftp` - подсоединения к узлу сети для осуществления обмена файлами по протоколу ftp
5. `get` - получение файла с удалённой машины
6. `put` - передача файла на удалённую машину
7. `tar` - архивация/разархивация
8. `pax` - архивация/разархивация
9. `gzip` - упаковка
10. `iconv` - перекодирование
11. `dict` - чтение электронного словаря

## 7. Сценарий выполнения работы [план работы, первоначальный текст программы в черновике (можно на отдельном листе) и тесты либо соображения по тестированию]. 
- Изучить справочный материал и дополнительную литературу
- Прослушать лекцию, посетить консультацию
- Просмотреть демонстрационный материал в лабораторной аудитории
- Собственноручно проделать основные примеры и продемонстрировать владение сетевыми средствами
преподавателю
- Выполнить не менее двух заданий связи с внешней средой
- Приобрести основные навыки работы в сети
- Освоить команды для работы в сети
- Научиться манипулировать с файлами на удалённой машине
- Запротоколировать сеанс

Пункты 1-7 отчета составляются сторого до начала лабораторной работы.
Допущен к выполнению работы.  
<b>Подпись преподавателя</b> ________________

## 8. Распечатка протокола.
~~~
stud@it-17:~$ ssh stud@192.168.2.162
The authenticity of host '192.168.2.162 (192.168.2.162)' can't be established.
ED25519 key fingerprint is SHA256:YIsChpiFwtLa0j9mRsG8e1xcA9rZlWTiM0whDRRSsxA.
This key is not known by any other names
Are you sure you want to continue connecting (yes/no/[fingerprint])? yes
Warning: Permanently added '192.168.2.162' (ED25519) to the list of known hosts.
stud@192.168.2.162's password: 
Welcome to Ubuntu 22.04.1 LTS (GNU/Linux 5.15.0-47-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

151 updates can be applied immediately.
57 of these updates are standard security updates.
To see these additional updates run: apt list --upgradable


The list of available updates is more than a week old.
To check for new updates run: sudo apt update
Last login: Sat Oct  8 10:00:50 2022 from 192.168.2.163
stud@it-32:~$ ls
1.txt    Desktop    fil1      hello   Pictures  Public  Templates  xyu.txt
aaa.txt  Documents  fil1.txt  Music   ping.gz   remote  test.txt   XYZ
ar.tar   Downloads  ghfs      ourdir  ping.txt  snap    Videos
stud@it-32:~$ touch text.txt
stud@it-32:~$ ls
1.txt    Desktop    fil1      hello   Pictures  Public  Templates  Videos
aaa.txt  Documents  fil1.txt  Music   ping.gz   remote  test.txt   xyu.txt
ar.tar   Downloads  ghfs      ourdir  ping.txt  snap    text.txt   XYZ
stud@it-32:~$ logout
Connection to 192.168.2.162 closed.
stud@it-17:~$ scp 4444.txt stud@192.168.2.162:/home/stud
stud@192.168.2.162's password: 
4444.txt                                      100%    0     0.0KB/s   00:00    
stud@it-17:~$ ssh stud@192.168.2.162
stud@192.168.2.162's password: 
Welcome to Ubuntu 22.04.1 LTS (GNU/Linux 5.15.0-47-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

151 updates can be applied immediately.
57 of these updates are standard security updates.
To see these additional updates run: apt list --upgradable


The list of available updates is more than a week old.
To check for new updates run: sudo apt update
Last login: Sat Oct  8 10:31:04 2022 from 192.168.2.160
stud@it-32:~$ ls
1.txt     Desktop    fil1.txt  ourdir    Public     test.txt  XYZ
4444.txt  Documents  ghfs      Pictures  remote     text.txt
aaa.txt   Downloads  hello     ping.gz   snap       Videos
ar.tar    fil1       Music     ping.txt  Templates  xyu.txt
~~~

## 9. Дневник отладки должен содержать дату и время сеансов отладки и основные события (ошибки в сценарии и программе, нестандартные ситуации) и краткие комментарии к ним. В дневнике отладки приводятся сведения об использовании других ЭВМ, существенном участии преподавателя и других лиц в написании и отладке программы.

| № |  Лаб. или дом. | Дата | Время | Событие | Действие по исправлению | Примечание |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| 1 | дом. | 08.10.22 | 13:00 | Выполнение лабораторной работы | - | - |

## 10. Замечания автора по существу работы.
~~~
takoo@sshtest2:~$ vi
takoo@sshtest2:~$ cat fffff 
sdffdfdfdf������������
takoo@sshtest2:~$ enca -L russian fffff 
MS-Windows code page 1251
  LF line terminators
takoo@sshtest2:~$ od fffff -t x1
0000000 73 64 66 66 64 66 64 66 64 66 e2 e0 e2 e0 e2 e0
0000020 e2 e0 e2 cc c0 c8 0a
0000027
takoo@sshtest2:~$ touch 2.txt
takoo@sshtest2:~$ touch 3.txt
takoo@sshtest2:~$ ls
2.txt  Desktop    Downloads  Music     Public  Templates
3.txt  Documents  fffff      Pictures  snap    Videos
takoo@sshtest2:~$ tar -cf new.tar 2.txt 3.txt fffff
takoo@sshtest2:~$ ls
2.txt  Desktop    Downloads  Music    Pictures  snap       Videos
3.txt  Documents  fffff      new.tar  Public    Templates
takoo@sshtest2:~$ scp new.tar takoo@192.168.56.101:/home/takoo/for_SSH/
takoo@192.168.56.101's password: 
new.tar                                      100%   10KB   7.2MB/s   00:00    
takoo@sshtest2:~$ ssh takoo@192.168.56.101
takoo@192.168.56.101's password: 
Welcome to Ubuntu 22.04.1 LTS (GNU/Linux 5.15.0-50-generic x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

0 updates can be applied immediately.

Last login: Tue Oct 18 22:19:50 2022 from 192.168.56.102
takoo@sshtest:~/for_SSH$ tar -xf new.tar
takoo@sshtest:~/for_SSH$ iconv -f CP1251 -t UTF-16 fffff -o outfile.txt
takoo@sshtest:~/for_SSH$ ls
2.txt  3.txt  fffff  new.tar  outfile.txt
takoo@sshtest:~/for_SSH$ file -i outfile.txt 
outfile.txt: text/plain; charset=utf-16le
takoo@sshtest:~/for_SSH$ od -A n -t x1 outfile.txt 
 ff fe 73 00 64 00 66 00 66 00 64 00 66 00 64 00
 66 00 64 00 66 00 32 04 30 04 32 04 30 04 32 04
 30 04 32 04 30 04 32 04 1c 04 10 04 18 04 0a 00
~~~

## 11. Выводы
Было выяснено, что существует множество различных утилит, полезных для работы в сети. Были изучены некоторые их них. Освоены основные команды для манипуляции файлами на удалённой машине, архивации и связи. Изучены основы кодировок файлов. В результате работы были приобретены навыки, которые будут полезны для выполнения последующих лабораторных работ.

Недочёты при выполнении задания могут быть устранены следующим образом: —

<b>Подпись студента:</b> ________________