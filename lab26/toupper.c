#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>

#define MSGSIZE 100

int main()
{
    char buf[MSGSIZE];
    int len;

    while ((len = read(fileno(stdin), buf, MSGSIZE)) > 0)
    {
        for (int i = 0; i < len; i++)
            buf[i] = toupper(buf[i]);
        write(1, buf, len);
    }
    exit(EXIT_SUCCESS);
}
