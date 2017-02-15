// exforkexample.c
//
// An example of using fork(), execvp(), and wait()
// systems calls.
// (c) 2016 zubernetes

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
 pid_t pid;
 /* fork a child process */
 pid = fork();
 if (pid < 0) { /* error occurred */
	fprintf(stderr, "Fork Failed");
	return 1;
 } else if (pid == 0) { /* child process */
	// execlp is a variant of 'ls'
	execlp("/bin/ls","ls",NULL);
	// ls did not return control to output buffer
	printf("Child Complete\n");
 } else { /* parent process */
	/* parent will wait for the child to complete */
	wait(NULL);
	printf("Parent complete\n");
 }
	return 0;
}
