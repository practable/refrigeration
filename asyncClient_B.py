'''

Testing Asyncio
'''


'''
Make an Async program with 4 tasks. 
3 - run independently on timed loops.
1 - is a handler called by one of the timed loops

can it be done? (Yes!)
'''
#https://realpython.com/async-io-python/#where-does-async-io-fit-in
#https://docs.python.org/3/library/asyncio-eventloop.html#asyncio.ProactorEventLoop
#https://docs.python.org/3/library/asyncio-subprocess.html

import asyncio
import time
from datetime import datetime
import prettyCLI as pcli
import acGlobals as glbs

df = pcli.pcli["default"]
yl = pcli.pcli["fg"]["yellow"]
cy = pcli.pcli["fg"]["cyan"]
mg = pcli.pcli["fg"]["magenta"]

TASK_ONE_DELAY = 5
TASK_TWO_DELAY = 2
TASK_THREE_DELAY = 15

timestamp = glbs.timestamp  #importing a function
timediff = glbs.timediff


import socket

host = glbs.server_ip
port = glbs.server_port
parse = glbs.jsonParse

import websockets

#from here DIDNT WORK
#https://www.pythonfixing.com/2021/11/fixed-non-blocking-websocket-receive.html
async def readWS(queue):
    while True:
        async with websockets.connect("ws://127.0.0.1:8181", close_timeout=0.1) as ws:
            try:
                data = await ws.recv()
                await queue.put(('websocket', data))
            except websockets.error:
                return None

class ClientProtocol:
    def __init__(self, queue):
        self.queue = queue

    def datagram_received(self, data, addr):
        self.queue.put_nowait(('udp', data))

    def connection_lost(self, exc):
        self.queue.put_nowait(('udp', b''))

async def sendWS(queue):
    while(1):
    #transport, protocol = await loop.create_datagram_endpoint(
    #    lambda: ClientProtocol(queue),
    #    remote_addr=(PCC_IP, PCC_PORT))
    # wait until canceled
        print("hellpop")
        try:
            await asyncio.get_event_loop().create_future()
        except asyncio.CancelledError:
            print("Cancelled")
            raise

async def read_both():
    queue = asyncio.Queue()
    # spawn two workers in parallel, and have them send
    # data to our queue
    ws_task = asyncio.create_task(readWS(queue))
    udp_task = asyncio.create_task(sendWS(queue))

    while True:
        source, data = await queue.get()
        if source == 'ws':
            print('from websocket', data)
        elif source == 'udp':
            if data == b'':
                break  # lost the UDP connection
            print('from UDP', data)

    # terminate the workers
    ws_task.cancel()
    udp_task.cancel()


if __name__ == "__main__":
    asyncio.get_event_loop().run_until_complete(read_both())






class asyncClient:
    def __init__(self):
        self.start_time = time.time()
        print(f"asyncClient Started at: {datetime.now()}")
        self.cmd_queue = []
        self.conn_errors = 0
        self.conn_start_time = 0

    def open_socket(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.s.connect((host, port))
            self.s.setblocking(False)     ## this line DOEs stop it blocking but it also Stops it working
            print(f"Connected to {self.s}")
            glbs.logging.info(f"websocketClient: Connected to Server: {self.s}")
            self.conn_errors = 0
            self.conn_start_time = time.time()
            return 0
        except ConnectionError:
            print(f"Caught Connection Error, number since last connect: {self.conn_errors}")
            if self.conn_errors < 1:  ## prevent this being written to log over and over
                print("logging exception as first instance")
                glbs.logging.exception(f"commandClient: Caught Connection Error no.{self.conn_errors}, restarting")
            self.conn_errors += 1
            time.sleep(1)
            return 1



    async def listener(self):
        while(True):
            print(f"Listening on {self.s}")
            data =  await self.receiver()
            print(f"Received {data!r}")
            error = parse.parse_json(data)
            if not error:
                # print("JSON Message Parsed - Queue Updated")
                glbs.logging.info(f"websocketClient: JSON Message Parsed: {data}")
                # glbs.command_received = True  ## this is done during the parsing
                success_code = "0"
                self.s.sendall(success_code.encode("UTF-8"))
            else:
                print(f"JSON Parsing Error, code: {error}")
                glbs.logging.error(f"websocketClient: JSON Parsing Error, code: {error}")
                error = str(error)
                self.s.sendall(error.encode("UTF-8"))  ## error must always be int here?
            await asyncio.sleep(1)

    async def receiver(self):
        data = self.s.recv(1024)
        return data

    async def reporter(self):
        while(True):
            print("Its Little Alex Horne")
            await asyncio.sleep(5)



    def main(self):
        try:
            disconnected = True
            while(disconnected):
                disconnected = self.open_socket()
            print("Exited Start Connection Loop")
            loop = asyncio.new_event_loop()
            loop.create_task(self.listener())
            loop.create_task(self.reporter())
            #loop.create_task(self.taskThree())
            loop.run_forever()
        except KeyboardInterrupt:
            print("commandClient: Caught keyboard interrupt, exiting")
        except Exception as ex:
            glbs.generic_exception_handler(ex, "commandClient")
            raise




#prog = asyncClient()
#prog.main()






