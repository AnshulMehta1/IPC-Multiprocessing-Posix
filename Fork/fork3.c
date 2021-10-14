#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>

/*
Remember:
1 . Any statement written before fork() will be printed twice(depends on number of fork()
2 . After fork() - inside main statement except written values block will be printed twice (Onefork)
3 . Fork () always creates child process
4 . fork() always returns three values
5 . < 0 if child process is not crated
6.  0 if child process is created
7.  > 0 to the parent process
--------------------------------------
*/ 

/*
Ascending Order sort within Parent and Descending order sort  (or vice versa) within the child process of an input array. (u can view as two different outputs –first entire array is asc order sorted in op and then the second part desc order output)
*/
int main(){
    int a[]={1,3,2};
    int aop[10];
    int dop[10];
    pid_t pid;
    int n=3;
    pid = fork ();
    if (pid<0){
        perror("Fork c ");
        exit(EXIT_FAILURE);
    }
    else if (pid==0){
        // Inside Child so sort in Descending 
       
        for (int i = 0; i < n; i++){                 //Loop for ascending ordering
            for (int j = 0; j < n; j++){             //Loop for comparing other values
            
            if (a[j] > a[i]){                      //Comparing other array elements
                int tmp = a[i];                     //Using temporary variable for storing last value
                a[i] = a[j];                        //replacing value
                a[j] = tmp;                         //storing last value
            }  
        }
    }
        for(int k = 0; k < n; k++)
             printf("%d ", a[k]);
        exit(EXIT_SUCCESS);


    } 
    else{
        // In Parent
        if (pid>0){
               for (int i = 0; i < n; i++){                 //Loop for ascending ordering
                    for (int j = 0; j < n; j++){             //Loop for comparing other values
                    
                        if (a[j] < a[i]){                      //Comparing other array elements
                            int tmp = a[i];                     //Using temporary variable for storing last value
                            a[i] = a[j];                        //replacing value
                            a[j] = tmp;                         //storing last value
                        }  
                }
            }
            wait(NULL);
            for(int k = 0; k < n; k++)
                 printf("%d ", a[k]);
           exit(0);
        }
    }
    return 0;

}