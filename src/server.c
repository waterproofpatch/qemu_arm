// Server side C/C++ program to demonstrate Socket programming
// socket code basis shamelessly stolen from
// https://www.geeksforgeeks.org/socket-programming-cc/, so much boilerplate
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5001

int handle();

int main(int argc, char const *argv[])
{
    int                server_fd, new_socket;
    struct sockaddr_in address;
    int                opt     = 1;
    int                addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family      = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port        = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int res = handle(new_socket);
    return 0;
}

int handle(int new_socket)
{
    char  buffer[1024] = {0};
    char *hello        = "Hello from server";
    int   valread      = 0;

    bzero(buffer, 1024);
    while (1)
    {
        valread = read(new_socket, buffer, 1024);
        if (valread < 0)
        {
            printf("Socket teardown...\n");
            break;
        }
        printf("received %s\n", buffer);
        bzero(buffer, 1024);
    }
    return 1;
}
