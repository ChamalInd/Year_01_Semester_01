#include <stdio.h>

int main() {
	int n = 10;
	int isFirst = 0;
	while (n <= 99) {
		printf("%d", n);
		isFirst = 0;
		if (n % 2 == 0) {
			if (!isFirst) {
				printf("\t-multiple of 2");
				isFirst = 1;
			} else {
				printf("\tmultiple of 2");
			}
		}
		if (n % 3 == 0) {
			if (!isFirst) {
				printf("\t-multiple of 3");
				isFirst = 1;
			} else {
				printf("\tmultiple of 3");
			}
		}
		if (n % 5 == 0) {
			if (!isFirst) {
				printf("\t-multiple of 5");
				isFirst = 1;
			} else {
				printf("\tmultiple of 5");
			}
		}
		printf("\n");
		++n;
	}
	return 0;
}
