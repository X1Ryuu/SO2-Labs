import msvcrt
import socket
import sys
import threading
import time
from datetime import datetime
clients = {}
lock = threading.Lock()

def handle_client(conn, addr):
    nick = conn.recv(1024).decode().strip()
    with lock:
        clients[conn] = nick
        print(f"[+] {nick} ({addr}) connected.")
    while True:
        try:
            msg = conn.recv(1024)
            curr = time.ctime()
            now = datetime.now()
            timestamp = now.strftime("%H:%M:%S.") + f"{now.microsecond // 1000:03d}"
            if not msg:
                break
            decoded_msg = msg.decode().strip()
            print(f"{timestamp} >>   {decoded_msg}")

            with lock:
                for client in clients:
                    if client != conn:
                        client.send(msg)
        except:
            break
    with lock:
        #clients.remove(conn)
        clients.pop(conn)
    conn.close()

def esc_listener():
    while True:
        if msvcrt.kbhit():
            key = msvcrt.getch()
            if key == b'\x1b':  # ESC
                print("\n[!] ESC pressed. Shutting down server.")
                server.close()
                sys.exit(0)


server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("0.0.0.0", 12345))
server.listen()
print("Server running...")
threading.Thread(target=esc_listener, daemon=True).start()

while True:
    try:
        conn, addr = server.accept()
        threading.Thread(target=handle_client, args=(conn, addr), daemon=True).start()
    except OSError:
        break  # Socket was closed by esc_listene
