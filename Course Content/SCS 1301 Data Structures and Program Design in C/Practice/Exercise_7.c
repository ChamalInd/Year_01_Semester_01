#include <stdio.h>


int main() {
	int fah;

	printf("%12s %12s\n", "Fahrenheit", "Celsius");

	for (fah = 300; fah >= 0; fah -= 20) {
		printf("%12d %12.2f\n", fah, (5.0 / 9.0) * (fah - 32.0));
	}
	return 0;
}
