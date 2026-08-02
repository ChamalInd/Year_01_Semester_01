#include <stdio.h>

int main() {
	int nums[10];
	int *ptr;

	printf("Enter 10 integers : \n");
	for (int i = 0; i < 10; i++) {
		scanf("%i", &nums[i]);
	}

	ptr = &nums[0];

	for (int i = 0; i < 10; i++) {
		printf("%i\t", *ptr);
		ptr++;
	}
	printf("\n");
}
