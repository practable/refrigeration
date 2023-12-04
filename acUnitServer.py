#

#https://realpython.com/python-sockets/
#https://websockets.readthedocs.io/en/stable/intro/tutorial1.html
#https://stackoverflow.com/questions/62528272/what-does-asyncio-create-task-do

import socket
import time
import acGlobals as glbs
import json

import asyncio
import websockets

parse = glbs.jsonParse
pack = glbs.jsonPack


#HOST = "127.0.0.1"  # The server's hostname or IP address
HOST = glbs.server_ip
#TESTHOST = "10.42.0.1"
#HOST = TESTHOST
PORT = glbs.server_port # The port used by the server

json_delay = 1   ## time between json messages to server
connection_error = 0

cmd_list = []

async def handler(websocket):
    while True:
        if cmd_list > 0:
            for command in cmd_list:
                await websocket.send(command)
        message = await websocket.recv(2048)
        print(message)
        ## Add message to receive queue

## This isnt needed now handled by handler
async def send_usr_cmd(websocket):
    json_command = await input_cmd()
    if (json_command[1] == True):
        websocket.send(json_command[0])
        data = await websocket.recv(2048)
        print(data)


async def main():
    while(1):
        async with websockets.serve(handler, HOST , 8001) as websocket:
        #async with websockets.WebSocketServerProtocol(handler, "ws://127.0.0.1:8001") as websocket:
            print(f"Starting Websocket Server: {HOST} 8001")
            await asyncio.Future()  # run forever




async def input_cmd():
    stop = False
    json_valid = True
    json_input = b""
    try:
        json_input = await input(f"\nPlease Enter JSON command in format: {glbs.example_cmd}\n\n")
        try:
            json_obj = json.loads(json_input)
        except ValueError:
            print("JSON format Not Recognised")
            json_valid = False
    except KeyboardInterrupt:
        print("User Input Escaped - Closing Server")
        stop = True
    # print(iteration)
    print(f"JSON Valid? {json_valid}")
    if stop == False and json_valid == True:
        json_command = json_input.encode("UTF-8")
        cmd_list.append(json_command)
    else:
        json_command = b''
    return json_command, json_valid



if __name__ == '__main__':
    asyncio.run(input_cmd())
    asyncio.run(main())


    #commandClient()

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

