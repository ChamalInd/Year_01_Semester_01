#include <stdio.h>

int main() {
	FILE *fp1, *fp2;
	char buffer[100], file1[100], file2[100];

	printf("Enter the name of source file: ");
	scanf("%s", file1);
	printf("Enter the name of destination file: ");
	scanf("%s", file2);

	fp1 = fopen(file1, "r");
	fp2 = fopen(file2, "w");

	if (fp1 != NULL) {
		while (fgets(buffer, sizeof(buffer), fp1) != NULL) {
			fputs(buffer, fp2);
		}
	} else {
		printf("File doesn't exists\n");
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}	
