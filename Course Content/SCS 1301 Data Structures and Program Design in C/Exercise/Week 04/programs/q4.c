#include <stdio.h>

int main() {
	int num1, num2;
	int *ptr1 = &num1, *ptr2 = &num2;

	printf("Enter a number : ");
	scanf("%i", ptr1);
	printf("Enter a number : ");
	scanf("%i", ptr2);

	*ptr1 = *ptr1 + *ptr2;

	printf("Sum of two numbers : %i\n", *ptr1);
}
