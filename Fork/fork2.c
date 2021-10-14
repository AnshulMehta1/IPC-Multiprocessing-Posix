/*
3) Armstrong number generation within a range. The digit extraction, cubing can be responsibility of child while the checking for sum == no can happen in child and the output list in the child
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
    printf("Enter range\n");
    scanf("%d",&n);
    // Taking Input
     int status;

 for(int i=1;i<=n;i++)
  {
  
  pid = vfork();
  int sum=0;int k=i;
  if (pid == 0)
    {
        // Digit Extraction
        while(k!=0)
        {
          int t= k%10;
          sum+=t*t*t;
          k=k/10;
        }
       pid=1;
    }
    // Parent ma 
      if (pid > 0)
      { pid = waitpid(pid, &status, 0);
        if(sum==i)
        printf("Armstrong number = %d\n",i);
      }
    
  }
    exit(0); 
    return 0;

}