#include <stdio.h>

int main() {
    double d;
	float f;
	long l;
	int i;

	i = l = f = d = 100/3;
	printf("%d\t%ld\t%f\t%f\n",i,l,f,d);

	d = f = l = i = 100/3;
	printf("%d\t%ld\t%f\t%f\n",i,l,f,d);

	i = l = f = d = 100/3;
	printf("%d\t%ld\t%f\t%f\n",i,l,f,d);

	d = f = l = i = (float)100/3;
	printf("%d\t%ld\t%f\t%f\n",i,l,f,d);

	i = l = f = d = (double)(100000/3);
	printf("%d\t%ld\t%f\t%f\n",i,l,f,d);

	d = f = l = i = 100000/3;
	printf("%d\t%ld\t%f\t%f\n",i,l,f,d);

	return 0;
}
