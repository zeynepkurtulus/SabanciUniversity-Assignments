#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <pthread.h>
#include <cstdio>
#include <vector>
using namespace std;


/*
 COMMAND FORMAT:
 
 command_name input option redirection_symbol file_name bacgroundjob_symbol
 
 grep danger < input1.txt &
 grep = command_name
 danger = input
 option = -
 redirection_symbol = <
 file_name = input.txt
 backgroundjob_symbol = & 
 
 
 */



struct CodeLines{
    string input;
    string command;
    size_t len;
    string option;
    bool isbackjob;
    string rdsymbol;
    string newfilename;

    CodeLines(): isbackjob(false), rdsymbol("-"), len(0), command(""), newfilename(""), input(""), option("")
    {}
    };
vector <pid_t> backgroundvec; // to keep track of the number of background jobs
vector <pthread_t> threadvec; // to keep track of the treads and join them afterwards
vector<CodeLines> codevec; // to access each command

void parser(CodeLines &Code, string line, string wordholder, bool getCommand, bool isFilenameNext){
    
    stringstream iss1(line); // take it word by word
    //iss1(line);
    getCommand = true;
    while(iss1 >> wordholder){
        if(getCommand){ // we know thta the fist word is the command itself
            getCommand = false; //make it false after extracting the command so that we will not get into this if statement again
            Code.len++; // ad uo to the length of the command
            Code.command = wordholder; // store the command
        }
        else if(isFilenameNext){ // we know that the 2nd
            Code.len++;
            Code.newfilename = wordholder;
            isFilenameNext = false;
            
        }
        else if(wordholder.at(0) == '<' || wordholder.at(0) == '>'){ // indicates we have reached at the symbol before filename
            isFilenameNext = true; // we know the word right after < or > is the filename so make isNextCommand true so that we can enter the if statement to store the filename
            Code.len++; // increase the lenght of the command
            Code.rdsymbol = wordholder;// store the redirection symbol
            
        }
        else if(wordholder.at(0) == '-'){ // starting point of the opiton for the command
            Code.len++;
            Code.option = wordholder; // store the option command
            
            
        }
        
        else if(wordholder.at(0) == '&'){ // means we are at the background job
            Code.isbackjob = true;
            
        }
        else{
            Code.input = wordholder;
        }
    }
}


void promt(const CodeLines Code, ofstream &output){

    string divider = "----------";
    output << divider << endl;
    output << "Command: " << Code.command << endl;
    output << "Inputs: " << Code.input << endl;
    output << "Options: " << Code.option << endl;
    output << "Redirections: " << Code.rdsymbol << endl;
    if (!Code.isbackjob) {
        output << "Background: " << "n" << endl;
       
    } else{
        output << "Background: " << "y" << endl;
    }
    output << divider << endl;
    
    
}


pthread_mutex_t MUTEX = PTHREAD_MUTEX_INITIALIZER;

void *threadListener(void *args){
    pthread_mutex_lock(&MUTEX); // lock the mutex for concurrency control
    int buflen = 1024;
    string divider = "---- ";
    int fd = *((int *) args);
    cout << divider << pthread_self() << endl;
    FILE * readStream =  fdopen(fd, "r");
    char buffer[buflen];
    size_t nread;
    while ((nread = fread(buffer, 1, sizeof(buffer) - 1, reinterpret_cast<FILE *>(readStream))) > 0) {
            // Ensure null-termination of buffer
            buffer[nread] = '\0';
            printf("%s", buffer); // print the read data to the console
            fflush(stdout);
        //cout << "I am a thread with the id: " << pthread_self() << endl;
        }
    fclose(readStream);
    cout << divider << pthread_self() << endl;
    pthread_mutex_unlock(&MUTEX); // release the lock so that other threads can have it
    return NULL;
}




int main(){
    ifstream input("commands.txt");
    string line;
    int backjobs = 0;
    bool getCommand = true; // will be used the grap the command i.e the beginning of the sentence
    bool isNextCommand = false; // will be used to check if we are in the next line i.e next command
    ofstream output;
    output.open("parse.txt");
    if (!output.is_open()) {
        perror("File");
        exit(1);
    }
    string wordholder = "";
    
    /* PARSER STARTS */
    while(getline(input,line)){
        CodeLines Code;
        parser(Code, line, wordholder, getCommand, isNextCommand);
        promt(Code, output);
        codevec.push_back(Code); // to keep track of each struct so that they wont be lost
    }
    /* PARSER ENDS */
    
    
    int size = codevec.size();
    for(int j = 0; j < codevec.size(); j++){
        CodeLines codeholder = codevec[j]; // take each parsed command
        // if the comamnd is wait the shell must wait all child processes to terminate
        if (codeholder.command == "wait") { // we do not generate any child processes
            int backgroundProcessNum = backgroundvec.size(); // gives the number of background processes
            for(size_t j = 0; j < backgroundProcessNum ; j++){
                int status;
                waitpid(backgroundvec[j], &status, 0); // shell will wait for them to terminate
            }
            
            // wait for threads to join
            int numofthread = threadvec.size();
            for (size_t j = 0; j < numofthread ; j++ )
            {
                pthread_join(threadvec[j], NULL);
            }
            
            int status;
            while (waitpid(-1, &status, WNOHANG) > 0) {
                // continue waiting for child processes to complete
            }
            backgroundProcessNum = 0;
            continue;
        
        }
        
        // If the command contains an output redirectioning part shell process forks a new process that manipulates standard stream file handlers
        if (codeholder.rdsymbol == ">") { // output should be redirected to a file
            // shell process must fork a new process
            int rc = fork();
            if (rc < 0) {
                perror("Fork");
                exit(1);
            }
            else if (rc == 0){ // we are at the child process
                //cout << "Hello I am the child process! Here is mu pid: " << rc << endl;
                int idx = 0;
                char *args[codeholder.len+1]; // use this array to store the arguments for the command that is being executed.
                args[idx++] = strdup(codeholder.input.c_str());
                
                if (!codeholder.option.empty()) {
                    args[idx++] = strdup(codeholder.option.c_str()); // store the option inside the command
                }
                if (!codeholder.input.empty()) {
                    args[idx++] = strdup(codeholder.input.c_str()); // store the input inside the array
                }
                
                FILE *newdesc = fopen(codeholder.newfilename.c_str(), "w"); // open the file with the given name in the write mode ("w")
                int filedescriptor = fileno(newdesc);
                dup2(filedescriptor, STDOUT_FILENO);
                args[idx] = NULL; //execvp command requires the array to be terminated with a null pointer
                execvp(args[0], args);
                
            }
            else{ // if not child process
                //cout << "Hello I am the parent process! Here is mu pid: " << rc << endl;
                if (codeholder.isbackjob) { //check if it is a background process
                    backgroundvec.push_back(rc);
                    backjobs++;
                    continue;
                    
                }
                int status;
                waitpid(rc, &status, 0);
                
            }
            
        }
        else // we dont have any file redirection part then we should use pipe to enable communication
        {
            int * fd = (int*)malloc(8); // will be used for file descriptors
            pipe(fd);
            int rc2 = fork();
            pthread_t threadId;
            if (rc2 < 0) {
                perror("Fork");
                exit(1);
            }
            else if (rc2 == 0)
            { // child process will execute the command
                //cout << "Hello I am the child process! Here is mu pid: " << rc2 << endl;
                // close the read end
                
                close(fd[0]);
                FILE * pipefile = fdopen(fd[1], "w"); // opened a file to perform write operations
                int fdescriptor = fileno(pipefile);
                dup2(fdescriptor, STDOUT_FILENO);
                
                int idx2 = 0;
                char *args2[codeholder.len+1];
                args2[idx2++] = strdup(codeholder.command.c_str());
                if (!codeholder.option.empty()) {
                    args2[idx2++] = strdup(codeholder.option.c_str());
                }
                if (!codeholder.input.empty()) {
                    args2[idx2++] = strdup(codeholder.input.c_str());
                }
                if (codeholder.rdsymbol == "<") {
                    string fn = codeholder.newfilename.c_str();
                    FILE * openfile = fopen(codeholder.newfilename.c_str(), "r");
                    int desc = fileno(openfile);
                    dup2(desc, STDIN_FILENO);
                }
                
                
                args2[idx2] = NULL;
                execvp(args2[0], args2);
                
            }
            else{
                //cout << "Hello I am the parent process! Here is mu pid: " << rc2 << endl;
                close(fd[1]); // close write end
                pthread_create(&threadId, NULL, threadListener, (void*)&fd[0]);
                if (codeholder.isbackjob) {
                    backgroundvec.push_back(rc2);
                    backjobs++;
                    continue;
                }
                else{
                    
                    int stat;
                    waitpid(rc2, &stat, 0);
                    pthread_join(threadId, NULL);
                }
                
                
            }
            
            
        }
        
    }
    int count = 0;
    while (count < backjobs) {
        int s;
        waitpid(-1, &s, 0);
        count++;
    }
    int s;
    int waitnum = waitpid(-1, &s, WNOHANG);
    bool check = true;
    if (waitnum < 0) {
        check = false;
    }
    while (check) {
        if (waitnum < 0) {
            check = false;
        }
        int s;
        wait(NULL);
        
    }
    
    for (int i = 0; i < threadvec.size(); i++) {
        pthread_join(threadvec[i], NULL);
    }
    
    
    return 0;
}

