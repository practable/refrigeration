'''

Testing Asyncio
'''


'''
Make an Async program with 4 tasks. 
3 - run independently on timed loops.
1 - is a handler called by one of the timed loops

can it be done?
'''
#https://realpython.com/async-io-python/#where-does-async-io-fit-in
#https://docs.python.org/3/library/asyncio-eventloop.html#asyncio.ProactorEventLoop
#https://docs.python.org/3/library/asyncio-subprocess.html

import asyncio
import time
import prettyCLI as pcli

df = pcli.pcli["default"]
yl = pcli.pcli["fg"]["yellow"]
cy = pcli.pcli["fg"]["cyan"]
mg = pcli.pcli["fg"]["magenta"]

TASK_ONE_DELAY = 5
TASK_TWO_DELAY = 2
TASK_THREE_DELAY = 15

def timestamp(time_float):
    return df + str(round(time_float, 2))

def timediff(time_float, last_time):
    diff = round((time_float - last_time),2)
    if diff < 10:
        return df + "0" + str(diff)
    else:
        return df + str(diff)


class asyncTest:
    def __init__(self):
        self.start_time = time.time()
        self.start_time_one = self.start_time
        self.start_time_two = self.start_time
        self.start_time_three =  self.start_time
        self.task_delay_one = TASK_ONE_DELAY
        self.task_delay_two = TASK_TWO_DELAY
        self.task_delay_three = TASK_THREE_DELAY
        self.start_time_prod = self.start_time
        self.task_four_var = 1
        self.c = ( # ANSI colors
            "\033[0m",   # End of color
            "\033[36m",  # Cyan
            "\033[93m",  # Yellow  30 black 31 red 37 grey
            "\033[35m",  # Magenta)
        )
        #time.sleep(4)
        self.cmd_queue = []
        #self.task_four = asyncio.create_task(self.taskFour(self.task_four_var))


    async def taskOne(self):
        now = time.time()
        if (now - self.start_time_one > self.task_delay_one):
            print(timediff(now,self.start_time_one) + yl + ": Do task one")
            self.start_time_one = now
        else:
            await asyncio.sleep(1)

    async def taskTwo(self):
        now = time.time()
        if ( now - self.start_time_two > self.task_delay_two):
            print(timediff(now,self.start_time_two) + cy +": Do task Two")
            self.start_time_two = now
        else:
            await asyncio.sleep(1)

    async def taskThree(self, i=0):
        now = time.time()
        if (now - self.start_time_three > self.task_delay_three):
            print(timediff(now,self.start_time_three) + mg + ": Do task three")
            self.start_time_three = now
            returnVal = await self.taskFour(self.task_four_var)
            print(timediff(time.time(),now) + f": Task 4 has been returned with variable: {returnVal}")
            self.task_four_var = returnVal   # For another test make this a returned value from taskThree
        else:
            await asyncio.sleep(1)


    async def taskFour(self, inputVal=0):
        print(timestamp(time.time()) + df +f": Task 4 has been called with input {inputVal}")
        await asyncio.sleep(10)
        inputVal += 1
        return inputVal


    async def producer(self):
        now = time.time()
        if (now - self.start_time_prod > self.task_delay_two):
            print(self.c[3] + ": Do task three")
            self.start_time_three = now
            returnVal = await self.taskFour(self.task_four_var)  ## WHY DOES THIS LINE SEEM BLOCKING?
            print(timestamp(now) +f": Task 4 has been returned with variable: {returnVal}")
            self.task_four_var = returnVal  # For another test make this a returned value from taskThree
        else:
            await asyncio.sleep(1)


    async def main(self):
        loop = asyncio.new_event_loop()
        #asyncio.get_event_loop().set_debug(True)
        try:
            while True:
                task1 = asyncio.create_task(self.taskOne())
                task2 = asyncio.create_task(self.taskTwo())
                task3 = asyncio.create_task(self.taskThree())
                #task4 = asyncio.create_task(self.taskFour())
                await asyncio.gather(task1,task2,task3)

                #
                #await asyncio.gather(self.taskOne(),self.taskTwo(),self.taskThree())
        except KeyboardInterrupt:
            print("User Ended Program, Exiting")


prog = asyncTest()
asyncio.run(prog.main())






'''

returnVal = await asyncio.create_task(self.taskFour(self.task_four_var))  ## This line continued to function as before
'''













import sys

## This is used to get arguments from command line input it is not needed here

'''
if len(sys.argv) != 4:
    print(f"Usage: {sys.argv[0]} <host> <port> <num_connections>")
    sys.exit(1)
else:
    data = sys.argv[1:4]
    print(data)
'''
