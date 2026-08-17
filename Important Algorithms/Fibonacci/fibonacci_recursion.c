#include <stdio.h>
#include <time.h>

long long int fib_fun(int n);

int main() {
    int n;
    long long int fib;
    clock_t start, end;

    printf("Enter the term : ");
    scanf("%i", &n);

    start = clock();
    fib = fib_fun(n);
    end = clock();

    printf("Fibonacci term is : %lli\n", fib);
    printf("Execution time : %lf\n", ((double) (end - start)) / CLOCKS_PER_SEC);

    return 0;
}

long long int fib_fun(int n) {
    if (n <= 1) {
        return n;
    }

    return fib_fun(n - 1) + fib_fun(n - 2);
}