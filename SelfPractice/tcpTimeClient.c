//  HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

// PREPROCESSOR DIRECTIVES
#define IP "192.168.1.157"
#define PORT 9999

// MAIN FUNCTION
int main(int argc, char *argv[])
{
    char readBuff[100];
    char writeBuff = "What's the Current time right now?";

    // socket creation
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0)
    {
        perror("Socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully with the descriptor as [%d]", socket_fd);

    // SETTING UP THE SERVER'S ADDRESS STRUCTURE
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);

    // CONNECT CALL
    int confd = connect(socket_fd, (struct sockaddr *)&server, sizeof(server));
    if (confd == -1)
    {
        perror("Connection request failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Connection established successfully with server IP :%s and PORT :%d\n", IP, PORT);
    // WRITE CALL
    printf("Client requesting to the server :%s\n", writeBuff);
    write(socket_fd, writeBuff, sizeof(writeBuff));

    // READ CALL
    int i = read(socket_fd, readBuff, sizeof(readBuff));
    printf("%d byte received from the server and response from the server is :%s", i, readBuff);
    // CLOSE CALL
    close(confd);
    close(socket_fd);

    return 0;
}