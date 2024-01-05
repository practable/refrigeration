#!/usr/bin/env python3


'''
sessionServer

- websocket server for testing acWebsocketClient

- Enables JSON messages to be received periodically as well as providing a command-line interface for sending JSON commands

#https://realpython.com/python-sockets/
'''

# multiconn-server.py

#import sys
import socket
import selectors
import types
import acGlobals as glbs

sel = selectors.DefaultSelector()

# ...

host = glbs.server_ip
port = glbs.server_port

class acWebsocketClient:
    def __init__(self):
        self.conn = []
        self.sock = 0
        self.data = 0


    def accept_wrapper(self, sock):
        conn, addr = sock.accept()  # Should be ready to read
        print(f"Accepted connection from {addr}")
        conn.setblocking(False)
        data = types.SimpleNamespace(addr=addr, inb=b"", outb=b"")
        events = selectors.EVENT_READ | selectors.EVENT_WRITE
        sel.register(conn, events, data=data)

    def service_connection(self, key, mask):
        self.sock = key.fileobj
        self.data = key.data
        if mask & selectors.EVENT_READ:
            recv_data = self.sock.recv(1024)  # Should be ready to read
            if recv_data:
                self.data.outb += recv_data
                #else:
        if mask & selectors.EVENT_WRITE:
            if self.data.outb:
                print(f"Echoing {self.data.outb!r} to {self.data.addr}")
                sent = self.sock.send(self.data.outb)  # Should be ready to write
                self.data.outb = self.data.outb[sent:]

    def close_connection(self):
        print(f"Closing connection to {self.data.addr}")
        sel.unregister(self.sock)
        self.sock.close()

wsc = acWebsocketClient

#host, port = sys.argv[1], int(sys.argv[2])
while(1):
    lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    lsock.bind((host, port))
    lsock.listen()
    print(f"Listening on {(host, port)}")
    lsock.setblocking(False)
    sel.register(lsock, selectors.EVENT_READ, data=None)
    try:
        while True:
            print("connection alive")
            events = sel.select(timeout=None)
            print(F"events: {events}")
            for key, mask in events:
                print(f"Key {key}, mask:{mask}")
                if key.data is None:
                    try:
                        wsc.accept_wrapper(key.fileobj)
                    except TypeError:
                        print("Type Error Occured")
                else:
                    wsc.service_connection(key, mask)
    except KeyboardInterrupt:
        print("Caught keyboard interrupt, exiting")
        wsc.close_connection()
    finally:
        sel.close()