#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main()
{

	char recv_data[256];

	// create a socket.
	int socket_fd, bytes_read, bytes_sent;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);

	// specify an address for the socket.
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002); // the function converts the port number to network byte order.
	server_address.sin_addr.s_addr = INADDR_ANY; // address to connect to.

	int is_connected = connect(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address));
	
	if (is_connected == -1) { // check if connection is successfull.
		printf("[x] Connection failed.\n");
		return -1;
	}

	printf("connect() return value: %d\n", is_connected);

	printf("[>] Connection successfull. \n\n");
	
	while (is_connected == 0) { // while connection is held.

		bytes_read = recv(socket_fd, recv_data, sizeof(recv_data), 0);
		printf("%d bytes of data: %s\n", bytes_read, recv_data);

		bytes_sent = send(socket_fd, recv_data, bytes_read, 0);
		
		if (bytes_sent != -1) {
			printf("%d bytes sent\n", bytes_sent);
		} else {
			printf("Failed to send data, connection lost\n");
		}

		memset(recv_data, '\0', 256); // reset the data buffer for the next message.
	}
	

	return 0;
}


