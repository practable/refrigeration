#!/usr/bin/env python3

'''
acWebsocketClient

- websocket client that connects to remotelabs sessionhost server to handle all incoming
 and outgoing JSON command & data acquisition messages


'''

#https://realpython.com/python-sockets/

import sys
import socket
import time
import selectors
import types
import acGlobals as glbs



parse = glbs.jsonParse
pack = glbs.jsonPack


host = glbs.server_ip
port = glbs.server_port

json_delay = 1   ## time between json messages to server
connection_error = 0


sel = selectors.DefaultSelector()
messages = [b"message one",b"message 2"]



'''
s.sendall(json_message.encode("UTF-8"))
init_time = time.time()
data = s.recv(1024)
message = int(data.decode())
# print(f" Response: {message}")
if message == 0:
    continue
    print("reportingClient: Success sending JSON data Message")
else:
    print("reportingClient: JSON Message failed to send")
    glbs.logging.error(f"reportingClient: JSON Message failed to send")
'''


class acWebsocketClient:
    def __init__(self):
        print("\n\nStarting AC Unit Refrigeration Rig - Websocket Client")
        self.conn_error = 0
        self.os_error = 0
        self.json_delay = 1
        self.host = host
        self.port = port
        self.report_que = []
        self.cmd_que = []
        self.last_rpt_time = time.time()




    def start_connections(self, num_conns = 1):
        server_addr = (self.host, self.port)
        for i in range(0, num_conns):
            connid = i + 1
            print(f"Starting connection {connid} to {server_addr}")
            while(1):
                try:
                    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    sock.setblocking(False)
                    try:
                        print("Trying to Connect")
                        sock.connect_ex(server_addr)
                        print(sock)
                    except ConnectionError:
                        print("startConnections connection exception")
                        self.os_error = glbs.known_exception_handler("ConnectionError", "acWSclient", self.os_error)
                    self.conn_error = 0
                    self.os_error = 0
                    break
                except OSError:
                    print("startConnections OS error")
                    self.os_error = glbs.known_exception_handler("OSError", "acWSclient", self.os_error)
            events = selectors.EVENT_READ | selectors.EVENT_WRITE
            data = types.SimpleNamespace(
                connid=connid,
                msg_total=sum(len(m) for m in messages),
                recv_total=0,
                messages=messages.copy(),
                outb=b"",
            )
            #print("data")
            #print(data)
            sel.register(sock, events, data=data)

    def service_connection(self, key, mask):
        sock = key.fileobj
        data = key.data
        if mask & selectors.EVENT_READ:
            recv_data = sock.recv(1024)  # Should be ready to read
            if recv_data:
                print(f"Received {recv_data!r} from connection {data.connid}")
                data.recv_total += len(recv_data)
            if not recv_data or data.recv_total == data.msg_total:
                print(f"Closing connection {data.connid}")
                sel.unregister(sock)
                sock.close()
        if mask & selectors.EVENT_WRITE:
            if not data.outb and data.messages:
                data.outb = data.messages.pop(0)
            if data.outb:
                print(f"Sending {data.outb!r} to connection {data.connid}")
                sent = sock.send(data.outb)  # Should be ready to write
                data.outb = data.outb[sent:]

    def prepare_json_report(self):
        json_message = pack.dump_json()
        json_message = json_message.encode("UTF-8")
        return json_message

    def load_report(self):
        if (time.time() - self.last_rpt_time >= 1):
            #print(time.time())
            self.report_que.append(self.prepare_json_report())
            print(f"Report Que Length {len(self.report_que)}")



    def run_client(self):
        print("client_running")




wsc = acWebsocketClient()
num_conns = 1

#if len(sys.argv) != 4:
#    print(f"Usage: {sys.argv[0]} <host> <port> <num_connections>")
#    sys.exit(1)
#host, port, num_conns = sys.argv[1:4]
try:
    while (1):
        wsc.start_connections(int(num_conns))
        print("connection started?")
        try:
            while True:
                wsc.load_report()
                events = sel.select(timeout=1)
                print("events")
                print(events)
                if events:
                    for key, mask in events:
                        wsc.service_connection(key, mask)
            # Check for a socket being monitored to continue.
                if not sel.get_map():
                    break
        except KeyboardInterrupt:
            print("Caught keyboard interrupt, exiting")
        except OSError:
            print("OSerror")
            glbs.update_error_status(23, "acWebClient: OSError Caught" )
            time.sleep(10)
        finally:
            sel.close()
except Exception as ex:
    print("generic exception")
    glbs.generic_exception_handler(ex, "acWebClient")
    time.sleep(10)










def commandClient():
    global connection_error
    try:
        while (1):
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                try:
                    s.connect((host, port))
                    print(f"Connected to {s}")
                    glbs.logging.info(f"websocketClient: Connected to Server: {s}")
                    connection_error = 0
                    init_time = time.time()
                    while(1):
                        #if time.time() - init_time >= json_delay:
                            #print("Sending JSON reply")
                            #json_message = pack.dump_json()
                            #s.sendall(json_message.encode("UTF-8"))
                            #init_time = time.time()
                        data = s.recv(1024)
                        #print(f"Received {data!r}")
                        error = parse.parse_json(data)
                        if not error:
                            #print("JSON Message Parsed - Queue Updated")
                            glbs.logging.info(f"websocketClient: JSON Message Parsed: {data}")
                            #glbs.command_received = True  ## this is done during the parsing
                            success_code = "0"
                            s.sendall(success_code.encode("UTF-8"))
                        else:
                            print(f"JSON Parsing Error, code: {error}")
                            glbs.logging.error(f"websocketClient: JSON Parsing Error, code: {error}")
                            error = str(error)
                            s.sendall(error.encode("UTF-8"))  ## error must always be int here?
                except ConnectionError:
                    print(f"Caught Connection Error, number since last connect: {connection_error}")
                    if connection_error < 1:  ## prevent this being written to log over and over
                        print("logging exception as first instance")
                        glbs.logging.exception(f"commandClient: Caught Connection Error, restarting")
                    connection_error += 1
    except KeyboardInterrupt:
        print("commandClient: Caught keyboard interrupt, exiting")
    except Exception as ex:
        glbs.generic_exception_handler(ex, "commandClient")
        raise

        #time.sleep(5)


#if __name__ == '__main__':
# commandClient()