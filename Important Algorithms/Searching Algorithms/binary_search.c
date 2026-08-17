#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define FOUND    1
#define NOTFOUND 0

#define TRUE  1
#define FALSE 0

typedef struct Search {
    int location;
    int status;
} Search;

Search binary_search(int x, int len, int *nums);
void bubble(int len, int *nums);

int main(int argc, char *argv[]) {
    int x, len;
    char buffer[100];
    FILE *fp;
    clock_t start, end;
    Search result;

    if (argc == 4) {
        x = atoi(argv[1]);
        len = atoi(argv[2]);
        fp = fopen(argv[3], "r");

        int i = 0, nums[len];

        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            nums[i] = atoi(buffer);
            i++;
        }

        fclose(fp);

        bubble(len, nums);

        start = clock();
        result = binary_search(x, len, nums);
        end = clock();

        if (result.status == FOUND) {
            printf("%i found at %i\n", x, result.location);
        } else {
            printf("Not found\n");
        }

        printf("Execution time : %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
        
        return 0;
    } else {
        return 1;
    }
}

Search binary_search(int x, int len, int *nums) {
    int mid = 1, left, right;
    Search result = {0, NOTFOUND};

    left = 0;
    right = len;
    
    while (left != mid && right != mid && left >= 0 && right >= 0) {
        mid = (left + right) / 2;
        
        if (nums[mid] == x) {
            result.location = mid;
            result.status = FOUND;
            break;
        } else if (nums[mid] < x) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;
}

void bubble(int len, int *nums) {
    int flagged = TRUE, temp;

    while (flagged) {
        flagged = FALSE;
        for (int i = 0; i < len; i++) {
            if (i != len - 1 && nums[i] > nums[i + 1]) {
                temp = nums[i];
                nums[i] = nums[i + 1];
                nums[i + 1] = temp;
                flagged = TRUE;
            }
        }
    }
}