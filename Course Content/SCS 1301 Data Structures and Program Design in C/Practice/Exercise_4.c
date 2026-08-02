#include <stdio.h>

int main() {
	float far, cel;
	float upper, step;

	upper = 300;
	step = 20;
	far = 0;

	printf("%12s %12s\n", "Fahrenheit", "Celsius");

	while (far <= upper) {
		cel = (5.0 / 9.0) * (far - 32.0);
		printf("%12.0f %12.2f\n", far, cel);
		far += step;
	}

	return 0;
}
