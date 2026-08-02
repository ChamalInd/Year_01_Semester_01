#include <stdio.h>
#include <math.h>

void check_point(double x, double y, double ox, double oy, double r);

int main() {
	double x, y, ox, oy, r;
	
	printf("Enter a X coordinate : ");
	scanf("%lf", &x);
	printf("Enter a Y coordinate : ");
	scanf("%lf", &y);
	printf("Enter a Ox coordinate of circle : ");
	scanf("%lf", &ox);
	printf("Enter a Oy coordinate of circle : ");
	scanf("%lf", &oy);
	printf("Enter the radius of circle : ");
	scanf("%lf", &r);
	check_point(x, y, ox, oy, r);
}

void check_point(double x, double y, double ox, double oy, double r) {
	printf("Is coordinate (%.2lf, %.2lf) is on the circle with a center at (%.2lf, %.2lf) and a radius of %.2lf : ", x, y, ox, oy, r);

	if (pow((x - ox), 2) + pow((y - oy), 2) == pow(r, 2)) {
		printf("True\n");
	} else {
		printf("False\n");
	}

	printf("Circumference of Circle : %.2lf\n", 2.0 * M_PI * r);
	printf("Area of Circle : %.2lf\n", M_PI * r * r);
	printf("Volume of Sphere with same readius : %.2lf\n", (4.0 / 3.0) * M_PI * pow(r, 3));
}
