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