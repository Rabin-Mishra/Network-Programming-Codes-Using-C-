
---
# Socket Programming in C (UNIX & Windows)

This repository contains C code implementations for **UNIX Socket Programming** and **Windows Socket Programming (Winsock)**. It also includes markdown files and PDF documentation that explain the flow, working, and functions used in the programs.

## Table of Contents

- [Overview](#overview)
- [Directory Structure](#directory-structure)
- [UNIX Socket Programming](#unix-socket-programming)
- [Windows Socket Programming (Winsock)](#windows-socket-programming-winsock)
- [How to Run](#how-to-run)
- [Documentation](#documentation)
- [License](#license)

## Overview

This repository aims to demonstrate the principles of **socket programming** in C. It covers both **UNIX-based systems** (using standard POSIX sockets) and **Windows-based systems** (using the Winsock API).

The project is divided into two sections:
- **UNIX Socket Programming**: Contains C code and documentation explaining socket communication using the standard Unix/Linux sockets interface.
- **Windows Socket Programming (Winsock)**: Contains C code for socket programming in Windows using the Winsock library, along with corresponding explanations.

Both implementations follow a client-server model and include socket creation, binding, connecting, reading/writing data, and handling errors.

## Directory Structure

```
/socket-programming-c
│
├── /unix-socket-programming
│   ├── client.c          # UNIX client code
│   ├── server.c          # UNIX server code
│   ├── README.md         # Markdown documentation for UNIX
│   └── unix-flow.pdf     # PDF document describing the UNIX flow and functions
│
├── /winsock-programming
│   ├── client.c          # Windows client code
│   ├── server.c          # Windows server code
│   ├── README.md         # Markdown documentation for Winsock
│   └── winsock-flow.pdf  # PDF document describing the Winsock flow and functions
│
├── README.md             # This file (overview of the project)
└── LICENSE               # License file
```

## UNIX Socket Programming

This section contains C programs that demonstrate **socket programming in UNIX-based systems**. The code is designed to be compiled and run on Linux/Unix systems using the POSIX socket API.

### Files:
- `client.c`: Implements a TCP client for UNIX socket communication.
- `server.c`: Implements a TCP server for UNIX socket communication.
- `README.md`: A markdown file explaining the flow, functions, and logic behind the UNIX socket programming.
- `unix-flow.pdf`: A PDF file describing the program flow and functions used for UNIX socket programming.

### Features:
- TCP/IP Client-Server communication using **sockets**.
- Functions like `socket()`, `bind()`, `listen()`, `accept()`, `read()`, `write()`, and `close()` are demonstrated.
- Basic error handling and connection management.

You can view the markdown file (`README.md`) for detailed explanations about the code and the flow.

---

## Windows Socket Programming (Winsock)

This section contains C programs demonstrating **socket programming on Windows systems** using the **Winsock API**. The code is designed to be compiled and run on Windows.

### Files:
- `client.c`: Implements a TCP client using Winsock for Windows socket communication.
- `server.c`: Implements a TCP server using Winsock for Windows socket communication.
- `README.md`: A markdown file explaining the flow, functions, and logic behind the Winsock socket programming.
- `winsock-flow.pdf`: A PDF document describing the program flow and functions used for Winsock programming.

### Features:
- TCP/IP Client-Server communication using **Winsock**.
- Functions like `socket()`, `bind()`, `listen()`, `accept()`, `recv()`, `send()`, and `closesocket()` are demonstrated.
- Includes error handling and connection management for Windows.

The markdown file (`README.md`) in this section contains a detailed explanation of the Winsock code and flow.

---

## How to Run

### UNIX Socket Programming
1. **Install GCC** (GNU Compiler Collection) if you don't have it already.
2. **Compile the code**:
   ```bash
   gcc -o unix-server server.c
   gcc -o unix-client client.c
   ```
3. **Run the server** (in one terminal):
   ```bash
   ./unix-server
   ```
4. **Run the client** (in another terminal):
   ```bash
   ./unix-client
   ```

### Windows Socket Programming (Winsock)
1. **Install a C Compiler** (e.g., MinGW or Microsoft Visual Studio).
2. **Link against Winsock** during compilation (e.g., use `-lws2_32` for MinGW).
3. **Compile the code**:
   ```bash
   gcc -o winsock-server server.c -lws2_32
   gcc -o winsock-client client.c -lws2_32
   ```
4. **Run the server** (in one Command Prompt window):
   ```bash
   winsock-server.exe
   ```
5. **Run the client** (in another Command Prompt window):
   ```bash
   winsock-client.exe
   ```

---

## Documentation

Each section (UNIX and Windows) contains a detailed markdown file (`README.md`) and a PDF (`unix-flow.pdf` / `winsock-flow.pdf`). These files describe:

- The program flow (from creating sockets to sending/receiving data).
- Functions used and their purpose.
- Error handling mechanisms.
- Basic troubleshooting steps.

You can check out the markdown and PDF documentation to better understand how the programs work and how to customize them for your own needs.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Feel free to open an **issue** or submit a **pull request** if you encounter any bugs or have suggestions for improvements!

---

### Notes:
1. **Code Compatibility**: The UNIX code uses POSIX sockets, which are typically available on Linux/Unix systems, while the Windows code uses the Winsock API. Ensure you're compiling and running the appropriate code for your platform.
2. **Documentation**: The provided PDFs contain a comprehensive explanation of the flow and functions used in both UNIX and Windows socket programming.

---
