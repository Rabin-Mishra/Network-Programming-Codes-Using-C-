#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 9999
#define IP "10.0.2.15"

int main()
{
    printf("Welcome to NP-Socket Lab-2{} Client\n");

    int sockfd;                    // File descriptor for the socket
    struct sockaddr_in serverAddr; // Server address structure
    char sendBuff[1024];           // Buffer for sending data
    char recvBuff[1024];           // Buffer for receiving data

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Socket created with descriptor [%d]\n", sockfd);

    // Initialize server address structure
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);

    // Convert and set the IP address
    if (inet_pton(AF_INET, IP, &serverAddr.sin_addr) <= 0)
    {
        perror("Invalid address or address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Request a connection to the server
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Connection to server failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Connected to server [%s:%d]\n", IP, PORT);

    // Send a message to the server
    snprintf(sendBuff, sizeof(sendBuff), "Hello, Server! This is Client.\n");
    if (write(sockfd, sendBuff, strlen(sendBuff)) < 0)
    {
        perror("Write to server failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Message sent to server: %s", sendBuff);

    // Receive a message from the server
    memset(recvBuff, 0, sizeof(recvBuff));
    if (read(sockfd, recvBuff, sizeof(recvBuff) - 1) < 0)
    {
        perror("Read from server failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Message received from server: %s", recvBuff);

    // Close the socket
    close(sockfd);
    printf("Connection closed.\n");

    return 0;
}
