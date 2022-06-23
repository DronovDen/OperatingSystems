#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <zconf.h>
#include <stdlib.h>

#define SOCKET_NAME "d.dronov_socket"
#define SIZE sizeof(struct sockaddr_un)

int main(int argc, char *argv[])
{
    // char buff[BUFSIZ];

    // structure that contains server socket address
    struct sockaddr_un address;
    memset(&address, 0, SIZE);
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, SOCKET_NAME, sizeof(address.sun_path) - 1);

    int soc_desc = socket(AF_UNIX, SOCK_STREAM, 0);
    if (soc_desc == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int connect_result = connect(soc_desc, (struct sockaddr *)&address, SIZE);
    if (connect_result == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    /*char buf[] = "HelLo, iT's ClIeNt CalLiNg!";
    write(soc_desc, buf, strlen(buf));*/

    char buf[BUFSIZ];
    int len;
    while ((len = read(STDIN_FILENO, buf, BUFSIZ)) > 0)
    {
        if (write(soc_desc, buf, len) != len)
        {
            if (len == -1)
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }

    close(soc_desc);
    exit(EXIT_SUCCESS);
}
