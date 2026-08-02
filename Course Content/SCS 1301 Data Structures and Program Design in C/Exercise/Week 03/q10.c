#include <stdio.h>

int main() {
	char n = 'a';
	while (n <= 122) {
		printf("%c ", n);
		++n;
	}
	printf("\n");
	return 0;
}
