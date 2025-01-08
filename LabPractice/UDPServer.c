// server program for the UDP connection
#include <stdio.h>   // Provides functions for input/output operations
#include <strings.h> //Provides functions like bzero for memory handling.
#include <stdlib.h>
#include <sys/types.h>  //Defines data types used in system calls
#include <arpa/inet.h>  //Contains definitions for internet operations, e.g., htons, htonl.
#include <sys/socket.h> //Provides socket functions and structures
#include <netinet/in.h> //efines structures for internet addresses.
#define PORT 5000       // Defines the port number on which the server will listen.
#define MAXLINE 1000    // Defines the maximum length of the message buffer.
#define IP "10.0.2.15"  //  IP address of the server

// driver code
int main()
{
    // buffer to hold the received messages
    char buffer[100];
    // message to be sent to the client
    char *message = 'Hello Client';
    // file descriptor for the socket
    int listenfd, len;
    // structure to hold the server and client address
    struct sockaddr_in serveraddr, cliaddr;
    // clear the server address structure
    bzero(&serveraddr, sizeof(serveraddr));

    // create a UDP socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);

    // setting the server address details
    serveraddr.sin_addr.s_addr = inet_addr(IP);
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_family = AF_INET;

    // Bind the server address to the socket descriptor
    bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    // recieve the datagram (incoming message) from the client
    len = sizeof(cliaddr); // initialize the length of the client address
    // receive the message from the client and store it in the buffer
    int n = recvfrom(listenfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);

    // null will terminate the received message
    buffer[n] = '\0';
    // print the received message
    puts(buffer);

    // send a response message to the client
    sendto(listenfd, message, MAXLINE, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}