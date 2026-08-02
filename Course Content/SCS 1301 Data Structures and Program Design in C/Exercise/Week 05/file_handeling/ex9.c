#include <stdio.h>

int main() {
	FILE *fp;
	char filename[100], c;
	int lines = 0, chars = 0, words = 1;

	printf("Enter the filename: ");
	scanf("%s", filename);
	
	fp = fopen(filename, "r");

	if (fp != NULL) {
		while ((c = fgetc(fp)) != EOF) {
			chars++;
			if (c == '.' || c == '?' || c == '!') {
				lines++;
			}
			if (c == ' ') {
				words++;
			}
		}

		printf("Lines: %i\nCharacters: %i\nWords: %i\n", lines, chars, words);
	} else {
		printf("File does not exists\n");
	}
	fclose(fp);
	return 0;
}
