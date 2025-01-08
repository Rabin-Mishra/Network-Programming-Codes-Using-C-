

---

### Header Files

```c
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
```

These are **standard libraries** for socket programming and general utility functions:

1. **`<arpa/inet.h>`**:
   - Provides definitions for **Internet operations** like converting IP addresses and network-related operations (e.g., `inet_addr()`).
   
2. **`<netinet/in.h>`**:
   - Provides **Internet address structures**, specifically `struct sockaddr_in` for specifying IPv4 addresses (used by `bind()`, `connect()`, etc.).
   
3. **`<stdio.h>`**:
   - Standard input/output functions like `printf()`, `perror()`, `scanf()`, etc.
   
4. **`<stdlib.h>`**:
   - Includes functions like `exit()`, `malloc()`, `free()`, etc., and error handling utilities.

5. **`<sys/socket.h>`**:
   - Defines the socket interface, including the **`socket()`**, **`connect()`**, **`bind()`**, **`listen()`**, and **`accept()`** functions.
   
6. **`<unistd.h>`**:
   - Provides access to POSIX operating system API, including system calls like `close()`, `read()`, `write()`, etc.

---

### Preprocessor Directives

```c
#define IP "192.168.1.157"
#define PORT 9999
```

- **`#define`**: Used for **macro substitution**.
   - `IP` is defined as `"192.168.1.157"` (this is the **server's IP address**).
   - `PORT` is defined as `9999` (this is the **server's port number**).

These macros are later used to configure the socket connection.

---

### Main Function

```c
int main(int argc, char *argv[])
```

- **`int argc`**: The **argument count** passed from the command line. It represents the number of arguments passed to the program (including the program's name itself).
- **`char *argv[]`**: An **array of strings** containing the actual command-line arguments passed to the program.

In this case, neither `argc` nor `argv` is used, so they are just part of the program signature.

---

### Buffers for Reading and Writing Data

```c
char readBuffer[100];
char writeBuffer[] = "what's the current time";
```

- **`readBuffer[100]`**: A buffer to store up to **100 bytes** of data that the client receives from the server.
- **`writeBuffer[] = "what's the current time"`**: A buffer to store the message the client sends to the server. The message is `"what's the current time"`.

---

### Create a Socket

```c
int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
```

- **`socket()`**: This system call creates a socket and returns a **file descriptor** (`socket_fd`) that will be used to refer to this socket in future operations.
  
  **Parameters**:
  - **`AF_INET`**: Address family. Specifies **IPv4** (Internet Protocol version 4). This is used for IPv4 addresses (e.g., `192.168.1.157`).
  - **`SOCK_STREAM`**: The socket type. It indicates that this is a **stream socket**, which will use **TCP** (Transmission Control Protocol) to transmit data in a reliable, connection-oriented manner.
  - **`IPPROTO_TCP`**: Specifies the **protocol** used for communication (in this case, TCP). For `SOCK_STREAM`, this is typically implied, but it can be specified explicitly here.

**Return value**:
- The function returns an integer, `socket_fd`, which is a **file descriptor** used to refer to the created socket. If it fails, it returns `-1`.

---

### Configure Server Address

```c
struct sockaddr_in server;
server.sin_family = AF_INET;
server.sin_addr.s_addr = inet_addr(IP);
server.sin_port = htons(PORT);
```

- **`struct sockaddr_in server`**: This structure holds the **server's address information** that will be used to connect to the server.
  
  - **`sin_family = AF_INET`**: This specifies that the socket will use **IPv4** addresses.
  - **`sin_addr.s_addr = inet_addr(IP)`**: The function **`inet_addr()`** takes a string IP address (like `"192.168.1.157"`) and converts it into a **32-bit binary format** (network byte order) that the socket system can use.
  - **`sin_port = htons(PORT)`**: **`htons()`** stands for **Host to Network Short**. It converts the **port number** from the host's byte order to **network byte order** (big-endian). The port `9999` is passed here.

---

### Establish Connection with the Server

```c
int confd = connect(socket_fd, (struct sockaddr *)&server, sizeof(server));
```

- **`connect()`**: This function attempts to establish a connection to a remote server using the specified socket.
  
  **Parameters**:
  - **`socket_fd`**: The **socket descriptor** (file descriptor) that was created earlier with `socket()`.
  - **`(struct sockaddr *)&server`**: The address of the **server** to which we are connecting. It must be cast to the generic `struct sockaddr` type, which is a parent structure that encompasses `struct sockaddr_in`.
  - **`sizeof(server)`**: The size of the `server` structure. This specifies how many bytes of data are being passed for the connection.

**Return value**:
- If the connection is successful, the function returns `0`. If it fails, it returns `-1`.

---

### Handle Connection Failure

```c
if (confd == -1) {
    perror("connection failed: \n");
    exit(EXIT_FAILURE);
}
```

- **`if (confd == -1)`**: Checks if the connection failed (since `connect()` returns `-1` on failure).
  
- **`perror("connection failed: \n")`**: This function prints the **error message** associated with the most recent system call failure (in this case, the failed `connect()` call). The string `"connection failed: \n"` is printed before the error message.
  
- **`exit(EXIT_FAILURE)`**: If the connection fails, the program terminates using `exit()`. The `EXIT_FAILURE` macro indicates that the program ended due to a failure.

---

### Print Successful Connection Information

```c
printf("connection established with server IP: %s && PORT: %d ...\n", IP, PORT);
printf("client requesting to server: %s\n", writeBuffer);
```

- **`printf()`**: Prints to the standard output (console). These two lines print the successful connection details and the message the client is about to send to the server.

---

### Send Data to the Server

```c
write(socket_fd, writeBuffer, sizeof(writeBuffer));
```

- **`write()`**: This function writes data to the socket. The data is sent to the remote server.
  
  **Parameters**:
  - **`socket_fd`**: The socket file descriptor, which was obtained from the `socket()` call.
  - **`writeBuffer`**: The buffer containing the data to send (i.e., `"what's the current time"`).
  - **`sizeof(writeBuffer)`**: Specifies how many bytes to send. Since `writeBuffer` is a **string**, `sizeof(writeBuffer)` is the total size of the string (including the null-terminator).

**Return value**:
- The function returns the number of bytes successfully written. If an error occurs, it returns `-1`.

---

### Read Data from the Server

```c
int i = read(socket_fd, readBuffer, sizeof(readBuffer));
```

- **`read()`**: This function reads data from the socket into the specified buffer.
  
  **Parameters**:
  - **`socket_fd`**: The socket file descriptor (the socket that the client has connected to).
  - **`readBuffer`**: The buffer that will hold the data received from the server.
  - **`sizeof(readBuffer)`**: The maximum number of bytes the function should read from the socket. In this case, the buffer can hold up to 100 bytes.

**Return value**:
- The function returns the **number of bytes** successfully read. If the server closes the connection, `read()` may return `0`. If an error occurs, it returns `-1`.

---

### Print Server Response

```c
printf("%d byte recived from server && respons from server: %s\n", i, readBuffer);
```

- **`printf()`**: Prints the number of bytes received from the server (`i`) and the server's response (`readBuffer`).

---

### Close the Connection

```c
close(confd);
close(socket_fd);
```

- **`close()`**: This system call closes the specified file descriptor (in this case, the socket).
  
  - **`close(confd)`**: Closes the connection socket.
  - **`close(socket_fd)`**: Closes the original socket used to establish

 the connection.

**Purpose**:
- It ensures that all resources used by the socket are released properly, and the connection to the server is closed cleanly.

---

### Exit the Program

```c
return 0;
```

- **`return 0;`**: The `main()` function returns `0` to indicate that the program terminated successfully.

---

### Summary of Key Functions and Parameters:

- **`socket()`**: Creates a socket. Parameters: `AF_INET`, `SOCK_STREAM`, `IPPROTO_TCP`.
- **`inet_addr()`**: Converts an IP address from string to numeric format.
- **`htons()`**: Converts the port number to network byte order.
- **`connect()`**: Establishes a connection to a server. Parameters: socket file descriptor, server address, size of server address.
- **`write()`**: Sends data to the server. Parameters: socket file descriptor, data buffer, number of bytes.
- **`read()`**: Reads data from the socket. Parameters: socket file descriptor, buffer to store data, maximum bytes to read.
- **`close()`**: Closes the socket connection.

