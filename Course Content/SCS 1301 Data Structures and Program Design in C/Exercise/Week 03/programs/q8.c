#include <stdio.h>

int main() {
	double n = 10.0;
	while (n >= -5.0) {
		printf("%.2f ", n);
		n = n - 0.1;
	}
	printf("\n");
	return 0;
}
