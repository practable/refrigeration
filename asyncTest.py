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
    dp = round(100*(diff - round(diff, 0)),4)
    if dp == 0.0:
        s_diff = str(diff) + "0"
    else:
        s_diff = str(diff)
    if diff < 10:
        return f"{df}0{s_diff}"
    else:
        return df + s_diff


class asyncTest:
    def __init__(self):
        self.start_time = time.time()
        print(f"asyncTest Started at: {datetime.now()}")
        self.start_time_one = self.start_time
        self.start_time_two = self.start_time
        self.start_time_three =  self.start_time
        self.task_delay_one = TASK_ONE_DELAY
        self.task_delay_two = TASK_TWO_DELAY
        self.task_delay_three = TASK_THREE_DELAY
        self.start_time_prod = self.start_time
        self.task_four_var = 1
        self.cmd_queue = []


    async def taskOne(self):
        while(True):
            now = time.time()
            if (now - self.start_time_one > self.task_delay_one):
                print(timediff(now,self.start_time_one) + yl + ": Do task one")
                self.start_time_one = now
            else:
                await asyncio.sleep(1)

    async def taskTwo(self):
        while (True):
            now = time.time()
            if ( now - self.start_time_two > self.task_delay_two):
                print(timediff(now,self.start_time_two) + cy +": Do task Two")
                self.start_time_two = now
            else:
                await asyncio.sleep(1)

    async def taskThree(self, i=0):
        while (True):
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
            print(mg + ": Do task three")
            self.start_time_three = now
            returnVal = await self.taskFour(self.task_four_var)  ## WHY DOES THIS LINE SEEM BLOCKING?
            print(timestamp(now) +f": Task 4 has been returned with variable: {returnVal}")
            self.task_four_var = returnVal  # For another test make this a returned value from taskThree
        else:
            await asyncio.sleep(1)


    def main(self):
        loop = asyncio.new_event_loop()
        loop.create_task(self.taskOne())
        loop.create_task(self.taskTwo())
        loop.create_task(self.taskThree())
        loop.run_forever()




prog = asyncTest()
prog.main()






