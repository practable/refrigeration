#!/usr/bin/env python3
'''
acUnitMain


understanding asyncio
https://medium.com/dev-bits/a-minimalistic-guide-for-understanding-asyncio-in-python-52c436c244ea
Understanding Threads
https://stackoverflow.com/questions/71969640/how-to-print-countdown-timer-and-accept-user-input-at-the-same-time-python/71971926#71971926



'''
import asyncio
import logging
from threading import Thread
thread_running = True



import acUnitGlobals as glbs
import acUnitStateMachine
import time

import sensorObjects as so

import commandClient as cc
import reportingClient as rc



# Renaming global variables to reduce number of things.with.references.to.other.things
hw = glbs.acHardware
parse = glbs.jsonParse
pack = glbs.jsonPack
# State machine must be defined here to avoid circular references
#sm = acUnitStateMachine.init_state()


PS1 = so.temperatureSensor()     ## method for datalogging and analysis is generic at the moment
PS2 = so.temperatureSensor()
PS3 = so.temperatureSensor()
TS1 = so.temperatureSensor()
TS2 = so.temperatureSensor()
TS3 = so.temperatureSensor()
TS4 = so.temperatureSensor()
TS5 = so.temperatureSensor()
flow = so.temperatureSensor()
power = so.temperatureSensor()

PS_array = [PS1, PS2, PS3]
TS_array = [TS1, TS2, TS3, TS4, TS5]


#async def gather_data(iteration=0):
def gather_data(iteration=0):
    global thread_running
    # Sample the hardware IOs: Valves, Power Relays, Pressure Sensors
    start_time = time.time()
    while thread_running:
        loop_start_time = time.time()
        valve_list = hw.get_all_valves(glbs.simulate_hardware)
        relay_list = hw.get_power_relays(glbs.simulate_hardware)
        pressure_list = hw.get_pressure_sensors(glbs.simulate_hardware)
        # add pressure sensor datapoints to sensor history
        PS1.add_new_datapoint(pressure_list[0][0],pressure_list[1])   ##2nd value in returned list is timestamp
        PS2.add_new_datapoint(pressure_list[0][1],pressure_list[1])
        PS3.add_new_datapoint(pressure_list[0][2],pressure_list[1])
        # Sample Hardware IOs: Temperature Sensors
        temps_list = hw.get_temp_sensors(glbs.simulate_hardware)
        i = 0
        # Add temperature datapoints to sensor history
        for temp in temps_list[0]:
            #print(temp)
            TS_array[i].add_new_datapoint(temp,temps_list[1])
            i = i+1
        # Sample Hardware IOs: Misc Sensors
        misc_list = hw.get_misc_sensors(glbs.simulate_hardware)
        # Add Flow Rate and Power Consumption datapoints to sensor history
        flow.add_new_datapoint(misc_list[0][0], misc_list[1])
        power.add_new_datapoint(misc_list[0][1], misc_list[1])
        # Pack all recorded current datapoints into global dictionary (database)
        pack.load_valve_data(valve_list)
        pack.load_relay_data(relay_list)
        # DEPRECIATED, now its all transfered in via the
        # Calculate sensor history variables & pack into global dictionary
        pack.load_sensor_data("PS1", PS1.calculate_history())
        pack.load_sensor_data("PS2", PS2.calculate_history())
        pack.load_sensor_data("PS3", PS3.calculate_history())
        i=0
        for sensor in TS_array:
            pack.load_sensor_data(pack.ts_list[i], sensor.calculate_history())
            i = i+1
        pack.load_sensor_data("flow", flow.calculate_history())
        pack.load_sensor_data("power", power.calculate_history())
        ## Pack error messages
        pack.load_status_data()
        ## Dump data into JSON format
        #pack.dump_json()
        iteration += 1
        #await asyncio.sleep(1)
        av_loop = round(benchmark_process(loop_start_time),2)
        #logging.info(f"Samples Taken, Iteration: {iteration} Average Loop Time:{av_loop}")
        time.sleep(0.9899)

        #print(iteration)
        #return iteration


time_list = []
def benchmark_process(process_start_time):
    time_taken = time.time() - process_start_time
    time_list.append(time_taken)
    average_loop_time = sum(time_list) / len(time_list)
    if len(time_list) >= 300:
        del time_list[0:len(time_list) - 300]
    #print(f"Loop Time {time_taken}")
    #print(f"Average Loop Time: {average_loop_time}")
    return average_loop_time

#async def json_interface(iteration=0):
def local_json_interface(iteration=0):
    global thread_running
    while(thread_running):
        command = parse.user_input_json()
        #command = 0
        print(command)
        #glbs.update_command(command)  ## depreciated
        glbs.command_received = True
        glbs.command_queue.append(command)
        #print(iteration)
        iteration += 1
        #time.sleep(1)
    #await asyncio.sleep(1)

def command_client():
    global thread_running
    while(thread_running):
        cc.commandClient()

def reporting_client():
    global thread_running
    while(thread_running):
        rc.reportingClient()



#TODO Move this to JSON parser
expansion_valve_list = ["V1", "V2", "V3", "V4"]

##TODO Define all state names in a list
##TODO write function for each state
##TODO state machine should just run state based on listed name

sm = acUnitStateMachine.init_state()

def state_machine():
    global thread_running
    while (thread_running):
        sm()
        #await asyncio.sleep(1)
        #ield from asyncio.sleep(n)

def check_globals():
    while (thread_running):
        print(f"command_received: {glbs.command_received}")
        time.sleep(10)
    #wait asyncio.sleep(1)


#using asyncio each "task" should be defined as an async option.
# tasks detailed below
"""
task: gather-data: save into current state dictionary, update 5 mins of samples to buffers, update csv with timestamp, calculate sensor history
task: listen for JSON messages and parse commands -> do all sorting here
task: run-state-machine: set hardware IO and system state in response to commands
"""
# An Event Loop
#loop = asyncio.get_event_loop()

# Create a function to schedule co-routines on the event loop
# then print results and stop the loop
#NOT SURE ABOUT THAT ONE CHEIF
#async def run_loop():
#    await asyncio.gather(state_machine(), gather_data(), json_interface(), check_globals())




def main():
    i = 0
    global thread_running
    glbs.init_logging()
    try:
        t1 = Thread(target=state_machine)
        t2 = Thread(target=gather_data)
        t3 = Thread(target=command_client)
        t4 = Thread(target=reporting_client)

        t2.daemon = True
        t3.daemon = True
        t4.daemon = True

        t1.start()
        t2.start()
        t3.start()
        t4.start()

        #t1.join()
        t2.join()
        t3.join()
        t4.join()

        #while t1.isAlive():
        #    do.you.subthread.thing()
        #gracefully.close.the.thread()


    #hile(1):
        #syncio.run(run_loop())
      #asyncio.run(state_machine())
        #asyncio.run(gather_data(i))
        #asyncio.run(json_interface(i))
        #loop = asyncio.get_event_loop()

        i = i+1
    except SystemExit or KeyboardInterrupt:
        print("User Terminated Program")
        thread_running = False
        t1.join()
        t2.join()
        t3.join()
        t4.join()
    except Exception as ex:  ## generic exception handler
        glbs.generic_exception_handler(ex, "main")
        thread_running = False
        #template = "An exception of type {0} occured. Arguments: \n{1!r}"
        #message = template.format(type(ex).__name__, ex.args)
        #print(message)
        #thread_running = False
        #print(" ")
        #print(traceback.format_exc())
        #pdb.post_mortem()
        #print("Program Error")
        raise






if __name__ == '__main__':
    main()

