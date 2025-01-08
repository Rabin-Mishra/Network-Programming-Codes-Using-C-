#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 9999
#define IP "10.0.2.15"

int main() {
    int sockfd;
    char sendBuff[1024] = "Hello, Server! This is Client.\n";
    char recvBuff[1024];
    struct sockaddr_in serverAddr;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IP, &serverAddr.sin_addr) <= 0 || 
        connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    write(sockfd, sendBuff, strlen(sendBuff));
    read(sockfd, recvBuff, sizeof(recvBuff) - 1);
    printf("Received: %s", recvBuff);

    close(sockfd);
    return 0;
}
