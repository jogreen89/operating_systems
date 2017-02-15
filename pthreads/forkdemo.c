#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>

int glob = 6; 				/* external variable in initialized data */

int main()	{
	int var; 				/* automatic variable on the stack */
	pid_t pid;
	var = 88;

	printf("before fork\n"); /* we don't flush stdout */

	if ((pid = fork()) < 0) 
		printf("fork error");
	else if (pid == 0) { /* child */
		glob++; /* modify variables */
		var++;
	} else 
	 sleep(2); /* parent */

	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);

	exit(0);
}
