#include <stdio.h>

int main() {
	FILE *fp;
	char filename[100], buffer[100];
	int linenum = 1;
	
	printf("Enter the file name: ");
	scanf("%s", filename);

	fp = fopen(filename, "r");
	if (fp != NULL) {
		while (fgets(buffer, sizeof(buffer), fp) != NULL) {
			printf("%i: %s", linenum, buffer);
			linenum++;
		}
	} else {
		printf("File does not exists\n");
	}

	fclose(fp);

	return 0;
}
