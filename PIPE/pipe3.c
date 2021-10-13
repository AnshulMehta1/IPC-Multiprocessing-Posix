// Code To Demonstrate the Pipe and Fork System Calls

#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>
#define MSGSIZE 16
int main(){
    char buffer[MSGSIZE];
    int p[2]; // pipe file descriptors
    pipe(p);
    printf("%d %d\n",p[0],p[1]);
    int pid=fork();
    if (pid==-1){
        perror("Fork nai hua");
        exit(EXIT_FAILURE);
    }
    // CHild Process
    else if (pid==0){
        close(p[0]);
        // Close Reading end
        int random=rand();
        write(p[1],&random,MSGSIZE);
        close(p[1]);
        exit(EXIT_SUCCESS);

    }
    // Parent Process ma read karyu
    int reader;
    read(p[0],reader,MSGSIZE);
    printf("PIN %d Fork %d\n",random,pid);
    wait(NULL);
    close(p[0]);
    close(p[1]);
    return 0;

}