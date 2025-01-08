#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#define PORT 9999
#define IP "10.0.2.15"
int main()
{
    printf("Welcome to NP-Socket Lab-1\n");

    int fd, confd;                     // File descriptors for the server and client sockets
    char str[INET_ADDRSTRLEN];         // Buffer to store client IP address
    struct sockaddr_in server, client; // Socket address structures
    char sendBuff[1024];               // Buffer for sending data
    time_t ticks;                      // Variable to store current time

    // Create a socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created with descriptor [%d]\n", fd);

    // Initialize server structure and buffers
    memset(&server, 0, sizeof(server));
    memset(sendBuff, 0, sizeof(sendBuff));

    // Configure server settings
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_port = htons(PORT);

    // Bind the socket to the IP and port
    if (bind(fd, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Bind failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Socket successfully bound to port %d\n", PORT);

    // Listen for incoming connections
    if (listen(fd, 5) < 0)
    {
        perror("Listen failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Server is listening for connections...\n");

    // Accept a client connection
    socklen_t clientLen = sizeof(client);
    confd = accept(fd, (struct sockaddr *)&client, &clientLen);
    if (confd < 0)
    {
        perror("Accept failed");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Connection accepted from client [%s:%d]\n",
           inet_ntop(AF_INET, &client.sin_addr, str, INET_ADDRSTRLEN),
           ntohs(client.sin_port));

    // Get the current time and send it to the client
    ticks = time(NULL);
    snprintf(sendBuff, sizeof(sendBuff), "Current time: %.24s\r\n", ctime(&ticks));
    write(confd, sendBuff, strlen(sendBuff));
    printf("Sent time to client: %s", sendBuff);

    // Close connections
    close(confd);
    close(fd);

    return 0;
}
