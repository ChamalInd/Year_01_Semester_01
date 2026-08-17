#include <stdio.h>

int main() {
	char c = '5';
	
	if (c > 64 && c < 91) {
		printf("c is in upper case\n");
		printf("lower case c is %c\n", c + 32); 
	} else if (c > 96 && c < 123) {
		printf("c is in lower case\n");
		printf("upper case c is %c\n", c - 32); 
	} else if (c > 47 && c < 58) {
		printf("numbers\n");
	} else {
		printf("Others\n");
	}

	return 0;
}
