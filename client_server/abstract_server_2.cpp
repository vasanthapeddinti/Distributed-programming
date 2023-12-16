// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

typedef struct{
    int server_fd;
    struct sockaddr_in address;
} server_ctx;

class Server {
	public:
		int server_init(int port, server_ctx &ctx);
		void process_read(int client_fd, char *buffer, uint *len);
};

int Server::server_init (int port, server_ctx *ctx){
    int opt = 1;
    int ret_val = -1;

    // Creating socket file descriptor
    if ((ctx->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        goto out;
    }
    printf("socket created %d\n", ctx->server_fd);

    // Setting socket options
    if (setsockopt(ctx->server_fd, SOL_SOCKET,
                SO_REUSEADDR | SO_REUSEPORT, &opt,
                sizeof(opt))) {
        perror("setsockopt");
        goto out;
    }
    (ctx->address).sin_family = AF_INET;
    (ctx->address).sin_addr.s_addr = INADDR_ANY;
    (ctx->address).sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(ctx->server_fd, (struct sockaddr*)&(ctx->address),
            sizeof(ctx->address)) < 0) {
        perror("bind failed");
        goto out;
    }
    printf("bind successful\n");
    if (listen(ctx->server_fd, 3) < 0) {
        perror("listen");
        goto out;
    }
    ret_val = 0;
out:
    return ret_val;
}

void Server::process_read(int client_fd, char *buffer, uint *len) {

    printf("Somebody connected at fd %d\n",client_fd);
    // valread is how many bytes we got from network
    // if 0 bytes, retry tto get data
    // // if less than or equal to 1024, we might have some more data
    *len = read(client_fd, buffer, *len);
    printf("recieved no of bytes: %d", *len);
    printf("%*.s\n", *len, buffer);
}

int main(int argc, char const* argv[])
{
    char buffer[1024];
    int client_fd;
    char* hello = "Hello from server";
    uint len = 1024;
    server_ctx ctx;

	Server myServer;
    int res = myServer.server_init(PORT, ctx);
    if (res == -1) {
        exit(EXIT_FAILURE);
    }
    int addrlen = sizeof(ctx.address);

    while (1){
        printf("Somebody connected \n");
        if ((client_fd
            = accept(ctx.server_fd, (struct sockaddr*)&(ctx.address),
                    (socklen_t*)&addrlen))
            < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        myServer.process_read(client_fd, buffer, &len);
        send(client_fd, hello, strlen(hello), 0);
        printf("Hello message sent\n");
    }

	// closing the connected socket
	 close(client_fd);
	// closing the listening socket
	 shutdown(ctx.server_fd, SHUT_RDWR);
	 printf("closing and shutting down the connection");
	return 0;
}

