#include <unistd.h>
#include <filesystem>
#include <sys/wait.h>
#include <bits/stdc++.h>
#include <fcntl.h>
#define MAXLIMIT 100

using namespace std;

void siginthandler(int p)
{
    cout << "#\n";
    return;
}

void parseInput(char *command, vector<string> &tokens)
{
    // cout << command << "\n";
    string currString = "";
    for (int i = 0; i < MAXLIMIT; i++)
    {
        // cout << command[i] << ".\n";
        if (command[i] == '\0')
        {
            tokens.push_back(currString);
            return;
        }
        else if (command[i] == ' ')
        {
            if (currString != "")
                tokens.push_back(currString);
            currString = "";
        }
        else
        {
            currString = currString + command[i];
        }
    }
}

void runInBuilt(vector<string> tokens)
{
    if (tokens[0] == "exit")
    {
        exit(0);
    }
    else if (tokens[0] == "pwd")
    {
        // char *args[] = {"pwd", NULL};
        // pid_t pid = fork();

        // if (pid == 0)
        // {
        //     execvp(args[0], args);
        // }
        // else
        // {
        //     wait(0);
        // }
        char currPath[256];
        getcwd(currPath, 256);
        cout << currPath << "\n";
    }
    else
    {
        string path = tokens[1];
        if (tokens[1] == "<<<")
        {
            path = tokens[2];
        }
        chdir(tokens[1].c_str());
        char currPath[256];
        getcwd(currPath, 256);
        // cout << currPath << "\n";
    }
}

void changeIO(vector<string> tokens, int i)
{
    if (tokens[i] == "<<<")
    {
        if (i + 1 >= tokens.size() || tokens[i+1]=="||")
        {
            cout << "Invalid Input Redirection file";
        }
        else
        {
            char *filename = &tokens[i + 1][0];
            close(0);
            int fd = open(filename, O_RDONLY);
            if (fd != 0)
            {
                cout << "Redirection Failed\n";
                exit(0);
            }
        }
    }
    else if (tokens[i] == ">>>")
    {
        // cout<<">>> detected";
        if (i + 1 >= tokens.size() || tokens[i+1]=="||")
        {
            cout << "Invalid Output Redirection file";
        }
        else
        {
            // cout<<">>> file also detected";
            char *filename = &tokens[i + 1][0];
            close(1);
            int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
            if (fd != 1)
            {
                cout << "Redirection Failed\n";
                exit(0);
            }
        }
    }
    else if (tokens[i] == "&>>")
    {
        if (i + 1 >= tokens.size() || tokens[i+1]=="||")
        {
            cout << "No Redirection File Given";
        }
        else
        {
            char *filename = &tokens[i + 1][0];
            close(1);
            close(2);
            int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
            dup(1);
            if (fd != 1)
            {
                cout << "Redirection Failed\n";
                exit(0);
            }
        }
    }
}

int main()
{
    vector<string> tokens;

    int i = 0;
    int whilecount = 10;
    while (1)
    {
        // if (signal(SIGINT, siginthandler))
        // {
        //     cout << "sig called\n";
        // }
        int pipesCount = 0;
        tokens.clear();
        write(1, "# ", 2);
        char command[MAXLIMIT];
        int rc = read(0, command, MAXLIMIT);
        // cout << command << ": Command\n";
        command[rc - 1] = '\0';
        int tokNO = 0;
        bool pipeline = false;

        // Parse command with delimiter " "
        parseInput(command, tokens);

        for (int i = 0; i < tokens.size(); i++)
        {
            // cout << tokens[i] << '\n';
            if (tokens[i] == "||")
            {
                pipeline = true;
                pipesCount += 1;
            }
        }

        if (tokens[0] == "cd" || tokens[0] == "pwd" || tokens[0] == "exit")
        {
            // Function 1
            runInBuilt(tokens);
        }
        else
        {
            // I/O redirection
            // for (int i = 0; i < tokens.size(); i++)
            // {
            //     if(tokens[i]=="<<<" || tokens[i]==">>>" || tokens[i] == "&>>")
            //     {
            //         changeIO(tokens,i);
            //     }
            // }
            if (pipeline)
            {
                // Function 2.2
                // Get all pipelined commands
                // Loop over commands
                //      pipe() data of child process to parent process and use it in the next child process
                // exit()
                // cout<<"Pipelining required\n";
                int pipefd[pipesCount+1][2];
                int pipc =0;
                bool isTokenIO = false;
                for (int i = 0; i < tokens.size(); i++)
                {
                    if(isTokenIO)
                    {
                        isTokenIO = false;
                        continue;
                    }
                    if (tokens[i] == "||")
                    {
                        continue;
                    }
                    else if(tokens[i] == "<<<" || tokens[i] == ">>>" || tokens[i] == "&>>")
                    {
                        isTokenIO = true;
                        continue;
                    }
                    else
                    {
                        char *currCommand = &tokens[i][0];
                        char *currArgs[] = {currCommand, NULL};

                        if (pipe(pipefd[pipc]) == -1)
                        {
                            fprintf(stderr, "Pipe Failed\n");
                            break;
                        }
                        if (pipc == 0)
                        {
                            if (currCommand[0] != '.' && currCommand[1] != '/')
                            {
                                break;
                            }
                        }

                        int pid1;
                        pid1 = fork();
                        if (pid1 < 0)
                        {
                            fprintf(stderr, "fork() failed.\n");
                            break;
                        }
                        else if (pid1 == 0)
                        {
                            if (pipc != pipesCount)
                            {
                                dup2(pipefd[pipc][1], 1);
                                close(pipefd[pipc][0]);
                                close(pipefd[pipc][1]);
                            }

                            if (pipc != 0)
                            {
                                dup2(pipefd[pipc - 1][0], 0);
                                close(pipefd[pipc - 1][1]);
                                close(pipefd[pipc - 1][0]);
                            }

                            if(pipc==0 && tokens[i+1] == "<<<")
                            {
                                // cerr<<"output redirection detected, i: "<<i<<" pipc: "<<pipc<<"\n";
                                changeIO(tokens,i+1);
                                i+=2;
                            }
                            else if(pipc == pipesCount &&(tokens.size()>i+1))
                            {
                                if((tokens[i+1] == ">>>"||tokens[i+1] == "&>>"))
                                {
                                    // cerr<<"output redirection detected";
                                    changeIO(tokens,i+1);
                                    i+=2;
                                }
                            }
                            execv(currCommand, currArgs);
                            cerr<<"Invalid command detected:\n Execution of "<<currCommand<<" failed.\n";
                            exit(0);
                        }
                        else
                        {
                            // Parent process
                            if (pipc != 0)
                            { // second process
                                close(pipefd[pipc - 1][0]);
                                close(pipefd[pipc - 1][1]);
                            }
                            pipc++;
                        }
                        
                    }
                    // else if (tokens[i + 1] == "<<<" || tokens[i + 1] == ">>>" || tokens[i + 1] == "&>>")
                    // {
                    //     changeIO(tokens, i);
                    //     goto L1;
                    // }
                }
                while(wait(NULL) > 0);
            }
            else
            {
                // cout<<"Pipelining not required"<<tokens[0]<<"<";
            // Function 2.1 -> No pipeline

                L1:
                bool pWait = true;
                for (int i = 0; i < MAXLIMIT && command[i] != '\0'; i++)
                {
                    if (command[i] == '&' && command[i + 1] == '\0')
                    {
                        pWait = false;
                        command[i] = '\0';
                    }
                }

                pid_t pid = fork();

                if (pid < 0)
                {
                    fprintf(stderr, "fork() failed.\n");
                }
                else if (pid == 0)
                {
                    // Function 2: Run Process
                    for (int i = 0; i < tokens.size(); i++)
                    {
                        if (tokens[i] == "<<<" || tokens[i] == ">>>" || tokens[i] == "&>>")
                        {
                            cout << "detected redirection at " << i;
                            changeIO(tokens, i);
                        }
                    }
                    if (tokens[0][0] == '.' && tokens[0][1] == '/')
                    {
                        char *args[] = {&tokens[0][0], NULL};
                        // cout << command << "\n";
                        execv(&tokens[0][0], args);
                        // never executed
                        exit(0);
                    }
                }
                else
                {
                    if (pWait == true)
                        wait(0);
                    // printf("Parent Process:\n");
                }
            }

            // Change I->STDIN and O->STODUT
        }
        // tokens.clear();
        // close(0);
        // open("stdin",O_RDONLY);
        // close(1);
        // open()
    }
}
