import socket
import threading

def receive(sock):
    while True:
        try:
            msg = sock.recv(1024)
            print("\r" + msg.decode() + "\n> ", end="")
        except:
            break

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect(("127.0.0.1", 12345))
nick = input("Enter your nickname: ")
sock.send(nick.encode())

threading.Thread(target=receive, args=(sock,), daemon=True).start()

while True:
    msg = input("> ")
    message = nick + ": " + msg
    sock.send(message.encode())
