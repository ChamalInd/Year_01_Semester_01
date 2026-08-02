#include <stdio.h>
#include <math.h>

int main() {
	int nums[8];
	int decimal = 0;

	printf("Enter a binary number with 8 bits : \n");
	for (int i = 0; i < 8; i++) {
		scanf("%i", &nums[i]);
	}

	for (int i = 0; i < 8; i++) {
		decimal += nums[i] * pow(2, 7 - i);
	}
	printf("Decimal Value : %i\n", decimal);
}
