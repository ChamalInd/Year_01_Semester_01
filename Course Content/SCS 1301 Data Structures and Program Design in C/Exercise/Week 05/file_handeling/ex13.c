#include <stdio.h>
#include <string.h>

int main() {
    char file1[256], file2[256];

    printf("Enter first filename: ");
    fgets(file1, sizeof(file1), stdin);
    file1[strcspn(file1, "\n")] = '\0';

    printf("Enter second filename: ");
    fgets(file2, sizeof(file2), stdin);
    file2[strcspn(file2, "\n")] = '\0';

    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (!f1 || !f2) {
        printf("Error: Cannot open files.\n");
        return 1;
    }

    char line1[1024], line2[1024];
    int line_num = 0;

    while (1) {
        int r1 = fgets(line1, sizeof(line1), f1) != NULL;
        int r2 = fgets(line2, sizeof(line2), f2) != NULL;

        if (!r1 && !r2) {
            printf("No difference exists.\n");
            break;
        }

        line_num++;

        if (!r1) {
            printf("First difference at line %d: '%s' (shorter file ends)\n", line_num, line2);
            break;
        }

        if (!r2) {
            printf("First difference at line %d: '%s' (shorter file ends)\n", line_num, line1);
            break;
        }

        if (strcmp(line1, line2) != 0) {
            printf("First difference at line %d:\n", line_num);
            printf("  File 1: %s", line1);
            printf("  File 2: %s", line2);
            break;
        }
    }

    fclose(f1);
    fclose(f2);
    return 0;
}
