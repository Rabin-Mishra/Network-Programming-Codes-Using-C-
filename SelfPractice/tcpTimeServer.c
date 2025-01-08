// UNIX PROGRAMMING server code
// HEADER FILES DEFINITION
#include <stdio.h>      //For standard I/O operation
#include <stdlib.h>     //For memory management and program termination
#include <time.h>       // For working with time functions
#include <unistd.h>     //For POSIX OS API,including close()
#include <string.h>     //For string manipulation function like strcpy,snprintf
#include <netinet/in.h> //For sockaddr_in structure ,AF_INET and htons/ntohs
#include <sys/socket.h> //For socket related functions

// MACRO DEFINITION
#define EXIT_SUCCESS 0     // Define exit status for successful execution
#define PORT 9999          // PORT number  server will listen for incoming client
#define IP "192.168.1.157" // IP address of server to which it will bind

// MAIN FUNCTION DEFINITION
int main(int argc, char *argv[])
{
    char clientIPBuff[100];             // holds client IP address
    char writeBuff[100], readBuff[100]; // for sending and receiving message to and from client
    time_t current_time;                // to store the current time

    // SOCKET CREATION
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
    {
        perror("Socket creation failed")
            exit(EXIT_FAILURE);
    }
    printf("Socket created successfully with descriptor as [%d]\n", server_fd);

    // SETTING UP THE SERVER ADDRESS
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;            // address of IPV4
    server_addr.sin_port = htons(PORT);          // port in network byte order
    server_addr.sin_addr.s_addr = inet_addr(IP); // converts ip string into required numerical format

    // BINDING THE SOCKET
    int server_addr_len = sizeof(server_addr);
    int socket_bind = bind(server_fd, (struct sockaddr *)&server_addr, (socklen_t)server_addr_len);

    if (socket_bind == 1)
    {
        perror("Binding of socket failed");
        exit(EXIT_FAILURE);
    }

    // LISTENING
    printf("Sever is listening on IP : %s and PORT :%d \n", IP, PORT);

    int backlog = 2; // max number of pending connections that the server can handle before refusing the new ones
    listen(server_fd, backlog);

    // ACCEPTING THE CLIENT CONNECTION
    // accept() function blocks and waits for the incoming client connection
    int client_addr_len = sizeof(client_addr);
    int accept_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t)*client_addr_len);
    if (accept_fd == -1)
    {
        perror("Client request not accepted\n");
        exit(EXIT_FAILURE);
    }

    // RETRIEVING THE CLIENT IP ADDRESS AND PORT NUMBER
    // inet_ntop()=>converts the binary IP address from the clients sockaddr_in structure into a human readable format
    inet_ntop(AF_INET, &client_addr.sin_addr, clientIPBuff, sizeof(clientIPBuff));
    printf("Client connected from IP:%s & PORT:%d...\n", clientIPBuff, ntohs(client_addr.sin_port));

    // RECEIVING THE DATA FROM THE CLIENT
    int i = read(accept_fd, readBuff, sizeof(readBuff));
    printf("%d byte received and message from the client is %s", i, readBuff);

    // SENDING THE DATA TO THE CLIENT
    // time(NULL)=> gets the current time in seconds since the UNIX epoch
    current_time = time(NULL);
    // snprintf()=> formats the time string and stores in the local time zone
    snprintf(writeBuff, sizeof(writeBuff), "%.24s\r\n", ctime(&current_time));
    printf("Sending time %s\n", writeBuff);
    write(accept_fd, writeBuff, sizeof(writeBuff));

    // CLOSE CONNECTIONS
    close(accept_fd); // closes the client connection
    close(server_fd); // closes the socket connection

    return EXIT_SUCCESS; // returns EXIT_SUCCESS to indicate that it compiled successfully
}