/* Pipe and Fork to concatenate strings
Here we will be using multiple Pipes
Write Linux C program to create two processes P1 and P2. 
P1 takes a string and passes it to P2. P2 concatenates the received string with another string without using string function and sends it back to P1 for printin
p1 --> P2 ,  P2 --> Received String + Original String , P2-->P1, P1--> Prints
 // o create child process we use fork(). fork() returns :
   <0 fail to create child (new) process
   =0 for child process
 //  >0 i.e process ID of the child process to the parent process. When >0 parent process will execute.


 Pipes are unidirectional
 AHiya two way communication che
 SO we will use 2 different pipes
 // Parent ma
 Close reading end of 1st pipe
 Write string through the writing end of the pipe [1st piepe]
 Now wait for child process where it will concatenate and then send backk
 After receiving from pipe 2 by reading parent will print int out
*/
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
    int p1[2];
    int p2[2];
    // FIle Descriptors for both the pipes
    char fixed_str[] =" JAI";
    char input_str[100];
    pid_t pid;
    // Initializing Pipes
    pipe(p1);
    pipe(p2);
    /*
    Alternatively we can have a error control block
    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    */
    scanf("%s", input_str);
    // Take Input
    pid=fork();
    if (pid==-1){
        perror("Fork nai hoa");
        exit(EXIT_FAILURE);
    }
    // Child Process
    else if (pid==0){
         // Declaring the concatenated String
        char concat_str[100];
        // AHiya pela pipe 1 maathi read thase
        // p1[0]
        // Concatenate thase
        // p2 [1] thi write thase
        // Close writing end of the 1st pipe and read from the 1st pipe
        close(p1[1]);
        read(p1[0],concat_str,100);
        // Concat Logic 
        int k = strlen(concat_str);
        int i;
        for (i=0; i<strlen(fixed_str); i++)
            concat_str[k++] = fixed_str[i];
  
        concat_str[k] = '\0';   // string ends with '\0'
  



        // Again IPC Block
        close(p1[0]);
        close(p2[0]);
        write(p2[1],concat_str,strlen(concat_str)+1);
        close(p2[1]);
        exit(0);


    }
    // Parent Process
    // Pela Take the Input String
    // Write to pipe 1 the I/P String and send it to CHild Process
    // Read from pipe 2

    // Declaring the concatenated String
    char concat_str[100];
    // CLosing Reading end of pipe 1
    close(p1[0]); 
    write(p1[1],input_str,(int)sizeof(input_str));
    // Closing writing end
    close(p1[1]);
     // Wait for child to send a string
    wait(NULL);
    // After the child process is done executing
    close(p2[1]); // Pipe 2 ma writing end bandh
    read(p2[0],concat_str,100);
    printf("Concatenated string %s\n", concat_str);
    close(p2[0]);
    return 0;
}