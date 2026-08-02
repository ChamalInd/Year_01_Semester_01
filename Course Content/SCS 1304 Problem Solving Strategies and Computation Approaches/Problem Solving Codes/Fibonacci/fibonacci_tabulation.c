#include <stdio.h>
#include <time.h>

int main() {
    int n;
    clock_t start, end;

    printf("Enter the term : ");
    scanf("%i", &n);

    long long int table[n];

    for (int i = 0; i <= n; i++) {
        if (i == 1) {table[i] = 1; continue;}
        table[i] = 0;
    }

    start = clock();
    for (int i = 2; i <= n; i++) {
        table[i] = table[i - 1] + table[i - 2];
    }
    end = clock();

    printf("Fibonacci term is : %lli\n", table[n]);
    printf("Execution time : %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    return 0;
}