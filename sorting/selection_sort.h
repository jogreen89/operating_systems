// selection_sort.h
//
// A C implementation of the basic selection sort
// algorithm. This can be easily ported because of
// of the limited library usage.
// (c) 2016 zubernetes
#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <stdio.h>

void selection_sort (int *a, int n) {
	int i, j, m, t;
	for (i = 0; i < n; i++) {
		for (j = i, m = i; j < n; j++) {
			if (a[j] < a[m]) {
				m = j;
			}
		}

		t = a[i];
		a[i] = a[m];
		a[m] = t;

	}
}

void testSelectionSort() {
	// Set of integers to be sorted.
	int a[] =  {121, 11, -11, 199, 324, 65, 2, -31, 0, 99, 2, 83, 782, 1};
	int b[] = {1, 2, 3};
	int n = sizeof a / sizeof a[0];
    int i, j;
	int size = sizeof b;

	printf("%d\n", size);

	for (i = 0; i < n; i++) {
		printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
	}
	selection_sort(a, n);
 	for (j = 0; j < n; j++) {
		printf("%d%s", a[j], j == n - 1 ? "\n" : " ");
	}
}

#endif

