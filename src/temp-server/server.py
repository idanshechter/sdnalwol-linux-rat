import socket

# A simple python server used for testing the client's functionality.


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 9002)
sock.bind(server_address)
sock.listen(5)
print("[>] Server is waiting for connection.\n")

client_socket, client_address = sock.accept()
print(f"Connection established!\n")

while True:

    command = input('>> ')

    try:
        client_socket.send(bytes(command, "utf-8"))
    except: 
        print(f"Failed to send message!\n")


