/*
Author : Anshul Mehta Enrolment Number:AU1940275
Write a parallel version of the wc command using C language. The file is processed simultaneously
 by each child process. Each child process should return the data via a pipe and theparent should process the total.

Input : Path and Number of Child Processes to spawn
Char Count, Word Count and Line Count
*/

// Header Files
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include<time.h>
#define SIZE 20
/*
Function to find the size of the file
Ref:https://www.geeksforgeeks.org/c-program-find-size-file/
*/
int findSize(const char *file_name){
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");
  
    // checking if the file exists
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calculating the size of the file
    int res = ftell(fp);
  
    // close file
    fclose(fp);
  
    return res;
}
void wcparallel(const char *fileName, int child){
    /*
    Has two args passed --> File Name and Number of Child Processes

    */
    // Iterators
    int i=0;
    int j=0;
    int k=0;

    // Buffer Stream for all R/W Ops
    char buf[26214]; 
    // int status;

    // Initializing PIPE fds
    int p_c[2];
    int p_l[2];
    int p_w[2];

    // Declaring pipes
    pipe(p_w);
    pipe(p_c);
    pipe(p_l);

    /* Error Handling for Pipes*/
    if (pipe(p_w)<0){
         perror("Pipe failed");
     }
     if (pipe(p_l)<0){
         perror("Pipe failed");
     }
     if (pipe(p_c)<0){
         perror("Pipe failed");
     }


    // For reading
    long int nbytes;

    // Opening the FIle
    int fd1 = open(fileName, O_RDONLY);
    /* Error Handling Block */
    if (fd1 == -1){
        return;
    }
    // Multiple Processes forked so multiple pids required
    pid_t pid[child];
    // pid_t pid;

    // Find size of the file to divide among child Processes
     // Explicitly call 
    //int size=findSize(fileName); // Throws Floating Point error
   
    FILE *fp = fopen(fileName, "r");
    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);

    /* Interval size for each process */
    int interval=size/child;
    // Approach 2--> fseek thi alag alag pointers
    // Fork Loop
    for (i=0;i<child;i++){
        // Forks different processes with pids in
        pid[i]=fork();
        
        // Error Handling Block
        if (pid[i]<0){
             perror("Fork Failed");
         }
        if (pid[i]==0){
            printf("Inside Child Process");
            // For assigning task to the Child Process
    
            int start=i*interval;
            int end=(i+1)*interval;
            if (i==child-1){
                end=size;
            }
            // Once we have the interval size we need to take two cases where pre-declared buffer may be bigger  or smaller than interval size.
    
            // For this interval one Process will run and for subsequent Intervals other Processes will run
            interval=end-start;
            if (interval);
            // Two cases for the interval being bigger or smaller than the buffer size
            
            if(interval>26214){
                int l,w,c;
                
                close(p_w[0]);
                close(p_l[0]);
                close(p_c[0]);
                // Read from the pipes to see if there are  values
                read(p_w[0],&w,sizeof(int));
                read(p_l[0],&l,sizeof(int));
                read(p_c[0],&c,sizeof(int));
          
                int lineC=l;
                int charC=c;
                int wordC=w;
                
                while(start<end){
                    // Read from file
                    nbytes = read(fd1, buf, sizeof(buf));
                    for (int j=0; j<nbytes; j++){
                        // new line prompt increase the Line Count
                        if (buf[j] == '\n'){ 
                            lineC++;
                            wordC++;    
                        
                        }
                        // If a blank space delimeter or tab esc seq then increase wc
                        else if( buf[j]==' '||buf[j]=='\t'){ 
                            wordC++;
                        }
                        
                        charC++;
                        
              
                    }
                    // The start needs to be incremented with the size of the buffer
                    start+=26214;
                }
                // Once we are done with the Counting, Do IPC
                // Closing the reading side

                 close(p_w[0]);
                 close(p_c[0]);
                 close(p_l[0]);

                // Every Process Writes to the respective Pipe
                write(p_w[1],&wordC,sizeof(int));
                write(p_l[1],&lineC,sizeof(int));
                write(p_c[1],&charC,sizeof(int));

                // Closing the Writing end as well
                close(p_w[1]);
                close(p_c[1]);
                close(p_l[1]);

               
                exit(EXIT_SUCCESS);

            }
            else{
                // If the interval is bigger than declare a buf of size interval
                char buf[interval];
                int l,w,c;
                // Read from the pipes to see if there are  values
                read(p_w[0],&w,sizeof(int));
                read(p_l[0],&l,sizeof(int));
                read(p_c[0],&c,sizeof(int));
                
                int lineC=l;
                int charC=c;
                int wordC=w;
                
                nbytes = read(fd1, buf, sizeof(buf));
                for (int j=0; j<nbytes; j++){
                        // new line prompt increase the Line Count
                        if (buf[j] == '\n'){ 
                            lineC++;
                            wordC++;    
                        
                        }
                        // If a blank space delimeter or tab esc seq then increase wc
                        else if( buf[j]==' '||buf[j]=='\t'){ 
                            wordC++;
                        }
                     
                        charC++;
                       
                }
                // Once we are done with the Counting Do IPC
                // Closing the reading side

                 close(p_w[0]);
                 close(p_c[0]);
                 close(p_l[0]);

                // Every Process Writes to the respective Pipe
                write(p_w[1],&wordC,sizeof(int));
                write(p_l[1],&lineC,sizeof(int));
                write(p_c[1],&charC,sizeof(int));
                // Close the writing end as well
                close(p_w[1]);
                close(p_c[1]);
                close(p_l[1]);

               
                exit(EXIT_SUCCESS);

            /*
                Here in IPC Processes will keep writing values at adjacent places and we will sum then up in calculations in parent process
            */
            }


        }

    }
        // Out of Child Process 
        //Inside Parent Process
        // Wait for the Child Processes
        for (int n = 0; n < child; n++){
            wait(NULL);
        }
        // Variables for reading from Pipe
        int wordCount=0;
        int lineCount=0;
        int charCount=0;
        // Output var
        int totw=0;
        int totc=0;
        int totl=0;
        // Closing the writing end
        close(p_w[1]);
        close(p_c[1]);
        close(p_l[1]);
        // Calculating the total by IPC
        // Calculating for all the child processes and since pipes are FIFO they will provide a sum from 1st to mth child process.
        for (int m=0;m<child;m++){
            read(p_w[0],&wordCount,sizeof(int));
            read(p_l[0],&lineCount,sizeof(int));
            read(p_c[0],&charCount,sizeof(int));
            // Update the total after each iteration
            totc=totc+charCount;
            totw+=wordCount;
            totl+=lineCount;

        }
        // Adding them all from the Processes
        /* Printing them all */
        printf("Words %d\n", totw);
        printf("Lines %d\n", totl);
        printf("Characters %d\n",totc);

        // Closing the Reading Pointers as well
        close(p_w[0]);
        close(p_c[0]);
        close(p_l[0]);


}

/* Main Method */
int main(int argc, char *argv[]){
    /*
        3 Arguments ./wc filename numchild
    */

   // Error Handling Block
   if (argc!=3){
       perror("Enter Valid Argument");
   }
   // If args are in correct format
   else{
       // string converted to int format
       int child=atoi(argv[2]);
       // Calling the Function
       wcparallel(argv[1],child);

   }
}



/* EOF */

