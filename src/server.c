#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	char connection_message[256] = "The server greets you!\n";
	
	// socket creation
	int sock_fd;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to your specified IP and port
	bind(sock_fd, (struct sockaddr*) &server_address, sizeof(server_address));

	// start listening
	listen(sock_fd, 1);

	int client_socket;
	client_socket = accept(sock_fd, NULL, NULL);

	if (client_socket == -1) {
		printf("[x] Failed to accept connection!\n");
		return -1;
	}


	send(client_socket, connection_message, sizeof(connection_message), 0);
	close(sock_fd);

	return 0;
}
