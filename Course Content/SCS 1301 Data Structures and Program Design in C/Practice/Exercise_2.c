#include <stdio.h>

int main() {
	int fah, cel;
	int upper, step;

	upper = 300;
	step = 20;
	fah = 0;
	
	while (fah <= upper) {
		// since we are using int variables 5 / 9 will result in 0 due to integer turncate
		// so no (5 / 9) * (fah - 32)
		cel = 5 * (fah - 32) / 9;
		// will print left aligned
		// printf("%d\t%d\n", fah, cel);
		// will print right aligned
		printf("%3d %6d\n", fah, cel);
		fah += step;
	}
	return 0;
}
