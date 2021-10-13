/* 
Pipe - | 
IPC maate
Output from one becomes input for another
Pipe is a one way Communication - i.e. One side reads and one side writes and direction is that only
It opens a pipe, which is an area of main memory that is treated as a “virtual file”.
The pipe can be used by the creating process, as well as all its child processes, for reading and writing. One process can write to this “virtual file” or pipe and another related process can read from it.
The pipe system call finds the first two available positions in the process’s open file table and allocates them for the read and write ends of the pipe
Etle 2 free jagya gote free tables ma ane allocate to an end of the pipe
fd [0] --> read end of the pipe
fd[1] --> write end of the pipe
int pipe (int fds[2])
// Array of size 2
PIpes are FIFO and behave like a QUEUE
Write --> 512 bytes at a time
Read --> Only One byte at a time 
*/
// Pipe Demo 1
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>
#define MSGSIZE 16
char* msg1 = "Jai";
char* msg2 = "Shree";
char* msg3 = "RAM";
int main(){
    char buffer[MSGSIZE];
    int p[2];
    int i;
    // Error handling block ke array ma kai - ma jaay to 
    if (pipe(p)<0){
        exit(1);
    }
    // p[1] is for writing and write msg of MSGSIZE in Pipe p
    write(p[1], msg1, MSGSIZE);
    write(p[1], msg2, MSGSIZE);
    write(p[1], msg3, MSGSIZE);
    for (i = 0; i < 3; i++) {
        // Here Read from buffer using p[0] end of the pipe 
        read(p[0], buffer, MSGSIZE);
        printf("% s\n", buffer);
    }
    return 0;
}
