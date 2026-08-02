#include <stdio.h>

#define UPPER 300
#define LOWER 0
#define STEP 20


int main() {
	int fah;

	for (fah = LOWER; fah <= UPPER; fah += STEP) {
		printf("%3d %6.2f\n", fah, (5.0 / 9.0) * (fah - 32.0));
	}
	return 0;
}
