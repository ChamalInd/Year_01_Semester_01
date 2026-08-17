#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

void selection(int len, int *nums);

int main(int argc, char *argv[]) {
    int len;
    char buffer[100];
    FILE *fp;
    clock_t start, end;

    if (argc == 3) {
        len = atoi(argv[1]);
        fp = fopen(argv[2], "r");

        int nums[len], i = 0;

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            nums[i] = atoi(buffer);
            i++;
        }

        fclose(fp);

        start = clock();
        selection(len, nums);
        end = clock();

        fp = fopen("sorted.txt", "w");
        for (int i = 0; i < len; i++) {
            fprintf(fp, "%i\n", nums[i]);
        }
        fclose(fp);

        printf("Execution time : %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
        return 0;
    } else {
        printf("Invalid arguments\n");
        return -1;
    }
}

void selection(int len, int *nums) {
    int temp, flagged = TRUE, min, min_addr;

    while (flagged) {
        flagged = FALSE;
        for (int i = 0; i < len; i++) {
            min = nums[i];
            min_addr = i;
            for (int j = i + 1; j < len; j++) {
                if (nums[j] < min) {
                    min_addr = j;
                    min = nums[j];
                }
            }
            if (min_addr != i) {
                temp = nums[i];
                nums[i] = nums[min_addr];
                nums[min_addr] = temp;
                flagged = TRUE;
            }
        }
    }
}