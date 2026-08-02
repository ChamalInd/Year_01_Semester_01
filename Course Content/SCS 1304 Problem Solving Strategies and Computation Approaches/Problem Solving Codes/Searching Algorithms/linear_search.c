#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define FOUND 1
#define NOTFOUND 0

typedef struct Search {
    int location;
    int status;
} Search;

Search linear_search(int x, int *nums, int len);

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

        start = clock();
        result = linear_search(x, nums, len);
        end = clock();

        if (result.status == FOUND) {
            printf("%i found at %i\n", x, result.location);
        } else {
            printf("Not found\n");
        }

        printf("Execution time : %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);
        return 0;

    } else {
        return -1;
    }
}

Search linear_search(int x, int *nums, int len) {
    Search result = {-1, NOTFOUND};

    for (int i = 0; i < len; i++) {
        if (nums[i] == x) {
            result.location = i;
            result.status = FOUND;
            break;
        }
    }

    return result;
}