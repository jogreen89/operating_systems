// sum_diagonal.c
//
// Solution to calculate the absolute difference
// between the sums of the diagonals of an N x N
// matrix.
// 2016 (c) zubernetes
#include <math.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int n,
        i = 0,
        j = 0,
        k = 0,
        fSum = 0,
        bSum = 0,
        diff = 0;

    scanf("%d", &n);
    k = n - 1;
    int a[n][n];

    for (i; i < n; i++) {
        for (j; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
        fSum = fSum + a[i][i];
        bSum = bSum + a[i][k];
        k--;
    }

    diff = abs(fSum - bSum);
    printf("%d", diff);
    
    return 0;
}
