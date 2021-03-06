/* A program to experiment with an unnamed pipe */
#include <stdio.h>
#include <unistd.h>

main ()
{
int fd[2];  /*  Array of two descriptors for an unnamed  pipe */
int pid;     /*  Variable for a process identifier */

/*  A pipe should be created before any fork() */
/* Do you understand why? */

if (pipe(fd) < 0)
      {perror ("PIPE CREATION ERROR");
       exit (1);
      }

pid = fork ();  /*  Parent:  creating the first child process */
if (pid == 0)   /*  The first  child process starts here */
      {
      dup2 (fd[0],0);  /* Standard input will be taken from the  downstream of the pipe  */
      close (fd[1]);     /*  Upstream end of the pipe is closed for this process (not used) */
      execlp ("sort", "sort", 0);  /* Running  “sort” command  taking input from the pipe */
      } 

else   /* Here the parent process continues */
pid = fork ();  /*  Parent:  creating the second child process */
if (pid == 0)   /*  The second child process starts  here */
      {dup2 (fd[1],1); /* Standard output  will be put  to the upstream end of the pipe */
       close (fd[0]);    /* Downstream end is closed  for this process (not used) */
       execlp ("who", "who", 0); /*  Running the command “who” which outputs to the pipe */
      }

else /* Parent process  closes for itself both ends of the pipe and waits for  children to terminate  */
      {
      close (fd[0]);
      close (fd[1]);
      wait (0);
      wait (0);
      }
}
