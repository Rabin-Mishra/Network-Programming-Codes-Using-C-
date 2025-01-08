

### Code Breakdown with Comments

```cpp
// #include "stdafx.h" 
```
- This line is typically used in **Visual Studio** for precompiled headers but is not necessary for most modern C++ compilers (and can be omitted in environments like VS Code). It speeds up compilation by precompiling commonly used headers.

```cpp
#include <io.h>
```
- **`<io.h>`**: This header file is used for low-level I/O operations like file handling. It is part of the Microsoft-specific libraries.

```cpp
#include <tchar.h>
```
- **`<tchar.h>`**: This header is used for supporting both Unicode and ASCII character sets in Windows programming. It helps when writing code that can be compiled with both `UNICODE` and `ANSI` settings.

```cpp
#include <stdio.h>
```
- **`<stdio.h>`**: This is the standard C library header for input/output functions, like `printf` and `scanf`.

```cpp
#include <winsock2.h>
```
- **`<winsock2.h>`**: This header defines functions and constants used for networking on Windows (Winsock API). It's essential for writing networked applications in Windows.

```cpp
#pragma comment(lib, "ws2_32.lib") // linking static library for window socket
```
- **`#pragma comment(lib, "ws2_32.lib")`**: This is a directive to the compiler, telling it to link against the **`ws2_32.lib`** library, which is the Winsock library. This library provides networking functions for TCP/IP communication.

```cpp
#define PORT 8888
#define IP "127.0.0.1"
```
- **`#define PORT 8888`**: This defines the port number `8888` that the server will listen on.
- **`#define IP "127.0.0.1"`**: This defines the IP address `127.0.0.1`, which is the **loopback address** (localhost), meaning the server will only accept connections from the same machine.

```cpp
int main(int argc, char *argv[])
```
- **`int main(int argc, char *argv[])`**: The `main` function, where program execution starts. It takes two arguments:
  - `argc`: The number of command-line arguments.
  - `argv`: An array of strings representing the command-line arguments.

```cpp
    WSADATA wsa;
```
- **`WSADATA wsa`**: A structure used by the Winsock API to store information about the Windows Sockets implementation. It's passed to `WSAStartup` to initialize Winsock.

```cpp
    SOCKET s, new_socket;
```
- **`SOCKET s, new_socket;`**: `SOCKET` is a data type used by the Winsock API to represent socket handles.
  - `s`: The server socket that listens for incoming connections.
  - `new_socket`: A socket that will be used to communicate with a client once the connection is accepted.

```cpp
    struct sockaddr_in server, client;
```
- **`struct sockaddr_in server, client;`**: This structure is used to define the IP address and port of a socket. It’s used for both the server’s and client’s address information.
  - `server`: Holds the server's socket address (IP and port).
  - `client`: Holds the client’s socket address.

```cpp
    int c;
```
- **`int c;`**: This is an integer that will hold the size of the client’s address structure when accepting a connection.

```cpp
    char *message;
```
- **`char *message;`**: A pointer to a string that will hold the message to be sent to the client.

```cpp
    printf("\nInitialising Winsock...");
```
- **`printf("\nInitialising Winsock...");`**: Prints a message to indicate that Winsock is being initialized.

```cpp
    printf("IP and Port\n[%d][%s]\n", PORT, IP);
```
- **`printf("IP and Port\n[%d][%s]\n", PORT, IP);`**: Prints the server’s IP address and port, so the user knows where the server will be listening.

```cpp
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
```
- **`WSAStartup(MAKEWORD(2, 2), &wsa)`**: Initializes the Winsock library. The parameter `MAKEWORD(2, 2)` specifies the version of Winsock to use (in this case, version 2.2).
  - If it fails, `WSAStartup` will return a non-zero value, and `WSAGetLastError()` will provide the error code.

```cpp
    printf("Initialised.\n");
```
- **`printf("Initialised.\n");`**: Prints a message indicating that Winsock has been initialized successfully.

```cpp
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
```
- **`socket(AF_INET, SOCK_STREAM, 0)`**: Creates a TCP socket (`SOCK_STREAM`) using IPv4 (`AF_INET`). If this fails, it returns `INVALID_SOCKET`.
  - The return value is assigned to `s`.

```cpp
    printf("Socket created.\n");
```
- **`printf("Socket created.\n");`**: Prints a message indicating that the socket was created successfully.

```cpp
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP); // INADDR_ANY;
    server.sin_port = htons(8888);
```
- **`server.sin_family = AF_INET;`**: Specifies the address family for the socket. `AF_INET` stands for IPv4.
- **`server.sin_addr.s_addr = inet_addr(IP);`**: Sets the server’s IP address. Here, `inet_addr(IP)` converts the IP string (`127.0.0.1`) to a numerical IP address.
- **`server.sin_port = htons(8888);`**: Sets the server’s port number (8888) and converts it to network byte order using `htons()` (host-to-network short).

```cpp
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
    }
```
- **`bind(s, (struct sockaddr *)&server, sizeof(server))`**: Binds the created socket `s` to the server’s address (`server`).
  - If it fails, `SOCKET_ERROR` is returned, and the error code is displayed.

```cpp
    puts("Bind done");
```
- **`puts("Bind done");`**: Prints a success message indicating that the bind was successful.

```cpp
    listen(s, 3);
```
- **`listen(s, 3);`**: The server socket `s` begins listening for incoming connections. The `3` specifies the maximum number of pending connections in the queue.

```cpp
    puts("Waiting for incoming connections...");
```
- **`puts("Waiting for incoming connections...");`**: Prints a message indicating the server is waiting for client connections.

```cpp
    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d", WSAGetLastError());
    }
```
- **`c = sizeof(struct sockaddr_in);`**: Sets `c` to the size of the address structure, which will be used to hold the client’s address.
- **`accept(s, (struct sockaddr *)&client, &c)`**: Accepts an incoming connection on the server socket `s` and returns a new socket `new_socket` for communication with the client.
  - If the connection fails, it returns `INVALID_SOCKET`.

```cpp
    puts("Connection accepted from Client");
```
- **`puts("Connection accepted from Client");`**: Prints a message indicating that the connection from the client was successfully accepted.

```cpp
    message = "Hello Client , I have received your connection. But I have to go now, bye\n";
    send(new_socket, message, strlen(message), 0);
```
- **`message = "Hello Client..."`**: The message to be sent to the client.
- **`send(new_socket, message, strlen(message), 0);`**: Sends the message to the client over the `new_socket`.

```cpp
    getchar();
```
- **`getchar();`**: Waits for the user to press Enter before closing the program.

```cpp
    closesocket(s);
    WSACleanup();
```
- **`closesocket(s);`**: Closes the server socket `s` after use.
- **`WSACleanup();`**: Cleans up the Winsock library when the program is done.

```cpp
    return 0;
}
```
- **`return 0;`**: The program finishes successfully.

### Summary:
This program initializes Winsock, creates a TCP socket, binds it to a specific IP and port, listens for incoming client connections, accepts a connection, sends a response, and then closes the connection and cleans up. The server is set to listen on `127.0.0.1` (localhost) at port `8888`.