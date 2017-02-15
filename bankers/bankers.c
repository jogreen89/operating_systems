// bankers.c
//
// A C implementation of the Bankers Algorithm
// 2016 (c) zubernetes
#include "reader.h"
#include <stdio.h>
#include <stdlib.h>

#define CMDLINE 2
#define BUF_SIZE 50

// Display the Bankers Algorithm simulation to STDOUT
void print_simulation(Simulation*);

// Display the NEED column of Bankers to STDOUT
void print_need(Simulation*);

// Run safety algorithm in Bankers, return a
// SAFE or UNSAFE code upon completion.
int safety_algorithm(Simulation*, char*);

int main (int argc, char **argv) {
    int i;
    _Bool deadlock;
    char action[BUF_SIZE], request_v[BUF_SIZE];
    void *filename;
    struct Simulation *s;

    // Check for input FILE path
    if (argc < CMDLINE || argc > CMDLINE) {
        printf("Usage: bankers input_file\n");
        return 0;
    }

    // Handle File I/O
    filename = argv[1];

    // Create Bankers Simulation object
    s = readInFile(filename);

    // Report 'input_file'
    print_simulation(s);

    // Run Bankers Algorithm
    while (deadlock) {
        deadlock = safety_algorithm(s, action);

        // If there isn't a deadlock, prompt for a Request
        if (deadlock) {
            int request_len = s->_m;
            int input = 0;
            printf("Any request?<Y/N>:");
            scanf("%s", action);
            if (strcmp(action, "Y") == 0 || strcmp(action, "y") == 0) {
                printf("please input request in format <pid> X X X X:\n<pid>");
                scanf("%s", action);
                while (input < request_len) {
                    printf("Enter a resource value:\n");
                    scanf("%s", &request_v[input]);
                    printf("%s\n", &request_v[input]);
                    input++;
                }
            }
            else
                break;
        }
    }
    free(s);

    return 0;
}

// Display the NEED column of Bankers to STDOUT
void print_need(Simulation *s) {
   int i, j;

    printf("Need:\n");
    for (i = 0; i < s->_n; i++) {
        for (j = 0; j < s->_m; j++) {
            printf("%d\t", (s->_max[i][j] - s->_allocation[i][j]));
        }
        printf("\n");
    }
}

// Display the Bankers Algorithm simulation to STDOUT
void print_simulation(Simulation *s) {
    int i, j;

    printf("Available:\n");
    for (i = 0; i < s->_m; i++)
        printf("%d\t", s->_available[i]);

    printf("\nMax:\n");
    for (i = 0; i < s->_n; i++) {
        for (j = 0; j < s->_m; j++) {
            printf("%d\t", s->_max[i][j]);
        }
        printf("\n");
    }

    printf("Allocation\n");
    for (i = 0; i < s->_n; i++) {
        for (j = 0; j < s->_m; j++) {
            printf("%d\t", s->_allocation[i][j]);
        }
        printf("\n");
    }
}

// Run the safety algorithm in Bankers, return a
// SAFE or UNSAFE code upon completion.
int safety_algorithm(Simulation *s, char *request) {
    int allocation[s->_n][s->_m], max[s->_n][s->_m], available[s->_m];
    int alloc[3] = {0, 0, 0};
    int maxres[s->_m], running[s->_m], safe = 0, safe_sequence[s->_n];
    int count = 0, i, j, exec, r = s->_m, p = s->_n, k = 0;
    _Bool deadlock = 1;

    // Intialization of running
    for (i = 0; i < p; i++) {
        running[i] = 1;
        count++;
    }

    // Initialization of alloc[], the currently allocated resources.
    for (i = 0; i < r; i++)
        alloc[i] = 0;

    // Setup Available Table
    for (i = 0; i < r; i++) {
        available[i] = s->_available[i];
    }

    // Setup Resource Table
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            allocation[i][j] = s->_allocation[i][j];
        }
    }

    // If a Request Edge is made, modify Allocation Table
    // for the process making a new request.
    if (request != NULL) {
        int pid;
        printf("This is your Request Edge: %s\n", request);
        printf("This is your <pid>: %c\n", request[0]);
        pid = atoi(&request[0]);
        printf("This is your <pid> (int): %d\n", pid);
    }

    // Setup Max Table
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            max[i][j] = s->_max[i][j];
        }
    }

    // Setup "Currently" Allocated Table
    for (i = 0; i < p; i++) {
        for (j = 0; j < r; j++) {
            alloc[j] += allocation[i][j];
        }
    }

    while (count != 0) {
        safe = 0;
        for (i = 0; i < p; i++) {
            if (running[i]) {
                exec = 1;
                for (j = 0; j < r; j++) {
                    if (max[i][j] - allocation[i][j] > available[j]) {
                        exec = 0;
                        break;
                    }
                }

                if (exec) {
                    safe_sequence[k] = i + 1;
                    k++;
                    running[i] = 0;
                    count--;
                    safe = 1;

                    for (j = 0; j < r; j++) {
                        available[j] += allocation[i][j];
                    }

                    break;
                }
            }
        }
        if (!safe) {
            for (i = 0; i < s->_n; i++) {
                printf("P%d is deadlocked!\n", i);
            }
            break;
        }
    }
    if (deadlock) {
        print_need(s);
        printf("we are safe!\n");
        printf("Safe sequence: <");
        for (i = 0; i < p; i++) {
            if (i == p - 1)
                printf("P%d", safe_sequence[i]);
            else
                printf("P%d, ", safe_sequence[i]);
        }
        printf(">\n");
        return 1;
    } else {
        return 0;
    }
}
