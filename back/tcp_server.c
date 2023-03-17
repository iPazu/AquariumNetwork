#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0) error("ERROR opening socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) error("ERROR on binding");
     printf("bind()\n");

//     printf("Breakpoint...\n");
//     getchar();
	 
     listen(sockfd,5);
     printf("listen()\n");
     clilen = sizeof(cli_addr);

     printf("en attente du accept()\n");
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     printf("accept()\n");
     if (newsockfd < 0) error("ERROR on accept");
     bzero(buffer,256);

//     printf("Breakpoint...\n");
//     getchar();

     printf("en attente du read()\n");
     n = read(newsockfd,buffer,255);
     printf("read() terminé\n");


     if (n < 0) error("ERROR reading from socket");

     printf("Here is the message: %s\n",buffer);
     n = write(newsockfd,"I got your message",18);
     printf("write()\n");

     if (n < 0) error("ERROR writing to socket");

//     printf("En attente de la fin du processus\n");
//     printf("Breakpoint...\n");
//     getchar();
     return 0; 
}
