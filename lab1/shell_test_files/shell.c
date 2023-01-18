#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main ()
{
    int i=0;
    while (1)
    {   
        write(1,"# ",2);
        // char *command = (char *) malloc(sizeof(char) * 100);
        char command[100];
        char *token;
        char *redirection;
        char *redirLocation;
        int rc = read(0,command,100);
        if(rc!=1)
            command[rc-1] = '\0';
        
        token = strtok(command," ");
        
        if (strcmp(token,"exit")==0)
        {
            exit(0);
        }
        // printf("%d.",strcmp(token,"exit\n"));

        pid_t pid = fork();
        if(pid < 0)
        {
            fprintf(stderr, "fork() failed.\n");
        }
        if(pid == 0)
        {
            // printf("child process: %s",command);
            // printf("rc = %d\n", rc);
            // command[rc-1] = '\0';
            // execl("./hello","./hello",NULL);
            // execv(command, args);
            // char *binaryPath = "./hello";
            // redirection = strtok(NULL," ");
            // if(strcmp(redirection,">>>"));
            // redirLocation = strtok(NULL," ");
            // open

            char *args[] = {token, "-lh", "/home", NULL}; 
            execv(token, args);
            
            // not execute 
            exit(0);
        }
        else{

            // if(rc>=2)
            // if((command[rc-2]!='&')&&(command[rc-3]))
            wait(0);

            // printf("Parent Process:\n");
        }
    }


}
