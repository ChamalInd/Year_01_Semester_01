#include <stdio.h>
#include <math.h>

void start_menu();
int sub_menu();
void show_history();
void addition();
void subtraction();
void multiplication();
void division();
void power();
void lcm();
void gcd();
void sine();
void cosine();
void tangent();
void inverse();
void rem();
void oddeven();
void percentage();

int main() {
	int input;

	start_menu();
	
	while (1) {
		printf("\n: ");
		scanf("%i", &input);
	
		if (input == 15) {
			return 0;
		}

		switch (input) {
			case 1 : addition(); break;
			case 2 : subtraction(); break;
			case 3 : multiplication(); break;	
			case 4 : division(); break;
			case 5 : power(); break;
			case 6 : lcm(); break;
			case 7 : gcd(); break;
			case 8 : sine(); break;
			case 9 : cosine(); break;
			case 10 : tangent(); break;
			case 11 : inverse(); break;
			case 12 : rem(); break;
			case 13 : oddeven(); break;
			case 14 : percentage(); break;
			case 16 : show_history(); break;
			default : printf("Invalid Input\n"); break;
		}
	}
}	

int sub_menu() {	
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 42; i++) { 
			printf("#");
		}
		printf("\n");
	}
	
	printf("##         1.  Integer Division         ##\n");
	printf("##         2.  Normal Division          ##\n");

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 42; i++) { 
			printf("#");
		}
		printf("\n");
	}

	int input;

	printf("\n: ");
	scanf("%i", &input);

	return input;
}

void show_history() {
	FILE *fp = fopen("history.txt", "r");
	char buffer[100];

	for (int j = 0; j < 4; j++) {
		if (j == 2) {
			printf("#                 History                #\n");
			continue;
		}

		for (int i = 0; i < 42; i++) { 
			printf("#");
		}
		printf("\n");
	}

	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		printf("# %s", buffer);
	}

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 42; i++) { 
			printf("#");
		}
		printf("\n");
	}

	fclose(fp);
}

void addition() {
	double num1,  num2;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a number : ");
	scanf("%lf", &num1);

	printf("Enter a number : ");
	scanf("%lf", &num2);
	
	if ((num1 == (int) num1) && (num2 == (int) num2)) {
		printf("%i + %i = %i\n", (int) num1, (int) num2, (int) (num1 + num2));
		fprintf(fp, "%i + %i = %i\n", (int) num1, (int) num2, (int) (num1 + num2));
	} else {
		printf("%.2lf + %.2lf = %.2lf\n", num1, num2, (num1 + num2));
		fprintf(fp, "%.2lf + %.2lf = %.2lf\n", num1, num2, (num1 + num2));
	}
	fclose(fp);
}

void subtraction() {
	double num1,  num2;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a number : ");
	scanf("%lf", &num1);

	printf("Enter a number : ");
	scanf("%lf", &num2);

	if ((num1 == (int) num1) && (num2 == (int) num2)) {
		printf("%i - %i = %i\n", (int) num1, (int) num2, (int) (num1 - num2));
		fprintf(fp, "%i - %i = %i\n", (int) num1, (int) num2, (int) (num1 - num2));
	} else {
		printf("%.2lf - %.2lf = %.2lf\n", num1, num2, (num1 - num2));
		fprintf(fp, "%.2lf - %.2lf = %.2lf\n", num1, num2, (num1 - num2));
	}
	fclose(fp);
}

void multiplication() {
	double num1,  num2;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a number : ");
	scanf("%lf", &num1);

	printf("Enter a number : ");
	scanf("%lf", &num2);

	if ((num1 == (int) num1) && (num2 == (int) num2)) {
		printf("%i * %i = %i\n", (int) num1, (int) num2, (int) (num1 * num2));
		fprintf(fp, "%i * %i = %i\n", (int) num1, (int) num2, (int) (num1 * num2));
	} else {
		printf("%.2lf * %.2lf = %.2lf\n", num1, num2, (num1 * num2));
		fprintf(fp, "%.2lf * %.2lf = %.2lf\n", num1, num2, (num1 * num2));
	}
	fclose(fp);
}

void division() {
	double num1,  num2;
	int mode;
	FILE *fp = fopen("history.txt", "a");
	
	mode = sub_menu();

	printf("Enter a number : ");
	scanf("%lf", &num1);

	printf("Enter a number : ");
	scanf("%lf", &num2);
	
	if (mode == 2) {
		printf("%.2lf / %.2lf = %.4lf\n", num1, num2, (num1 / num2));
		fprintf(fp, "%.2lf / %.2lf = %.4lf\n", num1, num2, (num1 / num2));
	} else {
		printf("%i / %i = %i\n", (int) num1, (int) num2, ((int) num1 / (int) num2));
		fprintf(fp, "%i / %i = %i\n", (int) num1, (int) num2, ((int) num1 / (int) num2));
	}
	fclose(fp);
}

void power() {
	double power, base;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter the base : ");
	scanf("%lf", &base);

	printf("Enter the power : ");
	scanf("%lf", &power);

	printf("%.2lf^%.2lf = %.2lf\n", base, power, pow(base, power));
	fprintf(fp, "%.2lf^%.2lf = %.2lf\n", base, power, pow(base, power));
	fclose(fp);
}

void lcm() {
	int num1,  num2, max, lcm;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a number : ");
	scanf("%i", &num1);

	printf("Enter a number : ");
	scanf("%i", &num2);

	if ( num1 > num2) {
		max = num1;
	} else {
		max = num2;
	}
	
	while (1) {
		if ((max % num1 == 0) && (max % num2 == 0)) {
			lcm = max;
			break;
		}
		max++;
	}

	printf("LCM of %i and %i = %i\n", num1, num2, lcm);
	fprintf(fp, "LCM of %i and %i = %i\n", num1, num2, lcm);
	fclose(fp);
}
	
void gcd() {
	int num1,  num2, min, gcd = 0;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a number : ");
	scanf("%i", &num1);

	printf("Enter a number : ");
	scanf("%i", &num2);

	if (num1 < num2) {
		min = num1;
	} else {
		min = num2;
	}

	for (int i = 2; i <= min; i++) {
		if ((num1 % 2 == 0) && (num2 % 2 == 0)) {
			if (gcd < i) {
				gcd = i;
			}
		}
	}

	printf("GCD of %i and %i = %i\n", num1, num2, gcd);
	fprintf(fp, "GCD of %i and %i = %i\n", num1, num2, gcd);
	fclose(fp);
}

void sine() {
	double angle, rad;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a angle : ");
	scanf("%lf", &angle);

	rad = angle * (M_PI / 180.0);

	printf("sin (%.2lf) = %.3lf\n", angle, sin(rad));
	fprintf(fp, "sin (%.2lf) = %.3lf\n", angle, sin(rad));
	fclose(fp);
}

void cosine() {
	double angle, rad;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a angle : ");
	scanf("%lf", &angle);

	rad = angle * (M_PI / 180.0);

	printf("cos (%.2lf) = %.3lf\n", angle, cos(rad));
	fprintf(fp, "cos (%.2lf) = %.3lf\n", angle, cos(rad));
	fclose(fp);
}

void tangent() {
	double angle, rad;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a angle : ");
	scanf("%lf", &angle);

	rad = angle * (M_PI / 180.0);

	printf("tan (%.2lf) = %.3lf\n", angle, tan(rad));
	fprintf(fp, "tan (%.2lf) = %.3lf\n", angle, tan(rad));
	fclose(fp);
}

void inverse() {
	double num;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a number : ");
	scanf("%lf", &num);

	printf("Inverse of %.2lf (1 / %.2lf)  =  %.2lf\n", num, num, (1/num));
	fprintf(fp, "Inverse of %.2lf (1 / %.2lf)  =  %.2lf\n", num, num, (1/num));
	fclose(fp);
}

void rem() {
	int num1,  num2;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a number : ");
	scanf("%i", &num1);

	printf("Enter a number : ");
	scanf("%i", &num2);

	printf("%i %% %i = %i\n", num1, num2, (num1 % num2));
	fprintf(fp, "%i %% %i = %i\n", num1, num2, (num1 % num2));
	fclose(fp);
}

void oddeven() {
	int num;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a number : ");
	scanf("%i", &num);

	if (num % 2 == 0) {
		printf("%i is even.\n", num);
		fprintf(fp, "%i is even.\n", num);
	} else {
		printf("%i is odd.\n", num);
		fprintf(fp, "%i is odd.\n", num);
	}
	fclose(fp);
}

void percentage() {
	double num1,  num2;
	FILE *fp = fopen("history.txt", "a");

	printf("Enter a number : ");
	scanf("%lf", &num1);

	printf("Enter a number : ");
	scanf("%lf", &num2);

	printf("(%.2lf / %.2lf) * 100 = %.2lf%%\n", num1, num2, ((num1 / num2) * 100.0));
	fprintf(fp, "(%.2lf / %.2lf) * 100 = %.2lf%%\n", num1, num2, ((num1 / num2) * 100.0));
	fclose(fp);
}

void start_menu() {
	for (int i = 0; i < 42; i++) { 
		printf("#"); 
	}

	printf("\n##   SCS 1301 - Scientific Calculator   ##\n");
	printf("##                 by                   ##\n");
	printf("##           Chamal Induwara            ##\n");
	
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 42; i++) { 
			printf("#");
		}
		printf("\n");
	}
	
	printf("#   1.  Addition \t8.  Sine         #\n");
	printf("#   2.  Subtraction \t9.  Cosine       #\n");
	printf("#   3.  Multiplication \t10. Tangent      #\n");
	printf("#   4.  Division \t11. Inverse      #\n");
	printf("#   5.  Power \t\t12. Remainder    #\n");
	printf("#   6.  LCM \t\t13. Odd or Even  #\n");
	printf("#   7.  GCD \t\t14. Percentage   #\n");
	printf("#                                        #\n");
	printf("#   15.  Exit \t\t16. History      #\n");

	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < 42; i++) { 
			printf("#");
		}
		printf("\n");
	}
}

