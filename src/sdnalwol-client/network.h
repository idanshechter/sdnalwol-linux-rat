int server_connect();
int receive_data(int socket_fd, char* recv_data);
int send_data(int socket_fd, const char* data);
int check_connection(int socket_fd);
int reconnect();
