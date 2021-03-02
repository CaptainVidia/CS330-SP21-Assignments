/*****************************************************************************
 * server-c.c                                                                 
 * Name:
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048

/* TODO: server()
 * Open socket and wait for client to connect
 * Print received message to stdout
 * Return 0 on success, non-zero on failure
*/
int server(char *server_port) 
{
    //server() function
    int sd = -1;
    int sd_init = -1;
    int size = -1;
    socklen_t addr_size = 512;
    struct sockaddr_in server_addr;
    char recv_buff[RECV_BUFFER_SIZE] = "";
    sd_init = socket(AF_INET, SOCK_STREAM, 0);
    if (sd_init < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }
    //prepare socket for accepting connections, and read message from client
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(server_port));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sd_init,(const struct sockaddr *) &server_addr, sizeof(struct sockaddr)) < 0)
    {
        perror("Error binding port to socket\n");
        exit(1);
    }

    if (listen(sd_init,5) == 0)
    {
        printf("Listening on socket .... \n");
    }
    else
    {
        perror("Error listening on socket \n");
        exit(1);
    }

    sd = accept(sd_init, (const struct sockaddr*)&server_addr, &addr_size);

    if (sd<0)
    {
        perror("Error accepting connection");
        exit(1);
    }
    else
    {
        printf("recieved message: %s ", recv_buff);
        printf("\n");
    }
    return sd;
    /*return 0;*/
}

/*
 * main():
 * Parse command-line arguments and call server function
*/
int main(int argc, char **argv) {
  char *server_port;

  if (argc != 2) {
    fprintf(stderr, "Usage: ./server-c [server port]\n");
    exit(EXIT_FAILURE);
  }

  server_port = argv[1];
  return server(server_port);
}
