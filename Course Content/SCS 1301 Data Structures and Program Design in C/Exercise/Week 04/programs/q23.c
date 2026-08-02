#include <stdio.h>

int main() {
	char welcome[] = {'H', 'E', 'L', 'L', 'O'};

	printf("%c\n", welcome[3]);
	welcome[0] = 'Y';
	printf("%c\n", welcome[3] + 2);
	for (unsigned short j = 0; j < 3; j++) {
		printf("%c\n", welcome[j]);
	}
}
