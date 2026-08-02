#include <stdio.h>

void oddeven(int num);

int main() {
	int num;
	
	printf("Enter a number : ");
	scanf("%i", &num);

	oddeven(num);
}

void oddeven(int num) {
	if (num % 2 == 0) {
		printf("%i is even\n", num);
	} else {
		printf("%i is odd\n", num);
	}
}
