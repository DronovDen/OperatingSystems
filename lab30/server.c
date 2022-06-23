#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define SOCKET_NAME "d.dronov_socket"
#define SIZE sizeof(struct sockaddr_un)

int main()
{
    // consists information about server socket address
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

    // using server address to bind it with socket descriptor
    // bind may return -1 if socket for this address already exists
    if (bind(soc_desc, (const struct sockaddr *)&address, SIZE) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(soc_desc, 1) == -1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // accepting a connection request
    int newsock_desc = accept(soc_desc, NULL, NULL);
    if (newsock_desc == -1)
    {
        perror("accept");
        close(soc_desc);
        exit(EXIT_FAILURE);
    }

    unlink(SOCKET_NAME);

    char buf[BUFSIZ];
    int len;
    while ((len = read(newsock_desc, buf, BUFSIZ)) > 0)
    {
        for (int i = 0; i < len; i++)
        {
            buf[i] = toupper(buf[i]);
        }
        write(1, buf, len);
    }
    if (len == -1)
    {
        perror("read");
        close(soc_desc);
        close(newsock_desc);
        exit(EXIT_FAILURE);
    }

    close(soc_desc);
    close(newsock_desc);
    exit(EXIT_SUCCESS);
}
