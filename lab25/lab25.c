#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define MSGSIZE 100

int main(int argc, char **argv)
{
    int filedescs[2] = {0};
    char out[] = "HeLlO, wOrLd!\n";

    if (pipe(filedescs) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    // filedescs[0] - read
    // filedescs[1] - write

    // SENDER
    pid_t pid_1 = fork();
    if (pid_1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid_1 == 0) // First child
    {
        close(filedescs[0]);
        write(filedescs[1], out, strlen(out));
        close(filedescs[1]);
        exit(EXIT_SUCCESS);
    }

    // RECIEVER
    pid_t pid_2;
    if (pid_1 > 0)
    {
        pid_2 = fork();
    }
    if (pid_2 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid_2 == 0)
    {
        close(filedescs[1]);
        int length;
        char output[MSGSIZE];
        while ((length = read(filedescs[0], output, MSGSIZE)) > 0)
        {
            for (int i = 0; i < length; i++)
            {
                output[i] = toupper(output[i]);
            }
            write(1, output, length);
        }
        close(filedescs[0]);
        exit(EXIT_SUCCESS);
    }

    close(filedescs[0]);
    close(filedescs[1]);

    int status1, status2;
    waitpid(pid_1, &status1, 1);
    if (WIFEXITED(status1) != 0)
    {
        printf("First child process %d exited with status %d\n", pid_1, WEXITSTATUS(status1));
    }
    waitpid(pid_2, &status2, 1);
    if (WIFEXITED(status2) != 0)
    {
        printf("Second child process %d exited with status %d\n", pid_2, WEXITSTATUS(status2));
    }
    exit(EXIT_SUCCESS);
}

