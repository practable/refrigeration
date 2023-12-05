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

import asyncio
import time

TASK_ONE_DELAY = 5
TASK_TWO_DELAY = 2
TASK_THREE_DELAY = 15

class asyncTest:
    def __init__(self):
        self.start_time = time.time()
        self.start_time_one = self.start_time
        self.start_time_two = self.start_time
        self.start_time_three =  self.start_time
        self.task_delay_one = TASK_ONE_DELAY
        self.task_delay_two = TASK_TWO_DELAY
        self.task_delay_three = TASK_THREE_DELAY
        self.task_four_var = 1
        self.c = ( # ANSI colors
            "\033[0m",   # End of color
            "\033[36m",  # Cyan
            "\033[93m",  # Yellow  30 black 31 red 37 grey
            "\033[35m",  # Magenta)
        )
        time.sleep(4)


    async def taskOne(self):
        current_time = time.time()
        if (current_time - self.start_time_one > self.task_delay_one):
            print(self.c[1] + "Do task one")
            self.start_time_one = current_time
        else:
            await asyncio.sleep(1)

    async def taskTwo(self):
        current_time = time.time()
        if (current_time - self.start_time_two > self.task_delay_two):
            print(self.c[2] +"Do task Two")
            self.start_time_two = current_time
        else:
            await asyncio.sleep(1)

    async def taskThree(self):
        current_time = time.time()
        if (current_time - self.start_time_three > self.task_delay_three):
            print(self.c[3] + "Do task three")
            self.start_time_three = current_time
            returnVal = await self.taskFour(self.task_four_var)  ## WHY DOES THIS LINE SEEM BLOCKING?
            print(f"Task 4 has been returned with variable: {returnVal}")
            self.task_four_var = returnVal   # For another test make this a returned value from taskThree
        else:
            await asyncio.sleep(1)


    async def taskFour(self, inputVal):
        print(self.c[0]+f"Task 4 has been called with input {inputVal}")
        await asyncio.sleep(10)
        inputVal += 1
        return inputVal

    async def main(self):
        try:
            while True:
                await asyncio.gather(self.taskOne(),self.taskTwo(),self.taskThree())
        except KeyboardInterrupt:
            print("User Ended Program, Exiting")


prog = asyncTest()
asyncio.run(prog.main())




















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
