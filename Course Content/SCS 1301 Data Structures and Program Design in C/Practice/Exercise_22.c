#include <stdio.h>

int main() {
	int c, i, n, nc;
	int lenwords[10];

	for (i = 0; i < 10; i++) {
		lenwords[i] = 0;
	}

	while ((c = getchar()) != EOF) {
		++nc;
		if (c == ' ' || c == '\t' || c == '\n') {
			nc = 0;
			printf("%d", nc);
			++lenwords[nc - 1];
		}
	}
	
	for (i = 0; i < 10; i++) {
		printf("%d : ", i + 1);
		for (n = 0; n < lenwords[i]; n++) {
			printf("#");
		}
		printf("\n");
	}
	return 0;
}
