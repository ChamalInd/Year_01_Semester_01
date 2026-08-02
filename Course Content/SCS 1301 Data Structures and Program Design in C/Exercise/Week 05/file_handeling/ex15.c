#include <stdio.h>

int main() {
    FILE *fp1, *fp2;
    char ch, inpf[100];
    int shifter;

    printf("Enter the input file path: ");
    scanf("%s", inpf);

    fp1 = fopen(inpf, "r");
    if (fp1 != NULL) {
        printf("Enter a number to shift: ");
        scanf("%i", &shifter);

        fp2 = fopen("decode.txt", "w");
        while ((ch = fgetc(fp1)) != EOF) {
            if (((ch >= 65) && (ch <= 90)) || ((ch >= 97) && (ch <= 122))) {
                if ((ch >= 65) && (ch <= 90)) {
                    if (ch - shifter < 65) {
                        int leftover = 65 - (ch - shifter);
                        fputc(91 - leftover, fp2);
                    } else {
                        fputc(ch - shifter, fp2);    
                    }
                } else if ((ch >= 97) && (ch <= 122)) {
                    if (ch - shifter < 97) {
                        int leftover = 97 - (ch - shifter);
                        fputc(123 - leftover, fp2);
                    } else {
                        fputc(ch - shifter, fp2);    
                    }
                }
            } else {
                fputc(ch, fp2);
            }
        }                
    } else {
        printf("File does not exists.\n");
        return -1;
    }

    fclose(fp1);
    fclose(fp2);
    return 0;
}
