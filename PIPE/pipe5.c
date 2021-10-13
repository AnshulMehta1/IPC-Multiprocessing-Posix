/*
Read from a file and write it to a pipe in parennt process and then read  it in the child process
*/
// Write into some varibale and then they can write into files and no need o directly communicate 

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
    pid_t pid;
    int p[2]; // Pipe File Descriptor
    char input_str[100];
    pipe(p);
    pid=fork();
    if (pid==0){
        printf("Inside Child Process");
        // Here we will read from the pipe
        close(p[1]);
        // Read and echo it out 
         FILE *stream;
         int c;
        stream = fdopen ("new.txt", "r");
        while ((c = fgetc (stream)) != EOF)
            putchar (c);
        fclose (stream);
        // CLose Reading end 
        close (p[0]);
        exit(EXIT_SUCCESS);

    }
    else{
        printf("Inside Parent Process");
        // CLose Reading End
        close(p[0]);
        // Write to Pipe 
        FILE *stream;
        stream = fdopen ("new.txt", "w");
        fprintf (stream, "Jai Shree RAM!\n");
        fclose (stream);

        // Wait for the CHild Process to terminate
        wait(NULL);
        return EXIT_SUCCESS;
    }
    return 0;
}