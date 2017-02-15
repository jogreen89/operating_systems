// char_search.c
//
// A small program from "The Principle of
// Programming" by Kernighan & Pike.
// 2016 (c) zubernetes
#include <stdio.h>

char *flab[] = {
    "actually",
    "just",
    "quite",
    "really",
    NULL
};

int lookup(char*, char**);

int main(int argc, char **argv) {
    printf("Hello, World!\n");
    char *a = "actually";
    int x = lookup(a, flab);
    printf("The word %s was found at index %d.\n", a, (x + 1));
    return 0;
}

int lookup(char *word, char *array[]) {
    int i;

    for (i = 0; array[i] != NULL; i++)
        if (strcmp(word, array[i]) == 0)
            return i;
    return -1;
}
