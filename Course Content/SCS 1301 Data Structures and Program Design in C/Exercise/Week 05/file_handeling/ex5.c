#include <stdio.h>

int main() {
	char name[100];
	int entry = 1, n;
	FILE *fp;
	
	fp = fopen("student_log", "r");
	if (fp != NULL) {
		while (fscanf(fp, "%i: %s", &n, name) == 2) {
			entry++;
		}
		fclose(fp);
	} 
	printf("Enter student name: ");
	scanf("%s", name);
	fp = fopen("student_log", "a");
	fprintf(fp, "%i: %s\n", entry, name);
	fclose(fp);

	fp = fopen("student_log", "r");
	while (fgets(name, sizeof(name), fp) != NULL) {
		printf("%s", name);
	}
	fclose(fp);

	return 0;
}	
