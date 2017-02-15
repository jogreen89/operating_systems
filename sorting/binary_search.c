// binary_search.c
//
// A C implementation of Binary Search algorithm.
// Worst Case O(log n), Best Case O(1)
// (c) 2016 zubernetes
#include <stdio.h>

#define BUF_SIZE 10

int findmin(int a[], int n);
int BinarySearch(int a[], int key, int low, int high);

int main(int argc, char **argv) {
	int a[BUF_SIZE] = {15, 21, 39, 44, 52, 71, 94, 154, 204, 322};
	int b[BUF_SIZE] = {9, 11, 22, 31, 45, 53, 69, 71, 88, 94};
	int c[BUF_SIZE] = {4, 11, 3, 19, 20, 2, 74, 1, 32, 41};

	int len = sizeof(b) / sizeof(b[0]);
	printf("Binary Search:\n");

	// Test Suite 1
	int pos = BinarySearch(b, 22, 0, 9);
	printf("The key was found at position %d\n", pos);

	// Test Suite 2
	int pos_two = BinarySearch(b, 71, 0, 9);
	printf("The key was found at position %d\n", pos_two);

	// Test Suite 3
	len = sizeof(c) / sizeof(c[0]);
	int min = findmin(c, len);
	printf("The minimum value found was %d\n", min);

	return 0;
}

int BinarySearch(int a[], int key, int low, int high) {
    int len = high - low + 1;
	if (low < high) {
		int mid = (low + high) / 2;
		if (a[mid] == key) {
        	printf("a[mid] is %d\n", a[mid]);
			return mid;
		} else if (a[mid] > key)
			return BinarySearch(a, key, low, mid-1);
		  else if (a[mid] < key)
			return BinarySearch(a, key, mid + 1, high);
	}
	return 0;
}

int findmin(int a[], int n) {
	// return the minimum element in a[]
	// worst case time complexity of findmin is theta(n)
	int min = 0;
	for (int i = 0; i < n; i++) {
		if (i == 0)
			min = a[i];
		if (a[i] > a[i+1])
			min = a[i+1];
	}
	return min;
}
