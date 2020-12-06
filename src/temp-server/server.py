import socket

# A simple python server used for testing the client's functionality.


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 9002)
sock.bind(server_address)
sock.listen(5)
print("[>] Server is waiting for connection.\n")

client_socket, client_address = sock.accept()
print(f"Connection established!\n")
client_socket.send(bytes("hey", "utf-8")) #connection message

while True:

    command = input('>> ')    

    client_response = sock.recv(1024)
    print(client_response.decode("utf-8"))
