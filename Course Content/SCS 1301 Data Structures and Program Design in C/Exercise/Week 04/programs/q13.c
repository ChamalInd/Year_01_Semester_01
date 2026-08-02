#include <stdio.h>

void floating_check(double num);

int main() {
	double num;

	printf("Enter a number : ");
	scanf("%lf", &num);

	floating_check(num);
}

void floating_check(double num) {
	if (num != (int) num) {
		printf("True\n");
	}
}
