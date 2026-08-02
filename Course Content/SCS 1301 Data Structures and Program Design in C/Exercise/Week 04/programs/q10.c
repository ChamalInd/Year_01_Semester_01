#include <stdio.h>
#include <math.h>

double calc_trig(int fun, int angle);
void print_trig_table(int fun, int start, int end, int step);

int main() {
	int start, end, step;
	char fun;

	while (1) {
		printf("Supported Functions\ns : Sin\tc : Cos\tt : Tan\tX : Exit\n\n");
		printf("Enter the function : ");
		scanf(" %c", &fun);

		if (fun == 'X') {
			return 0;
		}

		printf("Enter the start angle : ");
		scanf("%i", &start);
		printf("Enter the end angle : ");
		scanf("%i", &end);
		printf("Enter the step : ");
		scanf("%i", &step);

		print_trig_table(fun, start, end, step);
	}
}

void print_trig_table(int fun, int start, int end, int step){
	double ans;
	int fun_value;
	char *function[] = {"sin", "cos", "tan"};
	
	switch (fun) {
		case 's' : printf("\nSine Table\n\n"); fun_value = 0; break;
		case 'c' : printf("\nCosine Table\n\n"); fun_value = 1; break;
		case 't' : printf("\nTan Table\n\n"); fun_value = 2; break;
	}

	printf("Angle\t    Value\n");

	for (int i = start; i <= end; i += step) {
		ans = calc_trig(fun_value, i);
		printf("%s (%3i)  %6.3lf\n",function[fun_value],  i, ans);
	}
}

double calc_trig(int fun, int ang) {
	double ang_rad = (ang * (M_PI / 180.0));

	switch (fun) {
		case 0 : return sin(ang_rad); break;
		case 1 : return cos(ang_rad); break;
		case 2 : return tan(ang_rad); break;
	}

	return -1;
}
