#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define PORT 9999
#define IP "10.0.2.15"

int main() {
    int fd, confd;
    char sendBuff[1024];
    struct sockaddr_in server, client;
    socklen_t clientLen = sizeof(client);

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_port = htons(PORT);

    if (bind(fd, (struct sockaddr *)&server, sizeof(server)) < 0 || listen(fd, 5) < 0) {
        perror("Bind/Listen failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s:%d\n", IP, PORT);

    if ((confd = accept(fd, (struct sockaddr *)&client, &clientLen)) < 0) {
        perror("Accept failed");
        close(fd);
        exit(EXIT_FAILURE);
    }

    time_t ticks = time(NULL);
    snprintf(sendBuff, sizeof(sendBuff), "Current time: %.24s\r\n", ctime(&ticks));
    write(confd, sendBuff, strlen(sendBuff));

    close(confd);
    close(fd);
    return 0;
}
