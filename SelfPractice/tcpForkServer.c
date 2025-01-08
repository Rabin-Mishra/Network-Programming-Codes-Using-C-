// HEADER FILES DEFINTION
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

// MACRO DEFINITIION
#define IP "192.168.1.157"
#define PORT 9999

/*
Flow of program
socket
bind
listen
accept
read----->connection fd
write----connection fd
close
*/
// MAIN FUNCTION DEFINITION
int main(int argc, char *argv[])
{
    char writeBuf[100] = "I am TCP Server";
    char readBuff[100];
    char clientIPBuff[100];

    // SOCKET CREATION
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed \n");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    // Defintion of the structure
    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);

    // BINDING THE FUNCTIONS
    int bindfd = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (bindfd == -1)
    {
        perror("Bind Failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on IP;%s and PORT :%d\n", IP, PORT);
    int backlog = 5;
    listen(sockfd, backlog);

    while (1)
    {
        socklen_t addr_len = sizeof(client);
        int confd = accept(sockfd, (struct sockaddr *)&client, &addr_len);
        if (confd == -1)
        {
            perror("Connection accept failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        inet_ntop(AF_INET, &client.sin_addr, clientIPBuff, sizeof(clientIPBuff));
        printf("Client connected form IP:%s and PORT %d.....\n", clientIPBuff, ntohs(client.sin_port));

        pid_t pid = fork();

        if (pid == 0)
        {
            // client section
            close(sockfd);
            read(confd, readBuff, sizeof(readBuff));
            printf("Client message %s\n", readBuff);
            write(confd, writeBuf, sizeof(writeBuf));
            printf("Server respond :%s\n", writeBuf);
            close(confd);
            exit(EXIT_SUCCESS);
        }
        close(confd);
    }
    close(sockfd);
    return 0;
}