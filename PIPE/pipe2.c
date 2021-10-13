/* There can be a case where fd[0] and fd[1] both ends are shared by the parent and child processes
When we use fork in any process, file descriptors remain open across child process and also parent process.
If we call fork after creating a pipe, then the parent and child can communicate via the pipe.
// Etle pela pipe create kari pachi fork  karvanu


 */

// Continous reading 
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
    int pid;
    int nbytes;
    pipe(p);
    printf("%d %d\n",p[0],p[1]);
    // Now Forking 
    if ((pid=fork())>0){
        write(p[1], msg1, MSGSIZE);
        write(p[1], msg2, MSGSIZE);
        write(p[1], msg3, MSGSIZE);
        // Writing in the parent process
        close(p[1]);
        wait(NULL);
    }
    else{
        // In child Process
        close(p[1]);
        // Here Read from the buffer 
        while ((nbytes = read(p[0], buffer, MSGSIZE)) > 0)
            printf("% s\n", buffer);
        if (nbytes != 0)
            exit(2);
        printf("Finished reading\n");
    }









    return 0;
}