#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
	char target[100], filename[100];
	char line[1024];
	int line_num = 0;
	int total = 0;
	FILE *fp;

	printf("Enter the filename: ");
	scanf("%s", filename);
	printf("Enter the target word: ");
	scanf("%s", target);

	fp = fopen(filename, "r");
	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {
			line_num++;
			char *pos = line;
			while ((pos = strstr(pos, target)) != NULL) {
				int before_ok = (pos == line || !isalnum((unsigned char)pos[-1]));
				int after_ok = (!isalnum((unsigned char)pos[strlen(target)]));

				if (before_ok && after_ok)
				{
					printf("Found at line %d\n", line_num);
					total++;
				}
				pos++;
			}
		}

		printf("Total occurrences: %d\n", total);
	} else {
		printf("File does not exists\n");
	}

	fclose(fp);
	return 0;
}
