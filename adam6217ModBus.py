'''
adam6217 Controller - 8AI - ModBus

Advantech ADAM 6217 Data Acquisition Module - Analog In -  driver

- 8 Analog Inputs (-10/+10 v), (0/20mA)

# READ THE DOCS!
https://pypi.org/project/pyModbusTCP/
In directory: adam-user-manuals:
- ADAM-6000_User_Manaul_Ed.12-FINAL.pdf
- ADAM-6200_User_Manual_Ed.5_FINAL.pdf
'''


from pyModbusTCP.client import ModbusClient






class adam6217ModBus:
    def __init__(self, adam_ip, port = 502):
        print(f'Initializing adam6217 8-AI ModBus...')
        self._IP = adam_ip
        self.port = port
        self.AI_list = [0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07]
        #self.AI_state = [0,0,0,0,0,0,0,0]
        self.adam6217 = ModbusClient(host=self._IP, port=self.port, unit_id=1, auto_open=True)

    def get_all_inputs(self):
        #print("adam6217: Reading all Inputs")
        inputs_list = self.adam6217.read_input_registers(0, 8)
        AI_voltages = []
        if inputs_list:
            #print(f"AI_0-7: {inputs_list}")
            i = 0
            for value in inputs_list:
                #print(f"AI_{i}:",end=" " )
                voltage = self.calculate_voltage(value)
                AI_voltages.append(voltage)  #TODO Check this is working here (changed from self.AI_state
                i = i+1
            print(f"AI_0-7: {AI_voltages}")
            return AI_voltages
        else:
            print("adam6217: Unable to read Analog inputs :(")
            return "ERROR"



    def get_voltage_inputs(self, startAddr=0, endAddr=7):
        num_inputs = (endAddr-startAddr)+1
        #print(f"adam6217: Reading Inputs {startAddr} to {endAddr}. No. Inputs: {num_inputs}")
        inputs_list = self.adam6217.read_input_registers(startAddr, num_inputs)
        if inputs_list:
            #print(f"AI_{startAddr}-{endAddr}: {inputs_list}")
            i = 0
            voltage_list = []
            for value in inputs_list:
                #print(f"AI_{i}:",end=" " )
                voltage = self.calculate_voltage(value)
                voltage_list.append(voltage)
                i = i+1
            #print(f"AI_0-7: {voltage_list} V")
            return voltage_list
        else:
            print("adam6217: Unable to read Analog inputs :(")
            return "ERROR"




    def get_current_inputs(self, startAddr=0, endAddr=7):     #4-20mA input
        num_inputs = (endAddr - startAddr) + 1
        inputs_list = self.adam6217.read_input_registers(startAddr, num_inputs)
        if inputs_list:
            #print(f"AI_{startAddr}-{endAddr}: {inputs_list} DAC_val")
            i = 0
            current_list = []
            for value in inputs_list:
                #print(f"AI_{i}:",end=" " )
                current = self.calculate_current_0(value)
                current_list.append(current)
                #self.AI_state[i] = current
                i = i + 1
            #print(f"AI_{startAddr}-{endAddr}: {current_list} mA")
            return current_list
        else:
            print("adam6217: Unable to read Analog inputs (4-20mA) :(")
            return "ERROR"



    def calculate_voltage(self, inputValue):
        # Offset is 32768
        voltage = inputValue - 32768
        #with offset removed 3v input = 9772 returned
        voltage = round(voltage/3257.333,2)
        #print(f"Measured Voltage: {voltage}")
        return voltage

    def calculate_current_0(self, inputValue):   ## Maths for channel set to 0-20mA
        #13022 = 3.974
        current = round(inputValue/3276.799,3)
        return current
