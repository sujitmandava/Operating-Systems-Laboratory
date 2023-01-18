#include <unistd.h>
#include <filesystem>
#include <sys/wait.h>
#include <bits/stdc++.h>
#include <fcntl.h>

using namespace std;

int main ()
{
    int pid;
    int fd[2];
    char command[] = "./square";

    //constructing a pipe
    if(pipe(fd)==-1)
        cout<<"Pipe1 Failed";

    //first fork
    pid = fork();
    if(pid<0)
    {
        cout<<"fork failed";
    }
    else if(pid == 0)
    {
        cout<<"inside child 1\n";
        close(0);

        //opening input file at fd = 0
        if(open("input",O_RDONLY) != 0)
            cerr<<"Failed input open\n";

        //connecting write end of pipe to first child process
        dup2(fd[1],1);
        close(fd[1]);
        close(fd[0]);

        char *args[] = {command,NULL};
        //calling exec system call
        execlp(command,command,(char*)NULL);
        
        cerr<<"execv1 failed\n";
        exit(0);
    }

    //second fork
    pid = fork();
    if(pid<0)
    {
        cout<<"fork failed";
    }
    else if(pid == 0)
    {
        cout<<"inside child 2\n";
        
        //connecting read end of the pipe to second child process
        dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);

        char *args[] = {command,NULL};
        //calling exec system call
        execlp(command,command,(char*)NULL);

        cerr<<"execv2 failed\n";
        exit(0);
    }

    wait(NULL);
    cout<<"After wait\n";
    return 0;
}