'''


'''

##TODO ALL THIS FUNCTIONALITY SHOULD BE DEVOLVED INTO CLASSES FOR EACH SENSOR, WHICH ALSO CONTAIN A HISTORY OF THAT SENSOR

'''
Note: Buffer size

for 5 mins of samples @ 1 Hz = 300 samples

'''

import time
import numpy as np

BUFFER_SIZE = 300

class temperatureSensor:
    def __init__(self):
        #print(f'Temperature Sensor Library Deployed')
        self.current_val = 0
        self.sensor_history = []
        self.sensor_timestamp = []
        self.init_time = round(time.time())

    '''
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
    '''
    def calculate_history(self):
        average = self.calculate_average()
        min_max = self.calculate_min_max()
        dx_dy = self.calculate_dx_dy()
        lms = self.calculate_lms()
        output = [self.current_val, min_max[0],min_max[1],average,dx_dy,lms]
        return output

    def add_new_datapoint(self, new_datapoint, timestamp):
        buffer_length = len(self.sensor_history)
        self.current_val = new_datapoint
        #elapsed_time = round(time.time()-self.init_time)
        if buffer_length < BUFFER_SIZE:
            self.sensor_history.append(new_datapoint)
            self.sensor_timestamp.append(timestamp)
        elif buffer_length == BUFFER_SIZE:
            self.sensor_history.pop(0)
            self.sensor_timestamp.pop(0)
            self.sensor_history.append(new_datapoint)
            self.sensor_timestamp.append(timestamp)
        elif buffer_length > BUFFER_SIZE:
            overshoot = buffer_length - BUFFER_SIZE
            del self.sensor_history[0:overshoot+1]
            del self.sensor_timestamp[0:overshoot+1]
            self.sensor_history.append(new_datapoint)
            self.sensor_timestamp.append(timestamp)

    def calculate_average(self):
        buffer_length = len(self.sensor_history)
        total = 0
        for item in self.sensor_history:
            total = total+item
        average = total/buffer_length
        #print(f"Average of {buffer_length} samples: {average} degC")
        return average

    def calculate_min_max(self):
        current_max = 0
        current_min = self.sensor_history[0]
        for item in self.sensor_history:
            if item >= current_max:
                current_max = item
            if item <= current_min:
                current_min = item
        return [current_min, current_max]

#TODO ask Siji about which dt/dt she wants
    def calculate_dx_dy(self):
        try:
            dx = np.diff(self.sensor_history)
            dy = np.diff(self.sensor_timestamp)
            #d = dy/dx
            return 1
        except:
            error = ("Error: calculating dx/dy")
            return error

#TODO speak to Time & Siji
    def calculate_lms(self):
        #pinv = np.linalg.pinv(zip(self.sensor_history,self.sensor_timestamp))
        #alpha = pinv.dot(self.sensor_timestamp)
        alpha = 6
        return alpha



#TODO fix this function here (this one not used atm because sensorCalc class is used for voltage to temp calcs)
    def voltage_to_temp(self, voltage, degC_min=-50, degC_max=100, Vmin=0, Vmax=10):
        #2.53 v = 25 degC
        factor = 9.88
        tempRange = degC_max - degC_min
        vRange = Vmax - Vmin
        #factor = tempRange / vRange
        # print(f"Voltage to Pressure Factor: {factor}")
        temperature = round(((voltage) * factor), 3)
        # print(f"Calculating Voltage: {voltage} V = Pressure: {pressure} bar")
        return temperature





class sensorCalc:
    def __init__(self):
        print(f'Sensor Voltage/Current to Process Value Library Deployed')


    def current_to_flowmeter(self, current_mA, range_min=2, range_max=25, offset=1.3):   # for ABB D10A3255xxA1 flowmeter
        range = range_max - range_min
        flow_per_mA = range/16
        flowrate = round(((flow_per_mA * (current_mA-4))+ offset),3)       #
        #print(f"Convert Current: {current_mA} to flow-rate: {flowrate} L/h")
        #print("ERROR/TODO: Calculated value does not precisely match gauge value") #TODO Make sure calculations are accurate
        return flowrate


    def voltage_to_pressure(self, voltage, bar_min = 0,  bar_max = 30, Vmin=1, Vmax=6):
        barRange = bar_max - bar_min
        vRange = Vmax - Vmin
        factor = barRange/vRange
        #print(f"Voltage to Pressure Factor: {factor}")
        pressure = round(((voltage-Vmin)*factor), 3)
        #print(f"Calculating Voltage: {voltage} V = Pressure: {pressure} bar")
        return pressure


#TODO fix this function here
    def voltage_to_temp(self, voltage, degC_min=-50, degC_max=100, Vmin=0, Vmax=10):
        #2.53 v = 25 degC
        factor = 9.88
        tempRange = degC_max - degC_min
        vRange = Vmax - Vmin
        #factor = tempRange / vRange
        # print(f"Voltage to Pressure Factor: {factor}")
        temperature = round(((voltage) * factor), 3)
        # print(f"Calculating Voltage: {voltage} V = Pressure: {pressure} bar")
        return temperature


    def current_20mA_to_power(self, current, P_min=0, P_max=1053, I_min=0, I_max=20):
        # 3.123 mA = 205.6 W
        powerRange = P_max - P_min
        I_range = I_max - I_min
        #factor = powerRange / I_range
        factor = 65.834
        #print(f"Current to Power Factor: {factor}")
        power = round((((current-I_min)*factor)),1)     #-2.05 offset?
        #print(f"Calculating Power: {current} mA = {power} W")
        return power

    def current_to_pressure(self, current, bar_min = 0, bar_max=100, I_min=0, I_max=20):
        pressureRange = bar_max - bar_min
        I_range = I_max - I_min
        factor = pressureRange / I_range
        #print(f"Current to Pressure Factor: {factor} ")
        pressure = round(((current-I_min)*factor),3)
        #print(f"Calculating Current: {current} mA = Pressure: {pressure} bar")
        return pressure

    def current_to_temperature(self, current, temp_min=0, temp_max=100,I_min=0, I_max=20):
        tempRange = temp_max - temp_min
        vRange = I_max - I_min
        factor = tempRange / vRange
        #print(f"Current to Pressure Factor: {factor}")
        temperature = round(((current - I_min) * factor), 3)
        #print(f"Calculating Current: {current} mA = Temp: {temperature} degC")
        return temperature