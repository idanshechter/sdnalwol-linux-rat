import socket
import time

# A simple python server used for testing the client's functionality.


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 9002)
sock.bind(server_address)
sock.listen(5)
print("[>] Server is waiting for connection.\n")

client_socket, client_address = sock.accept()
print(f"Connection from:", client_address, "\n")

while True:

    command = input('>> ')
    
    if command == "sysinfo": # The sending process will be wrapped in a func
        client_socket.send(bytes(command, "utf-8"))
        time.sleep(1)
        response = client_socket.recv(1024).decode('utf-8')
        print(response)

    elif command == "getshell":
        client_socket.send(bytes(command, "utf-8"))
        time.sleep(1)
        response = client_socket.recv(1024).decode('utf-8')
        print(response)
    else:
        print("Unknown command.\n")

    time.sleep(1)


sock.close()





