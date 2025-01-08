
---

### 1. Header Files

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
```

These are **standard libraries** required for socket programming and other system-level operations:

- **`<stdio.h>`**: Provides input/output functions like `printf()`, `perror()`, etc.
- **`<stdlib.h>`**: Includes utility functions such as `exit()`, `malloc()`, `free()`, and other error handling functions.
- **`<unistd.h>`**: Provides access to POSIX system calls like `close()`, `read()`, and `write()`.
- **`<arpa/inet.h>`**: Provides functions for dealing with Internet addresses, such as converting IP addresses between text and binary format (`inet_addr()`).
- **`<sys/socket.h>`**: Defines the **socket** interface and various constants related to networking, including functions like `socket()`, `connect()`, and `write()`.
- **`<netinet/in.h>`**: Contains definitions related to Internet address structures, particularly `struct sockaddr_in` (used for IPv4 addresses).
- **`<sys/types.h>`**: Defines types used in system calls, such as `ssize_t` (for the return values of `read()` and `write()`).

---

### 2. Constants Definition

```c
#define IP "192.168.1.157"
#define PORT 9999
```

- **`#define IP "192.168.1.157"`**: This defines a constant for the **server's IP address** (`"192.168.1.157"`).
- **`#define PORT 9999`**: This defines the **port number** (`9999`) on which the server is expected to listen for connections.

These constants are used later to configure the server connection.

---

### 3. Main Function Definition

```c
int main(int argc, char *argv[])
```

- **`int argc`**: The **argument count** that holds the number of command-line arguments passed to the program.
- **`char *argv[]`**: An **array of strings** (or array of `char *`), which holds the actual command-line arguments passed to the program. Although not used in this program, it is a standard part of the `main()` function signature.

---

### 4. Buffers for Data

```c
char writeBuffer[100] = "Hello I am Client";
char readBuffer[100];
```

- **`writeBuffer[100]`**: A buffer that will hold the message the client sends to the server. It's initialized with the string `"Hello I am Client"`.
- **`readBuffer[100]`**: A buffer that will store the message received from the server. It's not initialized and will hold up to 100 bytes of data.

---

### 5. Create the Socket

```c
int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
```

- **`socket()`**: This function creates a **socket** that can be used to communicate over the network.

  **Parameters**:
  - **`AF_INET`**: This specifies the **address family**. `AF_INET` means the socket will use **IPv4** addresses.
  - **`SOCK_STREAM`**: This specifies the **socket type**. `SOCK_STREAM` is used for **TCP (Transmission Control Protocol)**, which is a connection-oriented protocol.
  - **`IPPROTO_TCP`**: This specifies the **protocol** used. In this case, TCP is used for reliable, ordered communication.

**Return value**:
- **`sockfd`**: The return value is a **socket file descriptor** (an integer). If the socket creation fails, it will return `-1`. The `sockfd` is used to refer to this socket for future network communication operations.
  
If `socket()` fails, the program exits with an error message.

---

### 6. Error Handling for Socket Creation

```c
if (sockfd < 0) {
    perror("socket creation failed: ");
    close(sockfd);
    exit(EXIT_FAILURE);
}
```

- **`if (sockfd < 0)`**: This condition checks if the `socket()` call failed (i.e., `sockfd` is less than `0`).
- **`perror("socket creation failed: ")`**: Prints an error message indicating that the socket creation failed. `perror()` automatically appends the error string related to the failure (from the `errno` global variable).
- **`close(sockfd)`**: Closes the socket if it was created, but the program fails before it could be used. Although, in this case, the socket creation failed, so this is more of a safeguard.
- **`exit(EXIT_FAILURE)`**: Terminates the program with a failure exit code (`EXIT_FAILURE` is a macro with a value of `1`).

---

### 7. Configure the Server Address

```c
struct sockaddr_in server;
server.sin_family = AF_INET;
server.sin_addr.s_addr = inet_addr(IP);
server.sin_port = htons(PORT);
```

- **`struct sockaddr_in server`**: This structure is used to store the **server's address** (IPv4) for the `connect()` function.
  
  - **`server.sin_family = AF_INET`**: This specifies that the address family is **IPv4**.
  - **`server.sin_addr.s_addr = inet_addr(IP)`**: The **`inet_addr()`** function converts the string representation of the IP address (e.g., `"192.168.1.157"`) into a **32-bit binary format** that can be used in network communications.
  - **`server.sin_port = htons(PORT)`**: The **`htons()`** function converts the **port number** to **network byte order** (big-endian), which is the format used for transmission over the network. `htons()` stands for **Host to Network Short**, and it ensures that the port number is represented correctly on all platforms.

---

### 8. Establish the Connection

```c
int confd = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
```

- **`connect()`**: This system call attempts to **establish a connection** between the client and the server.

  **Parameters**:
  - **`sockfd`**: The socket file descriptor, which was returned by the `socket()` system call.
  - **`(struct sockaddr *)&server`**: The server's address structure, which is cast to a generic `struct sockaddr *` type. The `connect()` function requires this generic type.
  - **`sizeof(server)`**: The size of the address structure `server`. This tells `connect()` how much memory it should use to read the address.

**Return value**:
- If the connection is successful, `connect()` returns `0`. If it fails, it returns `-1`, and the error message is printed.

---

### 9. Error Handling for Connection Failure

```c
if (confd == -1) {
    perror("connection establishment failed: ");
    close(sockfd);
    exit(EXIT_FAILURE);
}
```

- **`if (confd == -1)`**: This checks if the connection attempt failed (i.e., `confd` is `-1`).
- **`perror("connection establishment failed: ")`**: Prints an error message to **stderr**, indicating that the connection to the server failed.
- **`close(sockfd)`**: Closes the socket if the connection attempt failed.
- **`exit(EXIT_FAILURE)`**: Terminates the program with a failure code.

---

### 10. Print Client's Message

```c
printf("client message: %s\n", writeBuffer);
```

- **`printf()`**: This function prints the content of `writeBuffer` (i.e., `"Hello I am Client"`) to the console. It shows the message the client is sending to the server.

---

### 11. Send Data to the Server

```c
write(sockfd, writeBuffer, sizeof(writeBuffer));
```

- **`write()`**: This function writes data to the socket, sending it to the server.

  **Parameters**:
  - **`sockfd`**: The socket file descriptor used for communication.
  - **`writeBuffer`**: The buffer that contains the data to send (the message `"Hello I am Client"`).
  - **`sizeof(writeBuffer)`**: The size of the buffer, which is `100` (the allocated size, including the null-terminator). This sends the entire buffer, including any unused bytes (null padding).

**Note**: In this case, `sizeof(writeBuffer)` sends 100 bytes, which may not be ideal if you only want to send the actual message. Using `strlen(writeBuffer)` would be a more precise approach.

---

### 12. Read Data from the Server

```c
read(sockfd, readBuffer, sizeof(readBuffer));
```

- **`read()`**: This function reads data from the socket and stores it in the `readBuffer`.

  **Parameters**:
  - **`sockfd`**: The socket file descriptor used to receive the data.
  - **`readBuffer`**: The buffer where the received data will be stored.
  - **`sizeof(readBuffer)`**: The maximum number of

 bytes to read (in this case, 100 bytes).

**Return value**:
- The `read()` function returns the number of bytes read. It returns `0` if the server closes the connection, or `-1` if an error occurs.

---

### 13. Print Server's Response

```c
printf("server response: %s\n", readBuffer);
```

- **`printf()`**: This prints the content of `readBuffer` (the server's response) to the console. This lets the client see the message received from the server.

---

### 14. Close the Connection

```c
close(confd);
close(sockfd);
```

- **`close(confd)`**: Closes the socket connection. In this case, `confd` was returned by the `connect()` call, but it's not strictly necessary here because `sockfd` is used for communication. This line is a safeguard.
- **`close(sockfd)`**: This closes the socket after communication has finished.

**Important**: Closing the socket ensures that the resources (like memory and file descriptors) are released back to the operating system.

---

### 15. Return from the Main Function

```c
return 0;
```

- **`return 0;`**: This signifies successful completion of the program. Returning `0` from `main()` is the standard way to indicate that the program has run without errors.

---

### Summary of Key Functions and Parameters:

- **`socket()`**: Creates a socket. Parameters: `AF_INET`, `SOCK_STREAM`, `IPPROTO_TCP`.
- **`inet_addr()`**: Converts the string IP address (`IP`) into a network format.
- **`htons()`**: Converts the port number to network byte order.
- **`connect()`**: Establishes a connection to the server. Parameters: socket descriptor, server address structure, size of the address structure.
- **`write()`**: Sends data to the server. Parameters: socket descriptor, data buffer, number of bytes.
- **`read()`**: Reads data from the socket. Parameters: socket descriptor, buffer, maximum number of bytes to read.
- **`close()`**: Closes the socket connection.