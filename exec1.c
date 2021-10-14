/*
Theory
Exec system call is basically calling another process in the current process
It has same pid and resources
Etle ek running process ma biji running process bolavaani
The exec family of functions replaces the current running process with a new process. It can be used to run a C program by using another C program
There are many in the exec family 
Typically,the exec system call is used after a fork system call by one of the two processes to replace the process’ memory space with a new executable program. 
The new process image is constructed from an ordinary, executable file
There can be no return from a successful exec because the calling process image is overlaid by the new process image
Image process j repalce thai jaay che
Commonly a process generates a child process because it would like to transform the child process by changing the program code the child process is executing
The text, data and stack segment of the process are replaced and only the u(user) area of the process remains the same

#include <unistd.h>extern char **environ;
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
Therefore p means path

int execve(const char *path, char *const argv[], char *const envp[]);
 Therefore e means environement variables

 SImilarey l je che e stands for 
  ellipses : describe a list of one or more pointers to null-terminated strings that represent the argument list available to the executed program.
  l – Command-line arguments are passed individually (a list) to the function.


  So l - Points to ellipses and list of Strings
    p - Path
    e - ENvironment variables, changes the environemt 
    v- Command-line arguments are passed to the function as an array (vector) of pointers

path

The argument specifies the path name of the file to execute as the new process image. Arguments beginning at arg0 are pointers to arguments to be passed to the new process image. The argv value is an array of pointers to arguments.

arg0

The first argument arg0 should be the name of the executable file. Usually it is the same value as the path argument. Some programs may incorrectly rely on this argument providing the location of the executable, but there is no guarantee of this nor is it standardized across platforms.

envp

Argument envp is an array of pointers to environment settings. The exec calls named ending with an e alter the environment for the new process image by passing a list of environment settings through the envp argument. This argument is an array of character pointers; each element (except for the final element) points to a null-terminated string defining an environment variable.

Each null-terminated string has the form:

FUnctionalityies

execl 
This system call is used when the number of arguments to be passed to the program to be executed is known in advance

execv
This system call is used when the numbers of arguments for the program to be executed is dynamic.

aa be j main che e ne p to optional types che 

exec waala codes ma arc ne argv hovi joiye
e pipes saathe pan call thai sake tyaare exec emnem chaale 

Whereargcis the argument countand argvis an array of character pointers to the arguments themselves. In addition, the following variable

1St argument 
FILE/PATH
FIle - FIle contains the executable Image ni Process
Path -t identifies the location of the new process image within the hierarchical file syste

2Nd Argument 
Argument List/argv
argv -->  t is a pointer to an array of pointers to null-terminated character strings. A NULLpointer is used to mark the end of the array. Each character string pointed to by the array is used to pass an argument to the new process image.The first argument, argv[0],is required and must contain the name of the executable file for the new process image

arg0,arg1,arg2....NULL
NULLIt is a variable length list of arguments that are passed to the new process image. Each argument is specified as a null-terminated string, and the list must end with a NULLpointer.
The first argument, arg0, is required and must contain the name of the executable file for the new process image.
If the new process image is a normal C mainprogram, the list of arguments will be passed to argv as a pointer to an array
of strings. 
The number of strings in the array is passed to the main()function as argc

3rd Argument is envp
 is a pointer to an array of pointers to null-terminated character strings. A NULLpointer is used to mark the end of the array. Each character string pointed to by the array is used to pass an environment variableto the new process image.


 MIQ
 This system call simply replaces the current process with a new program --the pid does not change
 he exec () is issued by the calling process and what is expected is referred to as the new program --not the new process since no new process is created 
 t is important to realize that control is not passed back to the calling process unless an error occurred with the exec () call

 In the case of an error, the exec () returns a value back to the calling process 
 If no error occurs, the calling process is lost 
*/
// SImple ls using exec
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
    char *const parmList[] = {"/bin/ls", "-l", NULL};
    // Null Terminated String {/bin/ls,-l,NULL}
    pid=fork();
    if (pid<0){
        perror("Fork c");
        exit(EXIT_FAILURE);
    }
    else if (pid==0){
        printf("In Child Process");
        execv("/bin/ls", parmList);
        // char *const parmList[] = {"/bin/ls", "-l", "/", NULL}; when p used execvp
        printf("Return not expected. Must be an execv error.n");
    }
    return 0;
}
/* Here ls will take over from exec1 */


