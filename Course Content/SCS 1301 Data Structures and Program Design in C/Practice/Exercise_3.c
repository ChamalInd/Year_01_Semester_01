#include <stdio.h>

int main() {
	float fah, cel;
	float upper, step;

	upper = 300;
	step = 20;
	fah = 0;
	
	while (fah <= upper) {
		cel = (5.0 / 9.0) * (fah - 32.0);
		printf("%3.0f  %6.2f\n", fah, cel);
		fah += step;
	}
	return 0;
}
