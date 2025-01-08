

---

### 1. Header Files

```c
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
```

- **`<netinet/in.h>`**: Provides definitions related to Internet domain addresses, particularly for **IPv4** and **IPv6**. It contains the structure `sockaddr_in` and other relevant constants for socket programming.
- **`<stdio.h>`**: Standard input/output library for functions like `printf()` and `perror()`, which are used for printing messages to the console.
- **`<arpa/inet.h>`**: Provides functions to manipulate Internet addresses, such as `inet_addr()` (which converts a string IP address to a network byte order) and `inet_ntop()` (converts network address to presentation format).
- **`<unistd.h>`**: Provides system call interfaces like `close()`, `fork()`, `read()`, and `write()`.
- **`<sys/socket.h>`**: Defines socket-related system calls and constants like `socket()`, `bind()`, `listen()`, and `accept()`.
- **`<sys/types.h>`**: Contains definitions of system types like `pid_t` (for process IDs) and `socklen_t` (for length of socket addresses).
- **`<stdlib.h>`**: Provides functions for memory allocation and process control like `exit()`.

---

### 2. Constants Definition

```c
#define IP "192.168.1.157"
#define PORT 9999
```

- **`#define IP "192.168.1.157"`**: Defines the **server IP address** as `192.168.1.157`. The server will bind to this address for listening.
- **`#define PORT 9999`**: Defines the **port number** the server will listen on (port 9999).

---

### 3. Main Function Definition

```c
int main(int argc, char *argv[])
```

- **`int argc`**: The **argument count**, representing the number of arguments passed to the program when run. This is commonly used to handle command-line arguments.
- **`char *argv[]`**: An **array of strings**, each string representing a command-line argument passed to the program. These arguments can be used to modify server behavior or provide the server's address and port, but in this code, they are not used.

---

### 4. Buffers for Data

```c
char writeBuffer[100] = "I am TCP Server";
char readBuffer[100];
char clientIPBuffer[100];
```

- **`writeBuffer[100]`**: A buffer initialized with the message `"I am TCP Server"`. This message will be sent to the client.
- **`readBuffer[100]`**: A buffer to hold the message that will be received from the client.
- **`clientIPBuffer[100]`**: A buffer to hold the IP address of the client (used to display it after the client connects).

---

### 5. Create the Socket

```c
int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
```

- **`socket()`**: Creates a **socket** for communication.

  **Parameters**:
  - **`AF_INET`**: The **address family**, specifying that the socket will use **IPv4** addresses.
  - **`SOCK_STREAM`**: The **socket type**, specifying a **stream-based** connection, which corresponds to **TCP**.
  - **`IPPROTO_TCP`**: Specifies that the **TCP** protocol should be used.

**Return value**:
- **`sockfd`**: The socket file descriptor (an integer). If the socket creation fails, it returns `-1`.

---

### 6. Error Handling for Socket Creation

```c
if (sockfd < 0) {
    perror("socket creation failed: ");
    close(sockfd);
    exit(EXIT_FAILURE);
}
```

- **`if (sockfd < 0)`**: Checks if the socket creation failed. If `sockfd` is less than `0`, it indicates an error.
- **`perror("socket creation failed: ")`**: Prints the error message corresponding to the `errno` value, explaining why the socket creation failed.
- **`close(sockfd)`**: Closes the socket if it was created but an error occurred.
- **`exit(EXIT_FAILURE)`**: Terminates the program with a failure exit code (`EXIT_FAILURE`), indicating an error occurred.

---

### 7. Prepare the Server Address

```c
struct sockaddr_in server, client;
server.sin_family = AF_INET;
server.sin_addr.s_addr = inet_addr(IP);
server.sin_port = htons(PORT);
```

- **`struct sockaddr_in server, client;`**: Declares two structures of type `sockaddr_in`. One is for the **server's address** (`server`) and the other for the **client's address** (`client`).
  
- **`server.sin_family = AF_INET`**: Sets the address family to **IPv4** for the server.
- **`server.sin_addr.s_addr = inet_addr(IP)`**: Converts the server's IP address from a string (`IP`) to a **binary format** that can be used in network communication.
- **`server.sin_port = htons(PORT)`**: Converts the port number from **host byte order** to **network byte order** using `htons()` (Host to Network Short).

---

### 8. Bind the Socket to the Address

```c
int bindfd = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
```

- **`bind()`**: Binds the socket to a specific local address and port.

  **Parameters**:
  - **`sockfd`**: The socket file descriptor created by the `socket()` function.
  - **`(struct sockaddr *)&server`**: A pointer to the server's address structure, which holds the IP and port the server should listen on.
  - **`sizeof(server)`**: The size of the `server` structure, which tells `bind()` how much memory to use.

**Return value**:
- **`bindfd`**: If the `bind()` function succeeds, it returns `0`. If it fails, it returns `-1`.

---

### 9. Error Handling for Bind

```c
if (bindfd == -1) {
    perror("bind failed: ");
    close(sockfd);
    exit(EXIT_FAILURE);
}
```

- **`if (bindfd == -1)`**: Checks if the `bind()` call failed. If it returns `-1`, it indicates an error.
- **`perror("bind failed: ")`**: Prints the error message corresponding to the failure of the `bind()` call.
- **`close(sockfd)`**: Closes the socket if binding fails.
- **`exit(EXIT_FAILURE)`**: Terminates the program with a failure exit code.

---

### 10. Server Listening for Connections

```c
printf("server listening on IP: %s && PORT: %d\n", IP, PORT);
int backlog = 5;
listen(sockfd, backlog);
```

- **`printf()`**: Prints a message to the console indicating that the server is listening for incoming connections on the specified IP and port.
- **`int backlog = 5;`**: Sets the **backlog** for the **listen queue**, which is the maximum number of connections that can be waiting to be accepted. Here, the backlog is set to 5.
- **`listen()`**: Puts the socket in listening mode, so it can accept incoming connection requests.

  **Parameters**:
  - **`sockfd`**: The socket file descriptor.
  - **`backlog`**: The maximum number of pending connections that can be queued up before they are accepted.

---

### 11. Main Server Loop to Accept Connections

```c
while (1) {
    socklen_t addr_len = sizeof(client);
    int confd = accept(sockfd, (struct sockaddr *)&client, &addr_len);
    if (confd < 0) {
        perror("connection accept failed: ");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
```

- **`while (1)`**: Starts an infinite loop that continuously accepts new incoming connections.
- **`socklen_t addr_len = sizeof(client);`**: Defines the length of the client's address structure, which is passed to the `accept()` function.
- **`accept()`**: Accepts an incoming connection request from a client.

  **Parameters**:
  - **`sockfd`**: The server's listening socket descriptor.
  - **`(struct sockaddr *)&client`**: A pointer to a structure where the client's address will be stored. The client’s IP and port are populated here.
  - **`&addr_len`**: A pointer to the length of the `client` address structure.

**Return value**:
- **`confd`**: The accepted connection's file descriptor, which will be used to communicate with the client. If `accept()` fails, it returns `-1`.

---

### 12. Print Client Information

```c
inet_ntop(AF_INET, &client.sin_addr, clientIPBuffer, sizeof(clientIPBuffer));
printf("client connected from IP: %s && PORT %d ...\n", clientIPBuffer, ntohs(client.sin_port));


```

- **`inet_ntop()`**: Converts the client's IP address from binary format (stored in `client.sin_addr`) to a human-readable string. This function is the reverse of `inet_addr()`.

  **Parameters**:
  - **`AF_INET`**: Specifies that we are dealing with an **IPv4** address.
  - **`&client.sin_addr`**: A pointer to the client's IP address.
  - **`clientIPBuffer`**: The buffer where the client's IP address will be stored as a string.
  - **`sizeof(clientIPBuffer)`**: The size of the `clientIPBuffer` to ensure that the string is not overwritten.

- **`ntohs(client.sin_port)`**: Converts the client's port from **network byte order** to **host byte order** so it can be printed correctly.

---

### 13. Fork a Child Process to Handle the Client

```c
pid_t pid = fork();
```

- **`fork()`**: Creates a new child process that will handle the client communication. It returns:
  - **`0`** in the child process.
  - A positive value (the PID of the child) in the parent process.

---

### 14. Client Handling in the Child Process

```c
if (pid == 0) {
    close(sockfd);
    read(confd, readBuffer, sizeof(readBuffer));
    printf("client message: %s\n", readBuffer);
    write(confd, writeBuffer, sizeof(writeBuffer));
    printf("server respond: %s\n", writeBuffer);
    close(confd);
    exit(EXIT_SUCCESS);
}
```

- **`pid == 0`**: This block will be executed by the **child process**.
- **`close(sockfd)`**: The child process no longer needs the server’s listening socket, so it's closed.
- **`read(confd, readBuffer, sizeof(readBuffer))`**: Reads data sent by the client. The message is stored in `readBuffer`.
- **`write(confd, writeBuffer, sizeof(writeBuffer))`**: Sends the server's response (`writeBuffer`) back to the client.
- **`close(confd)`**: Closes the connection with the client after communication ends.
- **`exit(EXIT_SUCCESS)`**: Terminates the child process gracefully after handling the client.

---

### 15. Parent Process Continues Accepting New Connections

```c
close(confd);
```

- **`close(confd)`**: The parent process closes the client connection descriptor (`confd`) after forking the child. The parent will continue to listen for new connections.

---

### 16. Close the Server Socket

```c
close(sockfd);
```

- **`close(sockfd)`**: Closes the server's listening socket after exiting the loop, cleaning up the resources.

---

### Summary of Functions Used:

- **`socket()`**: Creates a socket for communication.
- **`bind()`**: Binds the server socket to a specific IP address and port.
- **`listen()`**: Makes the socket listen for incoming connections.
- **`accept()`**: Accepts a new incoming connection.
- **`inet_ntop()`**: Converts binary IP addresses to human-readable format.
- **`fork()`**: Creates a child process.
- **`read()`**: Reads data from a socket.
- **`write()`**: Sends data to a socket.
- **`close()`**: Closes a socket or file descriptor.
- **`exit()`**: Terminates the program.

