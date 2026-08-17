#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void merge_sort(int len, int *nums);

int main(int argc, char *argv[]) {
    int len, i = 0;
    char buffer[100];
    FILE *fp;
    clock_t start, end;

    if (argc == 3) {
        len = atoi(argv[1]);
        fp = fopen(argv[2], "r");

        int nums[len];

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            nums[i] = atoi(buffer);
            i++;
        }

        fclose(fp);

        start = clock();
        merge_sort(len, nums);
        end = clock();

        fp = fopen("sorted.txt", "w");
        for (i = 0; i < len; i++) {
            fprintf(fp, "%i\n", nums[i]);
        }
        fclose(fp);

        printf("Execution time : %lf\n", ((double) (end - start) / CLOCKS_PER_SEC));
        return 0;
    } else {
        printf("Invalid arguments\n");
        return -1;
    }
}

void merge_sort(int len, int *nums) {
    if (len > 1) {
        int mid = len / 2, j = 0, k = 0, i;
        int left_list[mid], right_list[len - mid];

        for (i = 0; i < len; i++) {
            if (i < mid) {
                left_list[j] = nums[i];
                j++;
            } else {
                right_list[k] = nums[i];
                k++;
            }
        }

        merge_sort(mid, left_list);
        merge_sort(len - mid, right_list);

        // printf("%i\t", len);

        // for(i = 0; i < mid; i++) {
        //     printf("%i ", left_list[i]);
        // }
        // printf("\t");
        // for(i = 0; i < len - mid; i++) {
        //     printf("%i ", right_list[i]);
        // }
        // printf("\n");

        i = 0, j = 0, k = 0;

        while (i < mid && j < (len - mid)) {
            if (left_list[i] < right_list[j]) {
                nums[k] = left_list[i];
                i++;
            } else {
                nums[k] = right_list[j];
                j++;
            }
            k++;
        }

        while (i < mid) {
            nums[k] = left_list[i];
            i++;
            k++;
        }

        while (j < len - mid) {
            nums[k] = right_list[j];
            j++;
            k++;
        }  
    }
}