#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input_filename[256];
    char output_filename[256];

    printf("Enter input filename: ");
    fgets(input_filename, sizeof(input_filename), stdin);
    input_filename[strcspn(input_filename, "\n")] = '\0';

    printf("Enter output filename: ");
    fgets(output_filename, sizeof(output_filename), stdin);
    output_filename[strcspn(output_filename, "\n")] = '\0';

    FILE *infile = fopen(input_filename, "r");
    if (!infile) {
        printf("Error: Cannot open file '%s'\n", input_filename);
        return 1;
    }

    int capacity = 100;
    int count = 0;
    char **lines = malloc(capacity * sizeof(char *));
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), infile)) {
        if (count >= capacity) {
            capacity *= 2;
            lines = realloc(lines, capacity * sizeof(char *));
        }
        lines[count] = malloc(strlen(buffer) + 1);
        strcpy(lines[count], buffer);
        count++;
    }
    fclose(infile);

    FILE *outfile = fopen(output_filename, "w");
    if (!outfile) {
        printf("Error: Cannot create file '%s'\n", output_filename);
        return 1;
    }

    for (int i = count - 1; i >= 0; i--) {
        fputs(lines[i], outfile);
        free(lines[i]);
    }

    free(lines);
    fclose(outfile);
    return 0;
}
