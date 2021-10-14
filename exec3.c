#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>
int num = 10;

int main(int argc, char *argv[]) {
    printf("Exec Demo: my pid is %d\n", getpid());
    // Pela ni P_id
    char *args[] = {"./helloExec", NULL};
    // Calling HelloExec .C
    /*
        v: vector i.e array
        l: comma sep values
        p: 
    */
    execvp(args[0], args);
    // args 0 is always the file name so helloexex filename che ne Null terminated strings follow

    printf("BYE!");
    return 0;
}