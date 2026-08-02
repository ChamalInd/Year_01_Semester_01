#include <stdio.h>

int powerof(int power, int base);

int main() {
	int power, base, answer;

	printf("Enter the base number : ");
	scanf("%i", &base);
	printf("Enter the power : ");
	scanf("%i", &power);

	answer = powerof(power, base);
	printf("%i^%i = %i\n", base, power, answer);
}

int powerof(int power, int base) {
	int answer = 1;

	for (int i = 0; i < power; i++) {
		answer *= base;
	}

	return answer;
}
