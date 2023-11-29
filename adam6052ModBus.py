'''
adam6052 Controller - 8DI 8DO - ModBus

Advantech ADAM 6052 Data Acquisition Module - Digital IO - driver

- 8 Digital Inputs (Dry Contact, Wet Contact (0-30v))
- 8 Digital Outputs (5/10v)

# READ THE DOCS!
https://pypi.org/project/pyModbusTCP/
In directory: adam-user-manuals:
- ADAM-6000_User_Manaul_Ed.12-FINAL.pdf
- ADAM-6200_User_Manual_Ed.5_FINAL.pdf
'''


from pyModbusTCP.client import ModbusClient
import time



class adam6052ModBus:
    def __init__(self, adam_ip, port = 502):
        print(f'Initializing adam6052 8-DI 8-DO ModBus...')
        self._IP = adam_ip
        self.port = port
        self.DO_list = [0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17]  #DO_0 to DO_7
        self.DO_state = [0,0,0,0,0,0,0,0]   # Dont rely too much on this untill checking added
        self.DI_list = [0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07]
        self.DI_state = [0,0,0,0,0,0,0,0]
        # Create a Modbus TCP client
        # Module init (TCP always open)
        self.adam6052 = ModbusClient(host=self._IP, port=self.port, unit_id=1, auto_open=True)


    def set_coil(self, DO_number, state):
        no_error = self.adam6052.write_single_coil(self.DO_list[DO_number], state)
        time.sleep(0.5)
        if (no_error):
            #print(f"adam6052: coil DO_{DO_number}: Written to {state}")
            return 0   # return false if complete
        else:
            print(f"adam6052: coil DO_{DO_number}: Unable to write to {state}")
            return 1  # error code can be returned here


    def set_output(self, output, state):
        no_error = self.adam6052.write_single_coil(output, state)
        time.sleep(0.5)
        if (no_error):
            #print(f"adam6052: output {output}: Written to {state}")
            return 0   # return false if complete
        else:
            print(f"adam6052: output {output}: Unable to write to {state}")
            return 1  # error code can be returned here

    def set_all_coils(self, states):
        no_error = (self.adam6052.write_multiple_coils(self.DO_list[0], states))
        self.DO_state = states
        time.sleep(0.5)
        if (no_error):
            #print(f"adam6052: all coils: Written to {states}")
            return 0  # return false if complete
        else:
            print(f"adam6052: all coils: Unable to write to {states}")
            return 1  # error code can be returned here


    def get_input(self, DI_number):
        #print(f"adam6052: Reading Input DI_{DI_number}")
        inputs_list = self.adam6052.read_discrete_inputs(DI_number, 1)
        inputs_list = [int(val) for val in inputs_list]   ## turn bool list into int list
        if inputs_list:
            #print(f"DI_{DI_number}: {inputs_list}")
            return inputs_list
        else:
            print("adam6052: Unable to read digital input :(")
            return "ERROR"

    def get_all_inputs(self):
        #print("adam6052: Reading all Inputs")
        inputs_list = self.adam6052.read_discrete_inputs (0, 8)
        if inputs_list:
            self.DI_state = [int(val) for val in inputs_list]  ## turn bool list into int list
            #print(f"DI_0-7: {self.DI_state}")
            return self.DI_state
        else:
            print("adam6052: Unable to read digital inputs :(")
            return "ERROR"

    def get_coil_state(self, coilNumber):
        #print("adam6052: Reading all Inputs")
        inputs_list = self.adam6052.read_discrete_inputs (self.DO_list[coilNumber], 1)
        if inputs_list:
            self.DI_state = [int(val) for val in inputs_list]  ## turn bool list into int list
            #print(f"DI_{coilNumber}: {self.DI_state}")
            return self.DI_state
        else:
            print(f"adam6052: Unable to read coil DO_{coilNumber} :(")
            return "ERROR"

    def get_all_coils(self):
        #print("adam6052: Reading all Inputs")
        inputs_list = self.adam6052.read_discrete_inputs (self.DO_list[0], 8)
        if inputs_list:
            self.DI_state = [int(val) for val in inputs_list]  ## turn bool list into int list
            #print(f"DI_0-7: {self.DI_state}")
            return self.DI_state
        else:
            print("adam6052: Unable to read coil values :(")
            return "ERROR"

    def get_coil_range(self, lower, upper):
        #print("adam6052: Reading all Inputs")
        range = (upper-lower)
        inputs_list = self.adam6052.read_discrete_inputs (self.DO_list[lower], range+1)
        if inputs_list:
            self.DI_state = [int(val) for val in inputs_list]  ## turn bool list into int list
            #print(f"DI_0-7: {self.DI_state}")
            return self.DI_state
        else:
            print("adam6052: Unable to read coil values :(")
            return "ERROR"