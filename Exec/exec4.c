#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>
/* Self exec */

int main(int argc, char *argv[]){
    printf("Exec Demo: my pid is %d\n", getpid());
    char *args[] = {"./exec4", "Hello", NULL};
    execvp(args[0], args);
    printf("FAREWELL :((");
    return 0;
   
    return 0;

}