#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 5000 // Server port
#define MAXLINE 1000 // Maximum size of the message buffer
#define IP "10.0.2.15" // IP address of the server

int main() {
    int sockfd; // Socket file descriptor
    char buffer[MAXLINE]; // Buffer to store received messages
    char *message = "Hello from Server"; // Message to send to the client
    struct sockaddr_in servaddr, cliaddr; // Structures for server and client addresses
    socklen_t len; // Variable to store address length
    int n; // Variable to store message length

    // Creating socket file descriptor for UDP communication
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Clearing and setting server address details
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_port = htons(PORT); // Set port number
    servaddr.sin_addr.s_addr = inet_addr(IP); // Set server's IP address

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // Receive message from client
    len = sizeof(cliaddr); // Length of client address
    n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
    if (n < 0) {
        perror("Receive failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0'; // Null-terminate the received message
    printf("Client: %s\n", buffer); // Print the received message

    // Send response to the client
    sendto(sockfd, message, MAXLINE, MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
    printf("Response sent to client\n");

    // Close the socket
    close(sockfd);
    return 0;
}
