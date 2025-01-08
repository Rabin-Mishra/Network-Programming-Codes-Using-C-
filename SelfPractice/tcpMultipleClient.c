// HEADER FILES
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

// MACRO DEFINTION
#define IP "192.168.1.157"
#define PORT 9999

// MAIN FUNCTION DEFINITION
int main(int argc, char *argv[])
{
    char writeBuff[100] = "Hello I am Client";
    char readBuff[100];
    // SOCKET CREATION

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // SOCKET CREATION CHECK
    if (sockfd < 0)
    {
        perror("Socket creation is failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    // CONFIGURING THE SERVER ADDRESS
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);

    // SETTING A CONNECTION
    int confd = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (confd == -1)
    {
        perror("Connection establishment failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // PRINTING THE MESSAGES
    printf("Client message %s\n", writeBuff);
    write(sockfd, writeBuff, sizeof(writeBuff));
    read(sockfd, readBuff, sizeof(readBuff));
    printf("Server response %s\n", readBuff);

    // CLOSING THE CONNECTIONS
    close(confd);
    close(sockfd);

    return 0;
}
