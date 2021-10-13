/*
Demonstrating two commands and their IPC
Eg: Who | Sort

One of these child processes should execute some shell command (for example, “who”)and  write  the  results  of  this  command  into  the upstreamend of the pipe.Another child process should execute some other shell command (fexample, “sort”)taking its input from the downstreamend of the same pipe
We will do communication between them using an unnamed pipe
*/


// Same as pipe 7
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>
int main(){

    int p[2];
    pid_t pid;
    // PIpe before fork
    pipe(p);
    pid=fork();
    if (pid<0){
        perror("Fork nai hoa");
        exit(EXIT_FAILURE);

    }
    else if (pid==0){
        printf("INside CHild Process");
        // Here we will execute who and data male e we will write to Pipe 
    
        dup2 (p[0],0); // Duplicates the file descriptor
        close (p[1]);
        execlp("sort","sort",NULL);
        //  Running sort command after taking the input from pipe
        return EXIT_SUCCESS;
    }
    // Now back in Parent Process
    pid=fork();

    // Creating another child process
     if (pid<0){
        perror("Fork nai hoa");
        exit(EXIT_FAILURE);

    }
    else if (pid==0){
        printf("INside CHild Process");
        // Here we will execute who and data male e we will write to Pipe  & tandard output  will be put  to the upstream end of the pipe
         // Reading side closed
        dup2 (p[1],1); // Duplicates the file descriptor
        close (p[0]);
        execlp ("who", "who", NULL);
        //  Running who command after taking the input from pipe
        return EXIT_SUCCESS;
    }
    // Back in Parent Process
    close(p[1]);
    close(p[0]);
    wait(0);
    wait(0);

// So multiple child processes can be called  in this way



    return 0;
}
