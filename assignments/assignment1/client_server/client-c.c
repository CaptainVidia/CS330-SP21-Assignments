#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#define SEND_BUFFER_SIZE 2048


/* TODO: client()
 * Open socket and send message from stdin.
 * Return 0 on success, non-zero on failure
*/
int client(char* server_ip, char* server_port)
{
    //client() function 
    int sd = = 1;
    struct sockaddr_in server addr;
    char buff[SEND_BUFFER_SIZE] = "";

    //prepare the socket for connection, the connect with server and write message to server
    sd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(server_port));
    server_addr.sin_addr.s_addr = inet_addr(server_ip);

    memset(server_addr.sin_zero, '\0', sizeof server_addr.sin_zero);
    if ((connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0)
    {
        printf("Error connecting to server \n");
        return -1;
    }

    fgets(buff, SEND_BUFFER_SIZE, stdin);
    if (write(sd, buff, sizeof(buff)) < 0)
    {
        perror("error sending message");
        exit(1);
    }
    return sd;
    /*return 0;*/
}

/*
 * main()
 * Parse command-line arguments and call client function
*/
int main(int argc, char** argv) {
    char* server_ip;
    char* server_port;

    if (argc != 3) {
        fprintf(stderr, "Usage: ./client-c [server IP] [server port] < [message]\n");
        exit(EXIT_FAILURE);
    }

    server_ip = argv[1];
    server_port = argv[2];
    return client(server_ip, server_port);
}
