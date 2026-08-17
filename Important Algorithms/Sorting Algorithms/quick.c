#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void quick_sort(int low, int high, int *nums);

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
        quick_sort(0, len - 1, nums);
        end = clock();

        fp = fopen("sorted.txt", "w");
        for (i = 0; i < len; i++) {
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

void quick_sort(int low, int high, int *nums) {
    if (low < high) {
        int pivot = nums[high], temp, i = low - 1, j;

        for (j = low; j < high; j++) {
            if (nums[j] <= pivot) {
                i++;
                temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }

        // printf("%i %i\t", low, high);
        // for (int k = 0; k < high; k++) {
        //     printf("%i ", nums[k]);
        // }
        // printf("\n");

        temp = nums[i + 1];
        nums[i + 1] = nums[high];
        nums[high] = temp;

        quick_sort(low, i, nums);
        quick_sort(i + 2, high, nums);
    }
}