// fibo.c
//
// A small, recursive Fibonacci
// Series program written in C.
// 2016 (c) zubernetes
#include <stdio.h>

// Calculate the nth Number of the Fibonacci Series
int fib(int);

int main(int argc, char **argv) {
    int n = 0;
    printf("Welcome to the Fibo Program.\n");
    printf("Please enter the nth Number: ");
    scanf("%d", &n);

    int result = fib(n);

    printf("The %dth Fibonacci Number is %d.\n", n, result);
}

// Calculate the nth Number of the Fibonacci Series
int fib(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return (fib(n-1) + fib(n-2));
}
