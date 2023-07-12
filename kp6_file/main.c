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