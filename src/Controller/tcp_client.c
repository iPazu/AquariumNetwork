#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char *argv[])
{

    char message[1000], server_reply[2000];

    int sock, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        perror("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Connect failed");
        return 1;
    }

    printf("Connected\n");

    // Send some data
    while (1)
    {
        // Receive a reply from the server
        if (recv(sock, server_reply, 2000, 0) < 0)
        {
            puts("Receive failed");
            break;
        }
        puts("Server reply:");
        puts(server_reply);

        printf("Enter message: ");
        fgets(message, sizeof(message), stdin);

        if (send(sock, message, strlen(message), 0) < 0)
        {
            puts("Send failed");
            return 1;
        }

        

        memset(message, 0, sizeof(message));
        memset(server_reply, 0, sizeof(server_reply));
    }

    close(sock);

    return 0;
}
