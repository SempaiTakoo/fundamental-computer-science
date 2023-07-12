#include <stdio.h>

int sign(int n) {
	return n > 0 ? 1 : n < 0 ? -1 : 0;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int min(int a, int b) {
	return a > b ? b : a;
}

int abs(int a) {
	return a >= 0 ? a : -a;
}

int main(void) {
	int i, j, l, k;
	i = 20;
	j = 10;
	l = -1;
	for (k = 0; k < 51; k += 1) {
		printf("k = %d, i = %d, j = %d, l = %d \n", k, i, j, l);
		if ((abs(i - 10) <= 5) && (abs(j + 10) < 5)) {
			printf("Hit! k = %d, i = %d, j = %d, l = %d \n", k, i, j, l);
			break;
		}
		if (k == 50) {
			printf("Missing! i = %d, j = %d, l = %d \n", i, j, l);
		}

		i = (abs(max(i*(k + 5), j*(k + 6))) - abs(min(j*(k + 7), l*(k + 8)))) % 20;
		j = (3 - sign(i - j)) * abs(min(i*l + 5, j*l - 3*i*j + 6)) % 25 - 7;
		l = i % 10  + j % 10 + l % 10;
	}
   return 0;
}