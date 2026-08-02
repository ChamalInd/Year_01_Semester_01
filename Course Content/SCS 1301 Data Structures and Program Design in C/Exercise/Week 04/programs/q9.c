#include <stdio.h>

int findgcd(int num1, int num2);

int main() {
	int num1, num2, gcd, nums;

	printf("Enter the number of inputs : ");
	scanf("%i", &nums);

	int num_array[nums];
	
	for (int i = 0; i < nums; i++) {
		printf("Enter a number : ");
		scanf("%i", &num_array[i]);
	}

	for (int i = 1; i < nums; i++) {
		if (i == 1) {
			gcd = findgcd(num_array[i - 1], num_array[i]);
		} else {
			gcd = findgcd(gcd, num_array[i]);
		}
		if (gcd == 0) {
			break;
		}
	}
	if (gcd == 0) {
		printf("No GCD for the given number.\n");
	} else {
		printf("GCD of the numbers is %i\n", gcd);
	}
}

int findgcd(int num1, int num2) {
	int gcd = 0, min = 0;

	if (num1 < num2) {
		min = num1;
	} else {
		min = num2;
	}

	for (int i = 2; i <= min; i++) {
		if ((num1 % i == 0) && (num2 % i == 0)) {
			if (i > gcd) {
				gcd = i;
			}
		}
	}

	return gcd;
}













