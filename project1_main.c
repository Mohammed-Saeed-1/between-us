#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>  //for reding the names of the files/directorys using [  DIR *dir = opendir(".");  ]
#include <signal.h>  //for blocking 
#define Length 100

void Exit();
void unknown_command(char *);
void help();
int cat(char *);
int cat_star(char *);
int ls(char *);


void parse_cmd(char *R_cmd){
    char command[Length] , *argument;

    sscanf(R_cmd, "%s", command); //command = cmd   -->only before the space (argument) ;
    argument = strchr(R_cmd, ' ');     // cmd = (after the space including the space it selfe)

    if(argument != NULL)   //if there is an argument
        argument++;         //remove the space
        

    if(strcmp(command, "help") == 0)  //strcmp (sting compare) ==0 if they are identical (command == help)
        help();
        
    else if(strcmp(command, "exit") == 0)
        Exit();
        
    else if(strcmp(command, "cat") == 0)
        if(argument != NULL)
            cat(argument);
        else
            printf("command 'cat' must have an argument\n");
    
    else if(strcmp(command , "ls") == 0)
        ls(argument);
    else
        unknown_command(command);
}

int main(){
    sigset_t mask, pre_mask;
	sigemptyset(&mask);
	sigaddset(&mask , SIGINT); // SIGINT to block ctrl-C (termination)
	
    
    char str[Length];
    while(1){
        signal(SIGINT , Exit);                       //catch SIGINT (CTRL-C) and call Exit()
        printf("$ ");    fgets(str, Length, stdin);
        
        sigprocmask(SIG_BLOCK, &mask , &pre_mask);  //block ctrl-C
        parse_cmd(str);
        sigprocmask(SIG_SETMASK , &pre_mask, NULL);  //after cleanup unblock 
    }
    
    
    return 0;
}
