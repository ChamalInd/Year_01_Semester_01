#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ACTIVITIES 100
#define TRUE  1
#define FALSE 0

typedef struct {
    int start;
    int end;
    char *activity;
} Activity;

void sort_activities(int start[], int end[], char *activity[]);
int select_activities(int start[], int end[], char *activity[], Activity selected[], int n);

int main() {
    clock_t start_t, end_t;

    // with 6 items
    // int start[ACTIVITIES] = {2, 6, 4, 10, 13, 7};
    // int end[ACTIVITIES] = {5, 10, 8, 12, 14, 15};
    // char *activities[ACTIVITIES] = {"Homework", "Presentation", "Term Paper", "Swimming Practice", "Study Time", "Hang out with friends"};

    // with 100 items
    int start[ACTIVITIES] = {54, 12, 78, 3, 91, 22, 67, 45, 8, 33, 89, 15, 41, 76, 2, 59, 95, 27, 64, 19, 82, 38, 50, 11, 73, 98, 31, 6, 47, 85, 24, 61, 17, 55, 90, 35, 79, 4, 43, 68, 14, 88, 29, 70, 52, 9, 46, 81, 21, 63, 94, 37, 75, 1, 58, 84, 26, 49, 13, 69, 32, 96, 42, 7, 72, 87, 18, 57, 92, 25, 65, 10, 48, 83, 34, 77, 5, 53, 97, 39, 20, 60, 86, 44, 71, 16, 93, 28, 66, 30, 80, 56, 23, 74, 36, 99, 40, 62, 51, 100};
    int end[ACTIVITIES] = {58, 16, 82, 7, 95, 26, 71, 49, 12, 37, 93, 19, 45, 80, 6, 63, 99, 31, 68, 23, 86, 42, 54, 15, 77, 102, 35, 10, 51, 89, 28, 65, 21, 59, 94, 39, 83, 8, 47, 72, 18, 92, 33, 74, 56, 13, 50, 85, 25, 67, 98, 41, 79, 5, 62, 88, 30, 53, 17, 73, 36, 100, 46, 11, 76, 91, 22, 61, 96, 29, 69, 14, 52, 87, 38, 81, 9, 57, 101, 43, 24, 64, 90, 48, 75, 20, 97, 32, 70, 34, 84, 60, 27, 78, 40, 103, 44, 66, 55, 104};
    char *activities[ACTIVITIES] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "A10", "A11", "A12", "A13", "A14", "A15", "A16", "A17", "A18", "A19", "A20", "A21", "A22", "A23", "A24", "A25", "A26", "A27", "A28", "A29", "A30", "A31", "A32", "A33", "A34", "A35", "A36", "A37", "A38", "A39", "A40", "A41", "A42", "A43", "A44", "A45", "A46", "A47", "A48", "A49", "A50", "A51", "A52", "A53", "A54", "A55", "A56", "A57", "A58", "A59", "A60", "A61", "A62", "A63", "A64", "A65", "A66", "A67", "A68", "A69", "A70", "A71", "A72", "A73", "A74", "A75", "A76", "A77", "A78", "A79", "A80", "A81", "A82", "A83", "A84", "A85", "A86", "A87", "A88", "A89", "A90", "A91", "A92", "A93", "A94", "A95", "A96", "A97", "A98", "A99", "A100"};

    Activity selected[ACTIVITIES];
    
    sort_activities(start, end, activities);
    start_t = clock();
    int n = select_activities(start, end, activities, selected, 0);
    end_t = clock();

    for (int i = 0; i < n; i++) {
        printf("Activity : %s\nStarts at : %i\nEnds at : %i\n\n", selected[i].activity, selected[i].start, selected[i].end);
    }
    printf("\nExecution time : %lf\n", ((double) (end_t - start_t)) / CLOCKS_PER_SEC);
    return 0;
}

int select_activities(int start[], int end[], char *activity[], Activity selected[], int n) {
    for (int i = 0; i < ACTIVITIES; i++) {
        if (i == 0 || start[i] >= selected[n - 1].end) {
            selected[n].start = start[i];
            selected[n].end = end[i];
            selected[n].activity = activity[i];
            n++;
        }
    }
    return n;
}

void sort_activities(int start[], int end[], char *activity[]) {
    int swapped = TRUE, temp1, temp2;
    char *temp3;

    while (swapped) {
        swapped = FALSE;
        for (int i = 0; i < ACTIVITIES; i++) {
            if (i != ACTIVITIES - 1 && end[i] > end[i + 1]) {
                temp1 = start[i];
                start[i] = start[i + 1];
                start[i + 1] = temp1;

                temp2 = end[i];
                end[i] = end[i + 1];
                end[i + 1] = temp2;

                temp3 = activity[i];
                activity[i] = activity[i + 1];
                activity[i + 1] = temp3;

                swapped = TRUE;
            }
        }
    }
}