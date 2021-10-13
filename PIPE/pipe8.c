/* 
Write a program of creation of a two-waypipe between twoprocess (Child process sends a question to Parent process “where is GEC?” through one pipe, parentprocess reads this questions and send a reply “in gudlavalleru” through second pipewhich thechild process reads.)
*/
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>
#define BUFSIZE 100
int main(){
    char buffer[BUFSIZE];
    pid_t pid;
    int p1[2];
    int p2[2];
    // Initializing the file descriptor for pipe
    pipe(p1);
    pipe(p2);
    // if (pipe(p1)<0){
    //     perror("Pipe na bani");
    // }
    pid=fork();
    if(pid<0){
        perror("Fork c");
        exit(EXIT_FAILURE);

    }
    else if (pid==0){
        printf("Inside the Child");
        char Question[] =" JAI? ";
        close(p1[0]);
        // CLose for reading
        write(p1[1],buffer,100);
        close(p1[1]);
        return EXIT_SUCCESS;
    }
    // Parent Process ma answer
    char answer[] =" Shree RAM ";
    close(p2[1]);
    // Close Writing 
    read(p1[0],buffer,100);
    printf("The Question:%s\n",buffer);
    write(p2[1],buffer,100);
    read(p2[0],buffer,100);
    printf("Answer %s\n",buffer);
    wait(NULL);
    return 0;
}
/*

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
int main() {
    int p2c[2], c2p[2];
    char msg1[] = "Wherer is GEC?\n", msg2[] = "in gudlavalleru\n";
    char buffer[120];
    pipe(p2c);
    pipe(c2p);
    int proId , data;
    if((proId = fork())== -1){
        printf("Error Creating child process!!");
    }
    if(proId == 0){
        
        //child process 
        //send message from child to parent
        close(c2p[0]);
        write(c2p[1] , msg1 , strlen(msg1)+1);

        //recive message from parent
        close(p2c[1]);
        data = read(p2c[0] , buffer , sizeof(buffer));
        printf("%s",buffer);
    }
    if(proId !=0 ){
        
        //***parent process 
        //***send message from parent to child
        close(p2c[0]);
        write(p2c[1] , msg2 , strlen(msg2)+1);

        //recieve message from child
        close(c2p[1]);

        data = read(c2p[0] , buffer , sizeof(buffer));
        printf("%s", buffer);
    }

return 0;
}

*/