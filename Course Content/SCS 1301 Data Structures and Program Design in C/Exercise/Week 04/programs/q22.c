#include <stdio.h>
#include <math.h>

#define LEN 100

int main() {
	int nums[] = {682, 145, 933, 421, 78, 556, 312, 894, 203, 477, 12, 639, 850, 364, 917, 158, 290, 743, 581, 49, 972, 335, 618, 88, 442, 706, 259, 113, 537, 824, 389, 196, 671, 955, 408, 27, 725, 460, 134, 598, 986, 321, 767, 54, 843, 219, 695, 436, 172, 810, 357, 942, 66, 501, 788, 284, 493, 161, 905, 627, 375, 412, 83, 759, 248, 964, 523, 109, 396, 730, 451, 876, 303, 574, 98, 650, 237, 862, 184, 515, 349, 712, 928, 46, 689, 265, 831, 547, 95, 401, 773, 211, 568, 899, 139, 604, 328, 795, 253, 981};
	int min, max;
	double avg, std_dev;
	int *ptr = &nums[0];
	
	min = max = nums[0];

	for (int i = 0; i < LEN; i++) {
		if (*ptr < min) {
			min = *ptr;
		} else if (*ptr > max) {
			max = *ptr;
		}

		avg += *ptr;
		ptr++;
	}

	avg = avg / LEN;
	
	ptr = &nums[0];

	for (int i = 0; i < LEN; i++) {
		std_dev += pow((*ptr - avg), 2);
		ptr++;
	}

	std_dev = sqrt(std_dev/(LEN - 1));

	printf("Maximum : %i\nMinimum : %i\nAverage : %.2lf\nStandard Deviation : %.2lf\n", max, min, avg, std_dev);
}
