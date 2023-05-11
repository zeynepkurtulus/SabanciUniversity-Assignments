// Zeynep Kurtulus CS307 - PA1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>



int main(){

    
    int fd[2]; // array of size 2
    printf("I'm SHELL process with PID:%d - My Command is: man grep | grep -A7 -e-w -m1\n", (int) getpid());
    // check if pipe has failed or not
    if(pipe(fd) < 0){
        printf("Pipe Error exiting program...");
        exit(1); // if pipe fails exit thr program
    }

    // at this point we are sure that pipe has not failed: pipe has created a descripter pari with a read and write and
    int rc1_id = fork(); // after pipe if we fork we can now use 2 processes with the pipe and the child process can also use the dup2 command to use its own pipe
    // check if fork has failed
    if(rc1_id < 0){
        printf("Fork Error exiting program...");
        exit(1);
    }

    else if(rc1_id == 0){ // this is child1 i.e. man command
        printf("I'm MAN process, with PID: %d - My command is: man grep\n", (int) getpid());
        //dup2 comment creates a copy on the file descripted specified: fd[1] is write end and fd[0] is read end
        close(fd[0]); // closing the read end since we will not use the read end of the pipe here man command will write the manual page of the command
        if(dup2(fd[1], STDOUT_FILENO)< 0){// dup2 duplicates the file descriptor fd[1] (write end of a pipe) onto the standard output file descriptor (STDOUT_FILENO).
        //This means that any data written to STDOUT_FILENO will be sent to the write end of the pipe instead of the console.
            printf("dup2 error exiting the program...");
            exit(1);
        }
        // write end is now copied to the man process
        close(fd[1]);
        char* arr[] = {"man","grep", NULL}; // an array of strings we will use to execute the ping command, it will pass arguments to the execvp
        //char * arr[] = {command_name, argument_name, NULL}
        execvp(arr[0], arr); // arr[0] is the command and arr is the arguments list
       

    }
    // the parent process i.e sehll must wait for the child process i.e. man to finish
    waitpid(rc1_id, NULL, 0);
    int rc2_id = fork(); // child2 for the grep command
    if(rc2_id < 0){
        printf("Fork Error exiting program...");
        exit(1);
    }

    else if(rc2_id == 0){
        // now we are in the child process which is the grep command
        printf("I’m GREP process, with PID: %d - My command is: grep -A7 -e-w -m1 > output.txt\n", (int) getpid());
        close(fd[1]); // closing the write end bc. grep will only read from the manual page
        if(dup2(fd[0], STDIN_FILENO) <0){ //STDIN_FILENO write operation read end is now copied to the grep process
            printf("dup2 error exiting the program...");
            exit(1);
        }
        close(fd[0]);
        char *arr2[] = {"grep", "-A7",  "-e-w", "-m1", NULL};
        int file = open("output.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR); // generated a file to write the results coming from the grep commmand.
        if(dup2(file, STDOUT_FILENO) <0 ){ // write to the output.txt file
            printf("dup2 error exiting the program...");
            exit(1);
        }
        close(fd[1]); // close the writing end
        execvp(arr2[0], arr2);
        
    }
    // shell must wait for the grep to finish
    waitpid(rc2_id, NULL, 0);
    //now the parent process can finish its execution
    printf("I’m SHELL process, with PID: %d - execution is completed, you can find the results in output.txt\n", (int) getpid());


    return 0;
    
}
