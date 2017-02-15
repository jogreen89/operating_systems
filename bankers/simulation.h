// simulation.h
//
// A C implementation of the Bankers Algorithm
// 2016 (c) zubernetes
#ifndef SIMULATION_H
#define SIMULATION_H

typedef struct Simulation Simulation;

struct Simulation {
    int    _n;
    int    _m;
    int*   _available;
    int**  _allocation;
    int**  _max;
};

/**
    Determines with the Simluation object contains a
    safe sequence.
*/
int* findSafeSequence(Simulation*);

/**
    Determines with the Simluation object contains a
    safe sequence.
*/
int* findSafeSequence(Simulation *s) {
    int i, j;
    int *min;
    for (i = 0; i < s->_n; i++) {
        if (i == 0)
            min = s->_allocation[i];
        if (s->_allocation[i][0] > s->_allocation[i+1][0])
            min = s->_allocation[i+1];
        if (s->_allocation[i][0] == s->_allocation[i+1][0]) {
            if (s->_allocation[i][1] > s->_allocation[i+1][1])
                min = s->_allocation[i+1];
        }
    } return min;
}

#endif
