/* 
 Odd and Even series  generation  for n terms using Parent Child relationship (say odd is the duty of the parent and even series as that of child) 
*/
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
    int i; //iterator
   int n; //range
   int status;
   printf("Enter n\n");
   scanf("%d",&n);
   pid=fork();
    if (pid<0){
        perror("Fork c");
        exit(EXIT_FAILURE);
    }
    else if (pid==0){
        for(i=1;i<=n;i++)
        if(i%2 == 0)
          printf("even %d\n",i);

    }
    // Parent Process
    else{
        if (pid>0)
        {
             wait(NULL);
            for(i=1;i<n;i++)
                if(i%2 != 0)
                printf("odd %d\n",i);
        }
        
        
    }
   


    return 0;
}