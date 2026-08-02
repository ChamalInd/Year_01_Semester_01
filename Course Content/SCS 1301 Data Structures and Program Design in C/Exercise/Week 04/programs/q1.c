#include <stdio.h>

int main() {
	int a; float b; char c; unsigned int d, e;

	printf("Enter an integer : ");
	scanf("%i", &a);
	printf("Enter a floating point number : ");
	scanf("%f", &b);
	printf("Enter a character : ");
	scanf(" %c", &c);
	printf("Enter an octal number : ");
	scanf("%o", &d);
	printf("Enter a hexa decimal number : ");
	scanf("%x", &e);

	printf("\nInteger : %i\n", a);
	printf("Floating point number : %f\n", b);
	printf("Character : %c\n", c);
	printf("Hexa decimal number : %o\n", d);
	printf("Octal number : %x\n", e);
	
	printf("\nInteger in integer format: %i\n", a);
	printf("Floating point number in integer format: %i\n", (int) b);
	printf("Character in integer format: %i\n", c);
	printf("Hexa decimal number in integer format: %i\n", d);
	printf("Octal number in integer format: %i\n", e);
}
