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