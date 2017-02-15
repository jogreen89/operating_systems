// shell.c
//
// Barebones osh program in C 
// 2016 (c) zubernetes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pid_t wait(int *status);
void  exit(int status);

int main(int argc, char **argv) {
    // history buffer size
    char line[1024];
    bool status = true;

    while (status) {
        printf("osh> ");
        gets(line);
        parse(line, argv);

        if (strcmp(argv[0], "exit") == 0)
            exit(0);
        else if (strcmp(argv[0], "!!") == 0) 
            launch_osh(argv);
        else 
            launch_osh(argv);
            
    }
}

void parse(char *line, char **argv) {
    while (*line != '\0') 
        while (*line == ' ' || *line == '\t' || *line == '\n')
            *line++ = '\0';

    *argv++ = line;

    while (*line != '\0' && *line != ' ' && *line != '\t' && '\n')
        line++;
}

void launch_osh(char **argv) {
    pid_t pid;
    int status;

    // create a new process
    pid = fork();

    if (pid < 0) {
        printf("Fork Failed.\n");
        exit(1);
    } else if (pid == 0) {
        if (execvp(*argv, argv) < 0) {
            printf("***Error: exec failed.\n");
            exit(1);
        }
    } else {
        while (wait(&status) != pid)
            ;
    }
}
