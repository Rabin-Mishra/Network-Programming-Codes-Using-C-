#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <sys/types.h>
#define PATH "/online/mxpfo/trace/sarod/un.txt"

int main()
{
    // socket creation
    int fd;
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1)
    {
        printf("Error creating socket %d\n", fd);
        exit(-1);
    }
    // struct initialization
    struct sockaddr_un server, client;
    memset(&server, 0, sizeof(struct sockaddr_un));
    server.sun_family = AF_UNIX;
    strncpy(server.sun_path, PATH, sizeof(server.sun_path) - 1);
    unlink(PATH);

    // binding the socket
    if (bind(fd, (struct sockaddr *)&server, sizeof(struct sockaddr_un)) == 0)
    {
        printf("Bind Succesfull with File Path[%s] and socket[%d]\n", PATH, fd);
    }
    // listening the socket
    int ls = listen(fd, 5);
    printf("Listen return value[%d]\n", ls);
    if (ls == -1)
    {
        printf("Error on Listening\n");
        exit(-1);
    }
    else
        printf("System is Listening on SOCKET[%s]\n", PATH);

    // accepting the connections
    size_t len = sizeof(client);
    int confd = accept(fd, (struct sockaddr *)&client, &len);
    printf("Connected Socked Descriptor[%d]\n", confd);

    // communication
    char recvBuff[128];
    char sendBuff[128] = "Hello this is UNIX Server";
    ssize_t r = recv(confd, recvBuff, sizeof(recvBuff), 0);
    printf("Message received UNIX-Client[%s]msglen[%]\n", recvBuff, r);
    ssize_t s = send(confd, sendBuff, 100, 0);
    printf("Message send to  UNIX-Client[%s]msg len[%d]\n", sendBuff, s);

    // cleanup
    close(confd);
    close(fd);
    unlink(PATH);
    return 0;
}
