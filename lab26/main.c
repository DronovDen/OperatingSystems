#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>

#define MSGSIZE 100

int main(int argc, char **argv)
{
    // char buf[MSGSIZE];
    int len;
    FILE *fp = popen("./toupper", "w");

    char buf[] = "HeLlsO, wOrLd!\n";

    if (fp == NULL)
    {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    write(fileno(fp), buf, strlen(buf));

    /*while ((len = read(0, buf, 100)) > 0) // 0 -- fileno(stdin)
        write(fileno(fp), buf, len);*/

    if (pclose(fp) == -1)
    {
        perror("pclose");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
