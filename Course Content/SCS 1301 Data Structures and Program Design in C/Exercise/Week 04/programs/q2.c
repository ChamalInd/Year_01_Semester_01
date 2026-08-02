#include <stdio.h>

int main() {
	int num;

	printf("Enter a number : ");

	if (scanf("%i", &num) != 1) {
		printf("Not an integer\n");
	} else {
		printf("You entered : %i\n", num);
	}
}
