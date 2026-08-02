#include <stdio.h>

int main() {
	int c, i, nwhite, nother;
	int ndigits[10];

	nwhite = nother = 0;

	// initializing the array
	for (i = 0; i < 10; i++) {
		ndigits[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		if (c >= '0' && c <= '9') {
			++ndigits[c - '0']; // since value of '0' is not known
		} else if (c == ' ' || c == '\t' || c == '\n') {
			++nwhite;
		} else {
			++nother;
		}
	}

	for (i = 0; i < 10; i++) {
		printf("%d: %13d\n", i, ndigits[i]);
	}
	printf("White spaces: %2d\nOthers: %8d\n", nwhite, nother);
	return 0;
}
