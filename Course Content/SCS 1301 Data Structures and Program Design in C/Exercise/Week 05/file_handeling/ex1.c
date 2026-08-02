#include <stdio.h>

int main() {
	FILE *fp;
	char *filename, ch;

	printf("Enter the file name: ");
	scanf("%s", filename);

	fp = fopen(filename, "r");
	if (fp != NULL) {
		while ((ch = fgetc(fp)) != EOF) {
			printf("%c\n", ch);
		}
		fclose(fp);
		return 0;
	} else {
		printf("File does not exists\n");
		return 0;
	}
}
