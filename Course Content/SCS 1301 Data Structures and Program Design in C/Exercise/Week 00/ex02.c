#include <stdio.h>
#include <math.h>

int main() {
	// rectangle dimensions
	double length = 10;
	double breadth = 5;

	double area_rect = length * breadth;
	double perimeter_rect = (length + breadth) * 2.0;
	double diagonal = sqrt((length * length) + (breadth * breadth));

	// triangle dimensions
	double base = 8;
	double height = 6;
	double side_1 = 8;
	double side_2 = 6;
	double side_3 = 7;

	double area_tri = 0.5 * base * height;
	double perimeter_tri = side_1 + side_2 + side_3;

	// circle dimensions
	double radius = 7;
	double area_cir = M_PI * radius * radius;
	double circumference = 2.0 * M_PI * radius;
	double diameter = 2.0 * radius;
	double semi_area = M_PI_2 * radius * radius;

	printf("Rectangle : \n\tArea      : %.2f m^2\n\tPerimeter : %.2f m\n\tDiagonal  : %.2f m\n\n", area_rect, perimeter_rect, diagonal);
	printf("Triangle : \n\tArea      : %.2f m^2\n\tPerimeter : %.2f m\n\n", area_tri, perimeter_tri);
	printf("Circle : \n\tArea               : %.2f m^2\n\tCurcumference      : %.2f m\n\tDiameter           : %.2f m\n\tArea of Semicircle : %.2f m^2\n\n", area_cir, circumference, diameter, semi_area);


	return 0;
}
