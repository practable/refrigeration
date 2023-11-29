#

#https://realpython.com/python-sockets/


import socket
import time
import acUnitGlobals as glbs

parse = glbs.jsonParse
pack = glbs.jsonPack


#HOST = "127.0.0.1"  # The server's hostname or IP address
HOST = glbs.COMMAND_SERVER_IP
#TESTHOST = "10.42.0.1"
#HOST = TESTHOST
PORT = glbs.COMMAND_PORT  # The port used by the server

json_delay = 1   ## time between json messages to server
connection_error = 0

def commandClient():
    global connection_error
    try:
        while (1):
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                try:
                    s.connect((HOST, PORT))
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


if __name__ == '__main__':
    commandClient()