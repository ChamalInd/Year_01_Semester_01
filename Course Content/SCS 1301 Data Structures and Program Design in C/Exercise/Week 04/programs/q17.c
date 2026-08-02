#include <stdio.h>

void find_intersect(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4);

int main() {
	double x1, x2, x3, x4, y1, y2, y3, y4;

	printf("Enter the X coordinate of 1st point : ");
	scanf("%lf", &x1);
	printf("Enter the Y coordinate of 1st point : ");
	scanf("%lf", &y1);
	printf("Enter the X coordinate of 2nd point : ");
	scanf("%lf", &x2);
	printf("Enter the Y coordinate of 2nd point : ");
	scanf("%lf", &y2);
	printf("Enter the X coordinate of 3rd point : ");
	scanf("%lf", &x3);
	printf("Enter the Y coordinate of 3rd point : ");
	scanf("%lf", &y3);
	printf("Enter the X coordinate of 4th point : ");
	scanf("%lf", &x4);
	printf("Enter the Y coordinate of 4th point : ");
	scanf("%lf", &y4);
	find_intersect(x1, x2, x3, x4, y1, y2, y3, y4);
}

void find_intersect(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4) { 
	double det = ((x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4));
	if (det == 0) {
		printf("Lines do not intersect\n");
	} else {
		double t1 = (x1 * y2) - (y1 * x2);
		double t2 = (x3 * y4) - (y3 * x4);

		double px = ((t1 * (x3 - x4)) - ((x1 - x2) * t2)) / det;
		double py = ((t1 * (y3 - y4)) - ((y1 - y2) * t2)) / det;

		printf("Intersection occur at (%.2lf, %.2lf)\n", px, py);
	}
}	
