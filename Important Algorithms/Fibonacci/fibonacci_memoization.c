#include <stdio.h>
#include <time.h>

long long int fib_fun(int n, long long int *memo);

int main() {
    int n;
    long long int fib;
    clock_t start, end;

    printf("Enter the term : ");
    scanf("%i", &n);

    long long int memo[n];

    for (int i = 0; i < n; i++) {
        memo[i] = 0;
    }

    start = clock();
    fib = fib_fun(n, &memo[0]);
    end = clock();

    printf("Fibonacci term is : %lli\n", fib);
    printf("Execution time : %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    return 0;
}

long long int fib_fun(int n, long long int *memo) {
    for (int i = 0; i < n; i++) {
        if (memo[i] == n) {
            return memo[n];
        }
    }

    if (n <= 1) {return n;}

    memo[n] = fib_fun(n - 1, memo) + fib_fun(n - 2, memo);

    return memo[n];
}