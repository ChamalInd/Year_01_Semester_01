#include <stdio.h>

int main() {
	int num1 = 10;
	int num2 = 5;
	int answer;
	char oper = '*';

	switch (oper) {
		case '+' : answer = num1 + num2; break;
		case '-' : answer = num1 - num2; break;
		case '/' : answer = num1 / num2; break;
		case '*' : answer = num1 * num2; break;
		case '%' : answer = num1 % num2; break;
	}

	printf("%i %c %i = %i\n", num1, oper, num2, answer);

	return 0;
}
