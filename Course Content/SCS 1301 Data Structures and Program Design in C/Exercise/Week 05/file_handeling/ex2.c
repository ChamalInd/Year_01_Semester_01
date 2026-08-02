#include <stdio.h>

int main() {
	FILE *fp;
	char filename[100], line[100], c;

	printf("Enter a file name: ");
	scanf("%s", filename);
	scanf("%c", &c);

	fp = fopen(filename, "r");
	
	if (fp == NULL) {
		fclose(fp);
		fp = fopen(filename, "w");
		
		printf("Enter a line of text: ");
		fgets(line, sizeof(line), stdin);

		fprintf(fp, "%s", line);

		fclose(fp);
	} else {
		printf("File already exists\n");
	}

	return 0;
}
