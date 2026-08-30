#include <stdio.h>

int main()
{
	FILE *fp = fopen("numbers.txt", "r");
	int numbers[50], maximum, i = 0;

	while (fscanf(fp, "%i", &numbers[i]) != EOF)
		i++;
	fclose(fp);
	numbers[i] = '\0';
	
	printf("Numbers : ");
	for (int i = 0; numbers[i] != '\0'; i++)
	{
		printf("%i ", numbers[i]);	
	}
	printf("\n");

	maximum = numbers[0];
	for (int i = 1; numbers[i] != '\0'; i++)
	{
		if (maximum < numbers[i])
		{
			maximum = numbers[i];
		}
	}
	printf("Maximum : %i\n", maximum);
}
