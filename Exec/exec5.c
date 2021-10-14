// Execl command to call the sum in execl
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    pid_t pid;
    pid = fork();
    if (pid<0){
        perror("Fork c");
        exit(EXIT_FAILURE);
    }
    else if (pid==0){
        
        // Relative or Absolute koi pan chalse 
        // l che etle null aapyu ne 5 ne 6 are args for sum waala programs
        if (execl("./product","product","5","6","8","9 ", NULL) <0 ){ 
            
            perror("Child failed to execute");
            return 1;
        }
        // char *const parmList[] = {"/bin/ls", "-l", "/", NULL}; when p used execvp
        printf("Return not expected. Must be an execv error.n");
    }


    return 0;
}