#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int ft_popen(const char *file, char *const argv[], char type)
{
    int fd[2];
    pid_t pid;

    if (!file || !argv || (type != 'r' && type != 'w'))
        return -1;
    pipe(fd);
    pid = fork();
    if (pid == 0)
    {
        if (type == 'w')
            dup2(fd[0], 0);
        if (type == 'r')
            dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        execvp(file, argv);
        exit (1);
    }
    if (type == 'w')
    {
        close(fd[0]);
        return (fd[1]);
    }
    if (type == 'r')
    {
        close(fd[1]);
        return (fd[0]);
    }
}