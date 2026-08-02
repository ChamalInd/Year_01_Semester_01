#include <stdio.h>

int main() {
	FILE *fp;
	char filename[100], string[100], rest[500];
	int pos;

	// Observation: When the content to be preserved from the file exceeds 
	// the size of the 'rest' array (500 bytes), fgets only reads up to 499 bytes. 
	// As a result, any data in the file beyond 500 bytes is truncated and lost 
	// when fputs writes 'rest' back to the file. The program does NOT behave 
	// correctly under this condition, as it causes data loss for larger files.

	printf("Enter a filename: ");
	scanf("%s", filename);

	fp = fopen(filename, "r+");
	if (fp != NULL) {
		printf("Enter a string: ");
		scanf("%s", string);
		printf("Position: ");
		scanf("%i", &pos);

		fseek(fp, pos, SEEK_SET);
		fgets(rest, sizeof(rest), fp);
		fseek(fp, pos, SEEK_SET);
		fputs(string, fp);
		fputs(rest, fp);
		
	} else {
		printf("File dont exists\n");
	}

	fclose(fp);

	return 0;
}
