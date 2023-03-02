#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>  //for reding the names of the files/directorys using [  DIR *dir = opendir(".");  ]
#include <signal.h>  //for blocking 
#define Length 100



void Exit(){  
    printf("\nExit the program safly"); exit(0);     //all open Files are closed safly
}

void unknown_command(char *cmd){   printf("%s: command not found\n" , cmd);   }
void help(){
    printf("ls: lists each file/directory in the current directory\n");
    printf("ls (argument): argument may be directory name in the current directory\n");
    printf("or a path to lists each file/directory in that directory or path\n\n");
    printf("cat (file name): Opens the file and reads all the content and prints it\n\n");
    printf("retrieve(argument): This retrieves, or downloads, the files\n\n");
    printf("stats(): Prints statistics related to files and networking\n");
    printf("exit(): to exit safely\n\n");
}

int cat(char *file_name){
    
    if(file_name[0] == '*')
        cat_star(file_name);
    else
{
        
    
    FILE *P_file;
    char F_name[Length];
    
    sscanf(file_name, "%s", F_name);  //copy the string (file name) to F_name
    P_file = fopen(F_name, "r");  //open the file for reading

    if(P_file == NULL){      //checking wether the file is founded in the directory or not
        printf("The file '%s' not found\n" , F_name);
        return 1;            //exit the function
    }
    
    char ch;
    
    while((ch = fgetc(P_file)) != EOF){    //while it did not reach the End Of File 
        printf("%c", ch);              //pirnt the file charecter by charecter
    }
    
    printf("\n");
    fclose(P_file);    // Closeing the file safely
    return 1;
    
}
}

int ls(char *arg){
    DIR *dir;
    char arg_name[Length];
    
    char After_dot[3];
    int t = 0;
    if(arg == NULL){          
        dir = opendir("."); 
        t = 1;
    }
    else{
        if(arg[0] == '*'){
            sscanf(strchr(arg,'.'), "%s", After_dot);
            dir = opendir(".");
            
        }
        else{
            sscanf(arg, "%s", arg_name);
            dir = opendir(arg_name);
            t = 1;
        }
    }


    struct dirent *entry;         //struct built in library <dirent.h>

    if(dir == NULL){              //avoiding crashing/errors
        printf("Error, this directory cannot be opend\n");
        return 1;
    }
    
    int n = 0;
    
    while((entry = readdir(dir)) != NULL){  //loop through all files/directorys and print their names
    
    
        if(t == 1){
            printf("%s     ", entry->d_name);
        }
        
        else if(strchr(entry->d_name , '.') != NULL){
            
            if(strcmp(strchr(entry->d_name , '.') , After_dot) == 0)
                printf("%s     ", entry->d_name);
        }
            
        n++;                                
        if(n % 5 == 0)            //just to organize
            printf("\n");
    }
    printf("\n");
    closedir(dir);                //closing the directory safely
    return 1;
}

int cat_star(char *arg){
    DIR *dir;
    char arg_name[Length];
    
    char After_dot[3];
    int t = 0;
    
    if(arg[0] == '*'){
        sscanf(strchr(arg,'.'), "%s", After_dot);
        dir = opendir(".");
    }
    else
        return 1;


    struct dirent *entry;         //struct built in library <dirent.h>
    
    if(dir == NULL){              //avoiding crashing/errors
        printf("Error, this directory cannot be opend\n");
        return 1;
    }
    
    
    while((entry = readdir(dir)) != NULL){  //loop through all files/directorys and print their names
    
        if(strchr(entry->d_name , '.') != NULL)
            if(strcmp(strchr(entry->d_name , '.') , After_dot) == 0)
                cat(entry->d_name);
                
    }
    printf("\n");
    closedir(dir);                //closing the directory safely
    return 1;
}
