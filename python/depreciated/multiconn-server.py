#!/usr/bin/env python3

import sys
import socket
import selectors
import types
import acGlobals as glbs
import json

parse = glbs.jsonParse

sel = selectors.DefaultSelector()

host = "127.0.0.1"
port = 8181


class multiconnServer:
    def __init__(self):
        print("Starting Multi Connection Websocket Server")
        self.cmd_que = []



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
        if mask & selectors.EVENT_WRITE:
            if self.data.outb:
                print(f"Echoing {self.data.outb!r} to {self.data.addr}")
                sent = self.sock.send(self.data.outb)  # Should be ready to write
                self.data.outb = self.data.outb[sent:]


    def close_connection(self):
        print(f"Closing connection to {self.data.addr}")
        sel.unregister(self.sock)
        self.sock.close()

    def main(self):
        lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        lsock.bind((host, port))
        lsock.listen()
        print(f"Listening on {(host, port)}")
        lsock.setblocking(False)
        sel.register(lsock, selectors.EVENT_READ, data=None)
        try:
            while True:
                events = sel.select(timeout=None)
                for key, mask in events:
                    if key.data is None:
                        self.accept_wrapper(key.fileobj)
                    else:
                        self.service_connection(key, mask)
        except KeyboardInterrupt:
            print("Caught keyboard interrupt, exiting")
        finally:
            sel.close()



server = multiconnServer()
server.main()