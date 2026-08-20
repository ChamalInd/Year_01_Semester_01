#include <stdio.h>
#include <math.h>
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

Search jump_search(int x, int len, int *nums);
int min(int n1, int n2);
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
        result = jump_search(x, len, nums);
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

int min(int n1, int n2)
{
	if (n1 < n2) return n1;
	else return n2;
}

Search jump_search(int x, int len, int *nums) {
	int block_size = sqrt(len);
	int prev_ptr = 0;
	int current_ptr = block_size;

	Search result;

	while (1)
	{
		int step = min(current_ptr, len - 1);
	
		if (nums[step] == x)
		{
			result.location = step;
			result.status = FOUND;
			return result;
		}
		else if (nums[step] > x)
		{
			for (int i = step; i > prev_ptr; i--)
			{
				if (nums[i] == x)
				{
					result.location = i;
					result.status = FOUND;
					return result;
				}
			}
			result.location = -1;
			result.status = NOTFOUND;
			return result;
		}

		if (step == len - 1)
		{
			result.location = -1;
			result.status = NOTFOUND;
			return result;
		}
		
		current_ptr += block_size;
		prev_ptr += block_size;
	}
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
