#include "types.h"
#include "user.h"
#include "syscall.h"

int main(int argc, char *argv[])
{
    printf(1, "initial fork count %d\n", getcount(SYS_fork));
    if (fork() == 0)
    {
        printf(1, "\nChild process: \n");
        printf(1, "Fork count %d\n", getcount(SYS_fork));
        printf(1, "Write count %d\n", getcount(SYS_write));
        
        int pfd[2];
        pipe(pfd);
        close(pfd[0]);
        close(pfd[1]);

        printf(1, "Pipe count %d\n", getcount(SYS_pipe));
    }
    else
    {
        wait();
        printf(1, "\nParent process: \n");
        printf(1, "Fork count %d\n", getcount(SYS_fork));
        printf(1, "Write count %d\n", getcount(SYS_write));
        int fd = open("README", 0);
        close(fd);
    }
    printf(1, "Wait count %d\n", getcount(SYS_wait));
    printf(1, "Open count %d\n", getcount(SYS_open));
    printf(1, "Close count %d\n", getcount(SYS_close));
    exit();
}