#include <stdio.h>

int main() {
	double num1, num2, ans;
	char oper;

	while (1) {
		printf("Enter a number : ");
		scanf("%lf", &num1);

		if (num1 < 0) {
			break;
		}

		printf("Enter a number : ");
		scanf("%lf", &num2);
		printf("Enter the operation : ");
		scanf(" %c", &oper);
	
		switch (oper) {
			case '+' : ans = num1 + num2; break; 
			case '-' : ans = num1 - num2; break; 
			case '*' : ans = num1 * num2; break; 
			case '/' : ans = num1 / num2; break; 
			case '%' : ans = (int) num1 % (int) num2; break;
		}

		printf("%.2lf %c %.2lf = %.2lf\n\n", num1, oper, num2, ans);
	}
}
