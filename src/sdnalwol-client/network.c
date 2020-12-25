#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>




// the function creates the communcation socket, and connects it to the requested server.
// the connection's socket fd will be returned on success, -1 on failure.
// On later versions, ip address & port will be requested to compile the client.
int server_connect()
{ 
	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0); // creating the socket.

	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002); // htons converts the port number into network byte order -> port number should be changed.
	server_address.sin_addr.s_addr = INADDR_ANY; // address to connect to -> should be changed.

	int is_connected = connect(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address));

	if (is_connected != -1) // incase connect() was successfull, return the connected socket fd.
		return socket_fd;
	else
		return -1; // incase connect() failed.	
}




// the function reads data from the socket stream.
// the returned value is the number of bytes read from the socket, if reading failed -1 will be returned.
// the function updated the recv_data with the received data.
int receive_data(int socket_fd, char* recv_data)
{
	int bytes_read;
	bytes_read = recv(socket_fd, recv_data, sizeof(recv_data), 0);

	if (bytes_read != 0) {;
		return bytes_read;
	} else {
		return -1;	
	}
}




// the function sends data to the socket specified by the fd
int send_data(int socket_fd, char* data)
{
	int bytes_sent = send(socket_fd, data, sizeof(data), 0);

	if (bytes_sent == sizeof(data)) { // send() returns the number of bytes sent, therefore we can know that "data" was sent fully.
		printf("Sent: %s\n", data); // For debugging.
		return 0;
	} else {
		return -1;
	}
}




// the function is used to check the connection status by sending a message to the server and checking if the message was fully sent.
int check_connection(int socket_fd)
{
	char* ping = "ping";
	int connection_status = send(socket_fd, ping, sizeof(ping), 0);
	
	return connection_status;
}



// the function is used to reconnect to the server.
// the function will first try to reconnect, if the reconnection is failed, reconnection attemps will be held until
// the connection is restored, and of course the program will wait between each connection to prevent spam.
int reconnect()
{
	int is_connected = server_connect();

	while (1) { // Try to reconnect
		printf("Attempting to reconnect\n");
		is_connected = server_connect();

		if (is_connected != -1) {
			return is_connected;
		} 

		sleep(10);
	}
}
