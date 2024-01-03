#!/usr/bin/env python3

import sys
import socket
import selectors
import types
import asyncio
import time

sel = selectors.DefaultSelector()
messages = [b"Message 1 from client.", b"Message 2 from client."]

host = "127.0.0.1"
port =  8181
num_conns = 1

#TODO ONE connection that is listening!!!

class multiconnClient:
    def __init__(self):
        print("Starting Multiconn Websocket Client")
        self.cmd_queue = []
        self.missed_connections = 0

    def start_connections(self, host, port, num_conns):
        server_addr = (host, port)
        for i in range(0, num_conns):
            connid = i + 1
            print(f"Starting connection {connid} to {server_addr}")
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.setblocking(False)
            disconnected = True
            while disconnected:
                try:
                    sock.connect_ex(server_addr)
                    if sock.getsockname()[0] == "0.0.0.0": # socket has not connected
                        print("Connection not etablished: Retrying")
                        time.sleep(5)
                    else:
                        disconnected = False
                except ConnectionError:
                    print("connection error")
                    time.sleep(5)
            events = selectors.EVENT_READ | selectors.EVENT_WRITE
            data = types.SimpleNamespace(
                connid=connid,
                msg_total=sum(len(m) for m in messages),
                recv_total=0,
                messages=messages.copy(),
                outb=b"",
            )
            sel.register(sock, events, data=data)


    def service_connection(self, key, mask):
        self.sock = key.fileobj
        self.data = key.data
        if mask & selectors.EVENT_READ:
            recv_data = self.sock.recv(1024)  # Should be ready to read
            if recv_data:
                print(f"Received {recv_data!r} from connection {self.data.connid}")
                self.data.recv_total += len(recv_data)
            if not recv_data or self.data.recv_total == self.data.msg_total:
                self.missed_connections += 1
                print(f"not recv data or data recv total. {self.missed_connections}")
                #if (self.missed_connections >= 10):
                sel.unregister(self.sock)
                self.sock.close()
                #self.close_connection()
        if mask & selectors.EVENT_WRITE:
            if not self.data.outb and self.data.messages:
                self.data.outb = self.data.messages.pop(0)
            if self.data.outb:
                print(f"Sending {self.data.outb!r} to connection {self.data.connid}")
                sent = self.sock.send(self.data.outb)  # Should be ready to write
                self.data.outb = self.data.outb[sent:]


    def close_connection(self):
        print(f"Closing connection {self.data.connid}")
        sel.unregister(self.sock)
        self.sock.close()

    def main(self):
        self.start_connections(host, int(port), int(num_conns))
        try:
            while True:
                events = sel.select(timeout=1)
                if events:
                    for key, mask in events:
                        self.service_connection(key, mask)
                # Check for a socket being monitored to continue.
                #if not sel.get_map():
        except KeyboardInterrupt:
            print("Caught keyboard interrupt, exiting")
        finally:
            sel.close()


client = multiconnClient()
client.main()
