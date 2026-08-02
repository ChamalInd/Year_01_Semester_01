#include <stdio.h>

int main() {
	int nums[10];

	printf("Enter 10 integers : \n");
	for (int i = 0; i < 10; i++) {
		scanf("%i", &nums[i]);
	}

	for (int i = 0; i < 10; i++) {
		printf("%i\t", nums[i]);
	}
	printf("\n");
}
