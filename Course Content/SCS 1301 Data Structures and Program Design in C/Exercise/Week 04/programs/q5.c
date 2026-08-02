#include <stdio.h>

int main() {
	int a; double b; char c;
	int *ptr_a = &a; double *ptr_b = &b; char *ptr_c = &c;

	printf("Initial position\n");
	printf("ptr_a : %p\nptr_b = %p\nptr_c = %p\n\n", ptr_a, ptr_b, ptr_c);
	
	for (int i = 0; i < 5; i++) {
		ptr_a++;
		ptr_b++;
		ptr_c++;
	}
	
	printf("After incrementing\n");
	printf("ptr_a : %p\nptr_b = %p\nptr_c = %p\n", ptr_a, ptr_b, ptr_c);
}
