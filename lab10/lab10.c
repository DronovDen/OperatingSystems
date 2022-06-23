#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char **argv)
{
    if (argc < 2)
    {
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork(); // Creating new process
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // Child process
    if (pid == 0)
    {
        execvp(argv[1], &argv[1]);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    // Parent process
    else
    {
        // status contains the child process exit code
        int status;
        if (wait(&status) == -1)
        {
            perror("wait");
            exit(EXIT_FAILURE);
        }
        // process ended execution by exit
        if (WIFEXITED(status))
        {
            printf("Child process %d exited with status %d\n", pid, WEXITSTATUS(status));
        }
        // process ended execution by signal
        if (WIFSIGNALED(status))
        {
            printf("Child process %d ended by signal %d", pid, WTERMSIG(status));
        }
    }
    exit(EXIT_SUCCESS);
}
