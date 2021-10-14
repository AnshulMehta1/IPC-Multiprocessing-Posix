#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>
int main(int argc, char *argv[]){
    pid_t pid;
    pid=fork();
    printf("Pid %d\n",getpid());
    if (pid<0){
        perror("Fork c");
        exit(EXIT_FAILURE);
    }
    else if (pid==0){
        printf("Inside child Process");
        printf("Now calling the parent process");
        char *args[]={"sample","c","programming",NULL};
        execv("./sample",args);
    }
 
        return 0;

    
}