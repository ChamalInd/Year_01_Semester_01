#include <stdio.h>

int main() {
	int read1, read2;
	int units;
	float cost, fixed, tax;

	printf("----------Electricity Billing System----------\n\n");
	
	while (1) {
		printf("Enter the previous meter reading: ");
		scanf("%d", &read1);
		printf("Enter the current meter reading: ");
		scanf("%d", &read2);
		
		if ((read1 > 0) && (read2 > 0) && (read2 > read1)) {
			break;
		} else {
			printf("Error: Invalid Inputs\n\n");
		}
	}

	units = read2 - read1;
	
	if (units < 30) {
		cost = units * 10.0;
		fixed = 75.0;
	} else if (units < 60) {
		cost = (30.0 * 10.0) + ((units - 30) * 30.0);
		fixed = 200;
	} else if (units < 90) {
		cost = (30.0 * 10.0) + (30.0 * 30.0) + ((units - 60) * 50.0);
		fixed = 400.0;
	} else if (units < 120) {
		cost = (30.0 * 10.0) + (30.0 * 30.0) + (30.0 * 50.0) + ((units - 90) * 70.0);
		fixed = 1000.0;
	} else if (units < 180) {
		cost = (30.0 * 10.0) + (30.0 * 30.0) + (30.0 * 50.0) + (30.0 * 70.0) + ((units - 120) * 110.0);
		fixed = 1500.0;
	} else {
		cost = (30.0 * 10.0) + (30.0 * 30.0) + (30.0 * 50.0) + (30.0 * 70.0) + (60.0 * 110.0) + ((units - 180) * 130.0);
		fixed = 2000.0;
	} 
		
	tax = (cost + fixed) * 18.0 / 100.0;
	
	printf("\nUnits Used : %11d\nCharge for Units : %8.2f\nFixed Charge : %12.2f\nVAT : %21.2f\n\nMonthly Bill : %12.2f\n", units, cost, fixed, tax, cost + fixed + tax);	
	
	return 0;
}
