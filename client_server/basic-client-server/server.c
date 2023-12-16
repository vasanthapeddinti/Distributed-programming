// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
int main(int argc, char const* argv[])
{
    int server_fd, client_fd, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = { 0 };
	char* hello = "Hello from server";

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	printf("socket created %d\n", server_fd);

	// Setting socket options
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address)) < 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	printf("bind successful\n");
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	printf("Somebody connected \n");
	if ((client_fd
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	printf("Somebody connected at fd %d\n",client_fd);
	// valread is how many bytes we got from network
	// if 0 bytes, retry to get data
	// // if less than or equal to 1024, we might have some more data
	valread = read(client_fd, buffer, 1024);
	printf("%s\n", buffer);
	send(client_fd, hello, strlen(hello), 0);
	printf("Hello message sent\n");

	// closing the connected socket
	 close(client_fd);
	// closing the listening socket
	 shutdown(server_fd, SHUT_RDWR);
	 printf("closing and shutting down the connection");
	return 0;
}

