#include <stdio.h>
#include <math.h>

void angle_between(double x1, double x2, double y1, double y2);

int main() {
	double x1, x2, y1, y2;

	printf("Enter the X coordinate of 1st point : ");
	scanf("%lf", &x1);
	printf("Enter the Y coordinate of 1st point : ");
	scanf("%lf", &y1);
	printf("Enter the X coordinate of 2nd point : ");
	scanf("%lf", &x2);
	printf("Enter the Y coordinate of 2nd point : ");
	scanf("%lf", &y2);

	angle_between(x1, x2, y1, y2);
}

void angle_between(double x1, double x2, double y1, double y2) {
	double opposite = y2 - y1;
	double adjacent = x2 - x1;

	printf("Angle with the X axis is : %.3lf\n", atan(opposite/adjacent));
}
