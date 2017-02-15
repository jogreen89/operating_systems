// reader.h
//
// A C implementation of the Bankers Algorithm
// 2016 (c) zubernetes
#ifndef READER_H
#define READER_H

// C Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Simulation Header
#include "simulation.h"

#define BUFFER_SIZE 100

/**
    Reads a FILE and generates a Simulation object
*/
Simulation* readInFile(char*);

/**
    Reads a FILE and generates a Simulation object
*/
Simulation* readInFile(char *c) {
    FILE *open_file;
    int *available, *allocation, *max;
    char buffer[BUFFER_SIZE];
    int n = 0, m = 0, i = 0, j = 0, k = 0, pos = 0;
    struct Simulation *s;
    s = (struct Simulation*) malloc(sizeof(Simulation));

    open_file = fopen(c, "r");

    while (fscanf(open_file, "%s", buffer) != EOF) {
        if (strcmp(buffer, "n") == 0) {
            fscanf(open_file, "%s", buffer);
            n = atoi(buffer);
            s->_n = n;
        }

        if (strcmp(buffer, "m") == 0) {
            fscanf(open_file, "%s", buffer);
            m = atoi(buffer);
            s->_m = m;
        }

        if (strcmp(buffer, "Available") == 0) {
            s->_available = (int*) malloc(sizeof(s->_m));
            for (i = 0; i < s->_m; i++) {
                fscanf(open_file, "%s", buffer);
                k = atoi(buffer);
                s->_available[i] = k;
            }
        }

        if (strcmp(buffer, "Allocation") == 0) {
            s->_allocation = (int**) malloc(sizeof(s->_n)*s->_n);
            s->_max = (int**) malloc(sizeof(s->_n)*s->_n);

            for (i = 0; i <= s->_n; i++) {
                s->_allocation[i] = (int*) malloc(sizeof(s->_m)*s->_m);
                s->_max[i] = (int*) malloc(sizeof(s->_m)*s->_m);
            }

            i = 0;
            for (j = 0; j < (s->_n * s->_m); j++) {
                if (j % s->_m == 0 && j != 0) {
                    pos = 0;
                    i++;
                }
                fscanf(open_file, "%s", buffer);
                k = atoi(buffer);
                s->_allocation[i][pos] = k;
                pos++;
            }
            fscanf(open_file, "%s", buffer);
            i = 0, pos = 0;
            for (j = 0; j < (s->_n * s->_m); j++) {
                if (j % s->_m == 0 && j != 0) {
                    pos = 0;
                    i++;
                }
                fscanf(open_file, "%s", buffer);
                k = atoi(buffer);
                s->_max[i][pos] = k;
                pos++;
            }
        }
    }
    return s;
}
#endif
