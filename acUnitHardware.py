'''
acUnit - DEMO

Refrigeration experiment IO demo program.

Demonstrates the function of all hardware IOs.


'''

#import adamModbus as adam
## Init
#from pyModbusTCP.client import ModbusClient
import time
import acUnitGlobals as glbs

import adam6052ModBus as adam6052
import adam6217ModBus as adam6217

import sensorObjects
# This file should not import globals as hw is defined in globals
#import acUnitGlobals as glbs
test_valve_status = [0,1,0,0,1,1,0,0]    ## Just used if hardware is not available remove after testing
#import jsonPacker as pack

# Ethernet Declarations
ADAM_6052_A_IP = "192.168.1.111"
ADAM_6052_B_IP = "192.168.1.116"
ADAM_6217_A_IP = "192.168.1.112"
ADAM_6217_B_IP = "192.168.1.115"

PORT = 502

'''
IO List
# DO - adam6052_A
V1 = adamDIO_A.DO_list[0]       # Self Regulating
V2 = adamDIO_A.DO_list[1]       # Small Capillary
V3 = adamDIO_A.DO_list[2]       # medium Capillary
V4 = adamDIO_A.DO_list[3]       # large Capillary
V5 = adamDIO_A.DO_list[4]       # Receiver Outlet
V6 = adamDIO_A.DO_list[5]       # Receiver Inlet
V7 = adamDIO_A.DO_list[6]       # Receiver Bypass0
unused = adamDIO.DO_list[7]     # Unused

# DO - adam6052_B
W1 = adamDIO_B.DO_list[0]       # fan - condenser
W2 = adamDIO_B.DO_list[1]       # fan - evaporator
V_comp = adamDIO_B.DO_list[2]   # Compressor

#Voltage AI
PS1 = adamAI_C.AI_list[0]       # Evaporation Pressure
PS2 = adamAI_C.AI_list[1]       # Compressor Outlet Pressure
PS3 = adamAI_C.AI_list[2]       # Condenser Outlet Pressure
TC1 = adamAI_C.AI_list[3]       # Compressor Inlet Temperature
TC2 = adamAI_C.AI_list[4]       # Compressor Outlet Temperature
TC3 = adamAI_C.AI_list[5]       # Condenser Outlet Temperature
TC4 = adamAI_C.AI_list[6]       # Evaporator Inlet Temperature
TC5 = adamAI_C.AI_list[7]       # Evaporator Outlet Temperature


#Current AI
flow_meter = adamAI_D.AI_list[0] # Flowmeter
power_meter = adamAI_D.AI_list[1] # Power Meter
APS = adamAI_D.AI_list[2] # ambient pressure sensor
ATS = adamAI_D.AI_list[3] # ambient temp sensor
'''







class acUnitHardware:
    def __init__(self):
        print("Starting AC Unit Refrigeration Rig - Hardware Interface")
        # Setup IOs
        self.adamDIO_A = adam6052.adam6052ModBus(ADAM_6052_A_IP, PORT)
        self.adamDIO_B = adam6052.adam6052ModBus(ADAM_6052_B_IP, PORT)
        self.adamAI_C = adam6217.adam6217ModBus(ADAM_6217_A_IP, PORT)  # 0-10v in for temp & pressure sensors
        self.adamAI_D = adam6217.adam6217ModBus(ADAM_6217_B_IP, PORT)  # 4-20mA in for flow sensor
        self.sensors = sensorObjects.sensorCalc()  ## library for sensor conversions
        # List IO channels
        self.V1 = 0  # Self Regulating
        self.V2 = 1  # Small Capillary
        self.V3 = 2  # medium Capillary
        self.V4 = 3  # large Capillary
        self.V5 = 4 # Receiver Outlet
        self.V6 = 5  # Receiver Inlet
        self.V7 = 6  # Receiver Bypass
        self.unused = 7  # Unused


## Feel like this function should be in a seperate file as it is not pure hardware IO, could be moved later
    def get_all_data(self):
        print(f"Getting all data & saving to global Dic")
        print("This Function has been devolved to main if you see this message something is wrong")
        #valve_list = self.get_all_valves(glbs.simulate_hardware)
        #relay_list = self.get_power_relays(glbs.simulate_hardware)
        #pressure_list = self.get_pressure_sensors(glbs.simulate_hardware)
        #temps_list = self.get_temp_sensors(glbs.simulate_hardware)
        #misc_list = self.get_misc_sensors(glbs.simulate_hardware)
        #glbs.pack.load_valve_data(valve_list)
        #glbs.pack.load_relay_data(relay_list)
        #glbs.pack.load_pressure_data(pressure_list)
        #glbs.pack.load_temp_data(temps_list)
        #glbs.pack.load_misc_data(misc_list)
        #TODO add function here to save all data into database with timestamp
        #TODO or write to csv
        #then (this should definatly go elsewhere
        #TODO add functions to calculate history for each sensor
        #TODO then add functions to write history data to global dictionary



    def set_valve(self, valveNumber, state):
        if valveNumber >= 1 and valveNumber <= 7:
            self.adamDIO_A.set_coil(valveNumber-1, state)
            valveState = self.adamDIO_A.get_coil_state(valveNumber-1)
            if (valveState[0] == state):
                #print(f"Valve V{valveNumber} set to {state}")
                print()
            else:
                print(f"Error checking valve V{valveNumber} state")
        else:
            print(f"ERROR: Unknown Valve V{valveNumber} requested ")

    def set_valve_name(self, valveName, state):
        valve_index = glbs.valve_list.index(valveName)
        #print(f"Valve Index {valve_index}")
        self.adamDIO_A.set_coil(valve_index, state)
        valveState = self.adamDIO_A.get_coil_state(valve_index)
        if (valveState[0] == state):
            print(f"Valve V{valve_index+1} set to {state}")
        else:
            print(f"Error checking valve V{valve_index+1} state")


    def get_valve_state(self, valveNumber):
        if valveNumber >= 1 and valveNumber <= 7:
            valveState = self.adamDIO_A.get_coil_state(valveNumber - 1)
            return valveState[0]
        else:
            print(f"ERROR: Unknown Valve V{valveNumber} requested ")

    def get_all_valves(self, test_mode=False):
        if test_mode == False:
            valveStates = self.adamDIO_A.get_coil_range(self.V1, self.V7)
            valve = 1
            for state in valveStates:
                #print(f"V{valve} = {state}")
                valve = valve + 1
            return valveStates
        else:
            return test_valve_status

    def set_compressor(self,state):
        self.adamDIO_B.set_coil(2, state)
        compressorState = self.adamDIO_B.get_coil_state(2)
        if (compressorState[0] == state):
            print(f"Compressor set to {state}")
            return 0
        else:
            print(f"Error Compressor state")
            return 1

    def set_fans(self,state):
        self.adamDIO_B.set_coil(0, state)
        self.adamDIO_B.set_coil(1, state)
        fanA_state = self.adamDIO_B.get_coil_state(0)
        fanB_state = self.adamDIO_B.get_coil_state(1)
        if (fanA_state[0] == state):
            print(f"Fan A set to {state}")
        else:
            print(f"Error Setting Fan A state")
        if (fanB_state[0] == state):
            print(f"Fan B set to {state}")
        else:
            print(f"Error Setting Fan B state")
        if (fanA_state[0] == state and fanB_state[0] == state):
            return 0
        else:
            return 1


    def get_power_relays(self, sim_hw=False):
        if sim_hw == False:
            relays_state = self.adamDIO_B.get_coil_range(0, 2)
            return relays_state
        else:
            return [0, 1, 0]



    def get_pressure_sensors(self, sim_hw=False):
        if sim_hw == False:
            pressure_voltages = self.adamAI_C.get_voltage_inputs(0, 2)
            sample_timestamp = time.time()
            pressure_list = []
            for voltage in pressure_voltages:
                pressure_bar = self.sensors.voltage_to_pressure(voltage, 0,30,1,6)
                pressure_list.append(pressure_bar)
                #print(f"Pressure: {pressure_bar} bar")
            #print(f"Pressures: P1-3: {pressure_list} bar")
            return (pressure_list, sample_timestamp)
        else:
            return ([23,56,123434], time.time())



    def get_temp_sensors(self, sim_hw=False):
        if (sim_hw):
            return([0,42,0,0,66.6], time.time())
        else:
            temp_voltages = self.adamAI_C.get_voltage_inputs(3, 7)
            sample_timestamp = time.time()
            temp_list = []
            for voltage in temp_voltages:
                temp_degC = self.sensors.voltage_to_temp(voltage)
                temp_list.append(temp_degC)
                # print(f"Pressure: {pressure_bar} bar")
            #print(f"Temperature: T1-5: {temp_list} degC")
            return (temp_list, sample_timestamp)


    def get_misc_sensors(self, sim_hw=False):   #TODO test this with hardware
        misc_sensors = []
        if (sim_hw == False):
            misc_sensors.append(self.get_flow_sensor())
            misc_sensors.append(self.get_power_meter())
            misc_sensors.append(self.get_ambient_sensors())
            sample_timestamp = time.time()
            return (misc_sensors, sample_timestamp)
        else:
            return ([1,2,3,4],time.time())

    def get_flow_sensor(self):
        #print("Getting Flow Sensor")
        flow_mA = self.adamAI_D.get_current_inputs(0, 0)[0]
        flow_rate_Lh = self.sensors.current_to_flowmeter(flow_mA)
        #print(f"Flow Rate: {flow_rate_Lh} L/hour")
        return flow_rate_Lh


    def get_power_meter(self):
        # getting offset of 2.6 W at zero, under scale by ~ 2 W at upper range
        #print("Getting Power Meter Value")
        power_mA = self.adamAI_D.get_current_inputs(1,1)[0]
        #print(f"Power Meter: {power_mA} mA")
        power_W =  self.sensors.current_20mA_to_power(power_mA)
        #print(f"Power Consumption: {power_W} W")
        return power_W


    def get_ambient_sensors(self):
        #print("Getting Ambient Conditions Sensor")
        ambi_pressure = self.sensors.current_to_pressure(self.adamAI_D.get_current_inputs(2, 2)[0])
        ambi_temperature = self.sensors.current_to_temperature(self.adamAI_D.get_current_inputs(3, 3)[0])
        ambient_sensors = [ambi_temperature,ambi_pressure]
        #print(f"Ambient Temp: {ambient_sensors[0]} degC, Ambient Pressure: {ambient_sensors[1]} mBar")
        return ambient_sensors

#TODO: Implement JSON interface using user inputs for CLI


def main():
    print("Starting AC Unit Refrigeration Rig - DEMO")
    # Setup IO Devices & start  library
    ac = acUnitHardware()
    # Set up Initial State
    ac.adamDIO_A.set_all_coils([0,0,0,0,0,0,0,0])   # direct method setting specific controller coil states
    ac.adamDIO_B.set_all_coils([0,0,0,0,0,0,0,0])
    ac.adamDIO_A.get_all_coils()
    ac.adamDIO_B.get_all_coils()
    ac.set_compressor(False)
    ac.set_fans(False)
    #print("AC Unit Init Complete - Starting Acquisition & Control loop")
    time.sleep(2)
    iteration = 0
    while(1):
        print(f"{iteration}:", end="\n")
        # Functions to return data to UI
        # tested
        #ac.get_all_valves()
        sensor_return = ac.get_pressure_sensors()
        print(sensor_return[1])
        #ac.get_temp_sensors()
        #ac.get_flow_sensor()
        #ac.get_power_meter()
        #ac.get_ambient_sensors()

        time.sleep(1)
        iteration = iteration + 1
        ## Functions for setting acUnit State
        ac.set_valve(5, True)    ## abstracted method setting ac valve state
        ac.set_valve(6, True)
        #ac.set_compressor(True)
        #ac.set_fans(True)
        #time.sleep(5)
        #ac.adamDIO_A.set_all_coils([1,1,1,1,1,1,1,1])
        if (iteration/2).is_integer():
            ##ac.set_valve(5, False)  ## abstracted method setting ac valve state
            ##ac.set_valve(6, False)
            continue







if __name__ == "__main__":
    main()
    print("Program Quit")

