#include <stdio.h>

int main() {
	FILE *fp;
	char filename[100], string[100];
	int pos;

	printf("Enter a filename: ");
	scanf("%s", filename);

	fp = fopen(filename, "r+");
	if (fp != NULL) {
		printf("Enter a string: ");
		scanf("%s", string);
		printf("Position: ");
		scanf("%i", &pos);

		fseek(fp, pos, SEEK_SET);
		fputs(string, fp);
	} else {
		printf("File dont exists\n");
	}

	fclose(fp);

	return 0;
}
