#include <stdio.h>

int main() {
	int total, roll;
	char name[100], buffer[100];
	float marks;
	FILE *fp;

	printf("Enter the total no. of students: ");
	scanf("%i", &total);
	
	fp = fopen("student_records.txt", "w");
	fprintf(fp, "Roll\t%-10s\tMarks\n", "Name");

	for (int i = 0; i < total; i++) {
		printf("Enter a roll number: ");
		scanf("%i", &roll);
		printf("Enter the name: ");
		scanf(" %s", name);
		printf("Enter marks: ");
		scanf("%f", &marks);

		fprintf(fp, "%03i\t%-10s\t%.2f\n", roll, name, marks);
	}

	fclose(fp);

	fp = fopen("student_records.txt", "r");
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		printf("%s", buffer);
	}
	fclose(fp);

	return 0;
}
