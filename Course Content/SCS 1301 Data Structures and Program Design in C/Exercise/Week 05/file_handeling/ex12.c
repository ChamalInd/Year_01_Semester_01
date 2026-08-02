#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char file1[256], file2[256], output[256];

    printf("Enter first input filename: ");
    fgets(file1, sizeof(file1), stdin);
    file1[strcspn(file1, "\n")] = '\0';

    printf("Enter second input filename: ");
    fgets(file2, sizeof(file2), stdin);
    file2[strcspn(file2, "\n")] = '\0';

    printf("Enter output filename: ");
    fgets(output, sizeof(output), stdin);
    output[strcspn(output, "\n")] = '\0';

    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    FILE *out = fopen(output, "w");

    if (!f1 || !f2 || !out) {
        printf("Error: Cannot open files.\n");
        return 1;
    }

    int a, b;
    int has_a = (fscanf(f1, "%d", &a) == 1);
    int has_b = (fscanf(f2, "%d", &b) == 1);

    while (has_a && has_b) {
        if (a <= b) {
            fprintf(out, "%d\n", a);
            has_a = (fscanf(f1, "%d", &a) == 1);
        } else {
            fprintf(out, "%d\n", b);
            has_b = (fscanf(f2, "%d", &b) == 1);
        }
    }

    while (has_a) {
        fprintf(out, "%d\n", a);
        has_a = (fscanf(f1, "%d", &a) == 1);
    }

    while (has_b) {
        fprintf(out, "%d\n", b);
        has_b = (fscanf(f2, "%d", &b) == 1);
    }

    fclose(f1);
    fclose(f2);
    fclose(out);
    return 0;
}
