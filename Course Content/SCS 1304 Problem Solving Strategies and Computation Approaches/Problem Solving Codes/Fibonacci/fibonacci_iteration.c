#include <stdio.h>
#include <time.h>

int main() {
    long long int n, fib, prev;
    clock_t start, end;

    printf("Enter the term : ");
    scanf("%lli", &n);

    start = clock();
    for (int i = 0; i <= n; i++) {
        if (i <= 1) { fib = i; prev = i - 1; continue;}

        fib = fib + prev;
        prev = fib - prev;
    }
    end = clock();

    printf("Fibonacci term is : %lli\n", fib);
    printf("Execution time : %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    return 0;
}