#include <stdio.h>

int main() {
	double weight_A = 68.0;
	double weight_B = 75.0;
	double weight_C = 50.0;

	double height_A = 1.65;
	double height_B = 1.70;
	double height_C = 1.55;

	double BMI_A = weight_A / (height_A * height_A);
	double BMI_B = weight_B / (height_B * height_B);
	double BMI_C = weight_C / (height_C * height_C);

	double avg_BMI = (BMI_A + BMI_B + BMI_C) / 3.0;

	double max_BMI, min_BMI;

	max_BMI = BMI_A * (BMI_A > BMI_B) + BMI_B * (1 - (BMI_A > BMI_B));
	max_BMI = max_BMI * (max_BMI > BMI_C) + BMI_C * (1 - (max_BMI > BMI_C));

	min_BMI = BMI_A * (BMI_A < BMI_B) + BMI_B * (1 - (BMI_A < BMI_B));
	min_BMI = min_BMI * (min_BMI < BMI_C) + BMI_C * (1 - (min_BMI < BMI_C));

	printf("Average BMI of A, B and C   : %.2f kgm^-2\n\n", avg_BMI);

	printf("Person A : \n\tBMI : %.2f kgm^-2\n", BMI_A);
	if (BMI_A > avg_BMI) {
		printf("\tYour BMI is higher than the average BMI\n");
	} else {
		printf("\tYour BMI is lower than the average BMI\n");
	}
	if (BMI_A < 24.9 && BMI_A > 18.5) {
		printf("\tYour BMI is in the normal range (18.5 , 24.9)\n\n");
	} else {
		printf("\tYour BMI is outside the normal range (18.5, 24.9)\n\n");
	}

	printf("Person B : \n\tBMI : %.2f kgm^-2\n", BMI_B);
	if (BMI_B > avg_BMI) {
		printf("\tYour BMI is higher than the average BMI\n");
	} else {
		printf("\tYour BMI is lower than the average BMI\n");
	}
	if (BMI_B < 24.9 && BMI_B > 18.5) {
		printf("\tYour BMI is in the normal range (18.5 , 24.9)\n\n");
	} else {
		printf("\tYour BMI is outside the normal range (18.5, 24.9)\n\n");
	}

	printf("Person C : \n\tBMI : %.2f kgm^-2\n", BMI_C);
	if (BMI_C > avg_BMI) {
		printf("\tYour BMI is higher than the average BMI\n");
	} else {
		printf("\tYour BMI is lower than the average BMI\n");
	}
	if (BMI_C < 24.9 && BMI_C > 18.5) {
		printf("\tYour BMI is in the normal range (18.5 , 24.9)\n\n");
	} else {
		printf("\tYour BMI is outside the normal range (18.5, 24.9)\n\n");
	}

	printf("Maximum BMI from A, B and C : %.2f kgm^-2\n", max_BMI);
	printf("Minimum BMI from A, B and C : %.2f kgm^-2\n", min_BMI);

	return 0;
}
