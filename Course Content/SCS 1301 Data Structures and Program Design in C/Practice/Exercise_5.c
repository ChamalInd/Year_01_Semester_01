#include <stdio.h>


int main() {
	float fah, cel;
	float upper, step;

	upper = 300;
	step = 20;
	cel = 0;

	printf("%12s %12s\n", "Celsius", "Fahrenheit");
	
	while (cel <= upper) {
		fah = (cel * (9.0 / 5.0)) + 32.0;
		printf("%12.0f %12.2f\n", cel, fah);
		cel += step; 
	}
	return 0;
}
