// thread.c
//
// Play code for using the POSIX thread library and make.
// (c) 2016 zubernetes
#include <stdio.h>
#include <pthread.h>

int pthread_create(pthread_t* thread, const pthread_attr_t* attr,
					void*(*start_routine)(void *), void *arg);
void print(void);

int main(void) {
	print();
}

void print(void) {
	printf("Hello World.\n");
}
