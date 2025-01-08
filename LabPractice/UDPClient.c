#include <stdio.h>      //standard input output functions
#include <strings.h>    //bzero function memory operations
#include <sys/types.h>  //data types used in system calls
#include <arpa/inet.h>  //internet operations like htons and htonl
#include <sys/socket.h> //scoket functions and structures
#include <netinet/in.h> //structure for internet addresses
#include <unistd.h>     //fuctions like close
#include <stdlib.h>     //standard library functions like exit
#define PORT 5000       // port number on which server will listen
#define MAXLINE 1000
#define IP "10.0.2.15" // define max size of buffer

// driver code
int main()
{
    char buffer[100];               // buffer to hold the server's response
    char *message = "Hello server"; // message to be sent to the server
    int sockfd, len;                // file descriptor for the socket
    struct sockaddr_in serveraddr;  // Structure to store server's address details

    // clear the serveraddr structure to ensure no garbage values are present
    bzero(&serveraddr, sizeof(serveraddr));

    // set the server's IP Address
    serveraddr.sin_addr.s_addr = inet_addr(IP);
    serveraddr.sin_port = htons(PORT); // set the server port converted to network byte order
    serveraddr.sin_family = AF_INET;   // set the address family for IPV4

    // create a datagram UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // connect to the server using the socket descriptor
    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("Connection to server failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    // request to send datagram
    // no need to specify the server address in sendto
    // connect stores the peers IP and port
    sendto(sockfd, message, MAXLINE, 0, (struct sockaddr *)NULL, sizeof(serveraddr));

    // wait for the servers response
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)NULL, NULL);
    puts(buffer);

    // close the descriptor
    close(sockfd);
}