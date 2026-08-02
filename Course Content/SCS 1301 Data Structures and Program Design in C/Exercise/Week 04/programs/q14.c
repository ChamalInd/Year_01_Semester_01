#include <stdio.h>

char switch_case(char letter);

int main() {
	char c;

	printf("Enter a character : ");
	scanf("%c", &c);

	printf("Case swapped letter : %c\n", switch_case(c));
}

char switch_case(char letter) {
	if ((letter >= 65) && (letter <= 90)) {
		return letter + 32;
	} else if ((letter >= 97) && (letter <= 122)) {
		return letter - 32;
	}

	return -1;
}
