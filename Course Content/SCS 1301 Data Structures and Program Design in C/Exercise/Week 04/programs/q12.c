#include <stdio.h>

int main() {
	int *pint;
	float *pfloat;
	char *pchar;
	double *pdouble;

	printf("Size of an integer pointer: %zu\n", sizeof(pint));
	printf("Size of an char pointer: %zu\n", sizeof(pchar));
	printf("Size of an double pointer: %zu\n", sizeof(pdouble));
	printf("Size of an float pointer: %zu\n", sizeof(pfloat));
}
