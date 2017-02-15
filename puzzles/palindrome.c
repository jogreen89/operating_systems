// palindrome.c
//
// A small program to detect Palindromes
// from STDIN, written in C.
// 2016 (c) zubernetes
#include <stdio.h>


void isPalindrome(char*);

int main(int argc, char **argv) {
    printf("Hello, World!\n");
    isPalindrome("hello");
}

void isPalindrome(char *c) {
    printf("This is what you called: %s.\n", c);
    return;
}
