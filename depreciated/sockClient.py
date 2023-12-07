'''
Testing Asyncio

#todo NEW SOURCE
#https://docs.python.org/3/howto/sockets.html
'''


'''

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

class asyncClient:
    def __init__(self):
        self.start_time = time.time()
        print(f"asyncClient Started at: {datetime.now()}")
        self.cmd_queue = []
        self.report_que = []
        self.conn_errors = 0
        self.conn_start_time = 0

    def open_socket(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.s.connect((host, port))
            #self.s.setblocking(False)     ## this line DOEs stop it blocking but it also Stops it working
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
            #self.report_que.append("Little Alex Horne")
            await asyncio.sleep(5)

    async def reader(self):
        while (self.report_que):
            print(self.report_que[0:1])
            del self.report_que[0:1]
            await asyncio.sleep(2)



    def main(self):
        try:
            disconnected = True
            while(disconnected):
                disconnected = self.open_socket()
            loop = asyncio.new_event_loop()
            loop.create_task(self.listener())
            loop.create_task(self.reporter())
            loop.create_task(self.reader())
            loop.run_forever()
        except KeyboardInterrupt:
            print("commandClient: Caught keyboard interrupt, exiting")
        except Exception as ex:
            glbs.generic_exception_handler(ex, "commandClient")
            raise




prog = asyncClient()
prog.main()






