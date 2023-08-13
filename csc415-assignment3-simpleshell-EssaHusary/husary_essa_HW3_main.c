/**************************************************************
 * Class:  CSC-415-03 Spring 2023
 * Name: Essa Husary
 * Student ID: 917014896
 * GitHub ID: EssaHusary
 * Project: Assignment 3 – Simple Shell
 *
 * File: husary_essa_HW3_main.c
 *
 * Description: In this assignment/file, we are creating a simple 
 *              shell program that exists within our existing 
 *              shell. So a shell within a shell (and possibly, 
 *              our shell has other shells in it if we so choose). 
 *              The purpose of this assignment is to acclimate us 
 *              to processes - creating them, exiting from them, 
 *              returning from them, waiting for them to terminate 
 *              – and to acclimate us to the exec family of functions, 
 *              string tokenization in C, string buffering in C, and 
 *              input buffering in C.  
 *
 **************************************************************/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>




#define BUFFER_SIZE         102 
#define ARGUMENT_ARRAY_SIZE ((BUFFER_SIZE/2) + 1) 




int main(int argc, char *argv[]) {



    while (true) {
        

        // A buffer to store user input
        char buffer[BUFFER_SIZE];


        /* A variable used in a check to see if EOF is reached or if an
           error has occurred when fetching input */
        char *returnOfFgets;

        
        // To check if a prompt has been specified.
        if (argv[1] == NULL){

            printf("> ");
        
        } else {

            printf("%s ", argv[1]);
        }

        
        
        /* Following ~20 lines are written to fetch input from user and to 
           check if either EOF has been reached or if an error has occurred
           while fetching that input from the user */
        returnOfFgets = fgets(buffer, BUFFER_SIZE, stdin);
        if (returnOfFgets == NULL) {
            
            if (feof(stdin)){
                
                printf("\n");
                printf("EOF has been reached. Thanks for using my shell!\n");
                clearerr(stdin);
                break;
            
            } else if (ferror(stdin)){
                
                printf("An error has occured while reading input." "Exiting...\n");
                clearerr(stdin);
                exit(errno);
            
            }
            
            
        } 
        printf("\n");   // To add a bit of neatness to output

        
        

        /* Next 12 lines of code are written to use truncated version
           of user input and to clear the input buffer */
        if (strchr(buffer, '\n') == NULL){
            int c;
            while(true){

                c = getchar();
                if (c == '\n' || c == EOF){
                
                    break;
                }
            
            }
        }
        





        /* NOTE: The next ~20 lines of code where I call and use 
           strtok() were inspired by a snippet of code from "Finding
           Tokens in a String" from the GNU C Manual website, gnu.org.
           This web page is where I learned how to use strtok() 
           (in addition to the man pages). I've cited the source in the 
           writeup */


        // Array of pointers to gather command line args
        char *stringParts[ARGUMENT_ARRAY_SIZE];

        // To track the index in stringParts[] (the array from prev line)
        int index = 0;

        /* To get first string/arg of input to store in 
           stringParts[] */
        char *stringPart = strtok(buffer, " \n");

        // To store first arg in stringParts[]
        stringParts[index] = stringPart;

        /* To get the next strings/args of input and store them
           into stringParts[] */
        while (!(stringPart == NULL)) {

            stringPart = strtok(NULL, " \n\0");
            index++;
            stringParts[index] = stringPart;
        
        }

        



        // To check if user has entered in an empty line
        if(stringParts[0] == NULL){
            
            printf("No command entered. Please enter a command to continue.\n\n");
            continue;
        
        }


        // To check if the user would like to exit
        if (strcmp(stringParts[0], "exit") == 0){

            break;
        
        } 

        




        /* NOTE: The following lines of code, specifically, process
           creation, the checks, and waiting, were heavily 
           inspired by a snippet of code from page 119 of the e-textbook, 
           specifically in chapter 3, section 3.3.1 (the very first 
           snippet of code from that section), when the authors were
           covering process creation. I've cited the source in the 
           writeup */


        // Process ID to be used in a check when forking
        pid_t pid;

        // To create a new child process
        pid = fork();

        // To get the exit status of the child
        int exitStatus;
        

    
        if (pid < 0) {  // To check if fork has failed

            printf("Fork has failed!");
            return 1;
        
        }
        else if (pid == 0) {  // To check if we are in child process
        
                        
            execvp(stringParts[0], stringParts);

            // To return an error when user inputs an invalid program
            printf("\"%s\" not found. Please enter a valid value.\n", 
                    stringParts[0]);
            exit(errno);
            

        }
        else {  // To check if we are in parent process
            
            
            /* To wait for child process to terminate and then get 
               both its pid and exit status */
            pid = wait(&exitStatus);

            
            /* To check if child terminated normally, and if so, to
               print both its pid and its exit status */
            if(WIFEXITED(exitStatus)){

                printf("\n");
                printf("Child %d, exited with %d\n\n", pid, 
                WEXITSTATUS(exitStatus));

            } 
            // To check if child terminated abnormally
            else if (WIFSIGNALED(exitStatus)){
                
                printf("\n");
                printf("Child %d, exited with %d\n\n", pid, 
                WTERMSIG(exitStatus));
            
            }
        }
    }




    return 0;
}