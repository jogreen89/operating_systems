// philosopher.c
//
// A POSIX threads solution to the
// Dining Philosophers Problem, a classic
// problem of synchronization.
// (c) 2016 zubernetes
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define NTHREADS 5
#define DELAY 5000
#define FOOD_ON_TABLE 50

void *dining_philosopher(void *id);
void pickup_chopsticks(int, int, char*);
void return_chopsticks(int, int);
int food_on_table();

pthread_mutex_t chopstick[NTHREADS];
pthread_t philo[NTHREADS];
pthread_mutex_t food_lock;

/* Sleep the philospher for 3 seconds so */
/* everyone can finish eating.           */
int sleep_seconds = 3;

int main(int argn, char **argv) {
    pthread_mutex_init(&food_lock, NULL);

    for (int i = 0; i < NTHREADS; i++) 
        pthread_mutex_init(&chopstick[i], NULL);
    for (int j = 0; j < NTHREADS; j++) {
        /* Create independent threads each of which will execute function */
        pthread_create(&philo[j], NULL, dining_philosopher, (void*)j);
    }
    for (int k = 0; k < NTHREADS; k++) { 
        /* Wait till threads are complete before main continues. Unless we */
        /* wait we run the risk of executing an exit which will terminate  */
        /* the process and all threads before the threads have completed.  */
        pthread_join(philo[k], NULL);
    }
	return 0;
}

void *dining_philosopher(void *num) {
    int id;          /* Philosophers 0, 1,...,4 are thinking at this point */
    int i, left_chopstick, right_chopstick, food;
    id = (int)num;
    right_chopstick = id;
    left_chopstick = id + 1;
    printf("Philosopher %d is done thinking and now ready to eat.\n", id);

    /* Wrap around the chopsticks */
    if (left_chopstick == NTHREADS)
        left_chopstick = 0;

    while ((food = food_on_table())) {    // there is still food on the table
        if (id == 1)                      
            sleep (sleep_seconds);

        pickup_chopsticks(id, right_chopstick, "right ");
        pickup_chopsticks(id, left_chopstick,  "left ");
        
        printf("Philosopher %d is eating.\n", id);
        usleep(DELAY * (FOOD_ON_TABLE - food + 1));  // Philosopher is eating.
        return_chopsticks(left_chopstick, right_chopstick);
    }
    
    printf("Philosopher %d is done eating.\n", id);
    return (NULL);
}

int food_on_table() {
    static int food_available = FOOD_ON_TABLE;
    int myfood;

    pthread_mutex_lock(&food_lock);

    // Critical Section
    if (food_available > 0)     /* Change the number       */
        food_available--;       /* of philosophers eating  */  
    myfood = food_available;    /* at the table at a time. */  

    pthread_mutex_unlock(&food_lock);

    return myfood;
}
        
void pickup_chopsticks(int philosopher_number, int c, char *hand) {
    pthread_mutex_lock(&chopstick[c]);
    printf("Philosopher %d: got %s chopstick %d\n", 
            philosopher_number, hand, c);
}

void return_chopsticks(int chopstick1, int chopstick2) {
    pthread_mutex_unlock (&chopstick[chopstick1]);
    pthread_mutex_unlock (&chopstick[chopstick2]);
}
