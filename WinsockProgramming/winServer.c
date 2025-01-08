// #include "stdafx.h"==>used in Visual Studio for precompiled headers
#include <io.h> //used for low level IO operations like file handling
#include <stdio.h>//for i/p and o/p functions
#include <winsock2.h>//functions and constants used for networking in windows
#pragma comment(lib, "ws2_32.lib") // linking static library for window socket
#define PORT 8888
#define IP "127.0.0.1"//server accepts connections from same machine which is loopback address
//argc==>Number of command line arguments
//argv==>array of strings representing command line arguments

int main(int argc, char *argv[])
{
    //structure used by Winsock API to store info about windows sockets and passed to WSAStartup to initialize Winsock
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c;//holds the size of clients address structure when accepting a connection
    char *message;//pointer to a string that will hold the message to be sent to client 

    printf("\nInitialising Winsock...");
    printf("IP and Port\n[%d][%s]\n", PORT, IP);
    //in


    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("Initialised.\n");

    // Create a socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }

    printf("Socket created.\n");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP); // INADDR_ANY;
    server.sin_port = htons(8888);

    // Bind
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
    }

    puts("Bind done");

    // Listen to incoming connections
    listen(s, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");

    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d", WSAGetLastError());
    }

    puts("Connection accepted from Client");

    // Reply to client
    message = "Hello Client , I have received your connection. But I have to go now, bye\n";
    send(new_socket, message, strlen(message), 0);

    getchar();

    closesocket(s);
    WSACleanup();

    return 0;
}
/*
To run the code use the command as follows:
gcc winServer.c -o winS -lws2_32
./winS

*/