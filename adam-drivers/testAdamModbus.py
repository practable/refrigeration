"""
adamModbus - Example

Series of python drivers for ModBus Communication with Advantech ADAM Data Acquisition Modules.
- More Robust and Simple operation than ASCII commands and websockets.
- Simple


See the following classes for specific ADAM controllers:

ADAM-6052 (8DI, 8DO): adam6052ModBus.py
ADAM-6217 (8AI):      adam6052ModBus.py
ADAM-6018+ (8TC):     adam6018ModBus.py
ADAM-6024  (6AI, 2AO, 2DI, 2DO) adam6024ModBus.py


# READ THE DOCS!
https://pypi.org/project/pyModbusTCP/
https://control.com/forums/threads/reading-di-do-status-of-adam-6050.27164/
In directory: adam-user-manuals:
- ADAM-6000_User_Manaul_Ed.12-FINAL.pdf
- ADAM-6200_User_Manual_Ed.5_FINAL.pdf

Example ModBus commands (ADAM-6052 docs)
Example: Force Coil 3 (Address 00003) to ON in an ADAM-6000 module.
01 05 00 03 FF 00

Example: Force Coil DO 0 (Address 00017 (0x11)) to ON in an ADAM-6000 module.
01 05 00 11 FF 00

"""

## Init
#from pyModbusTCP.client import ModbusClient
import time

import adam6052ModBus as adam6052
import adam6217ModBus as adam6217
import adam6018ModBus as adam6018
import adam6024ModBus as adam6024


# Ethernet Delarations
ADAM_6052_IP = "192.168.1.111"
ADAM_6217_IP = "192.168.1.112"
ADAM_6018_IP = "192.168.1.113"
ADAM_6024_IP = "192.168.1.114"

PORT = 502




def main():
    print("Starting ADAM Modbus control")
    iteration = 0
    adamDIO = adam6052.adam6052ModBus(ADAM_6052_IP, PORT)
    adamAI = adam6217.adam6217ModBus(ADAM_6217_IP, PORT)
    adamTC = adam6018.adam6018ModBus(ADAM_6018_IP, PORT, tc_type="K")   ## tc_type does nothing at the moment! (set type in adam utility)
    adamUIO = adam6024.adam6024ModBus(ADAM_6024_IP, PORT)
    adamUIO.set_analog_output(1, 0, "mA_4")
    while (True):
        print(f"{iteration}:", end="\n")
        #adamDIO.get_all_inputs()
        #adamAI.get_all_inputs()
        #adamTC.get_all_inputs()
        adamUIO.get_analog_inputs()
        #adamUIO.get_digital_inputs()
        #adamDIO.set_coil(0, True)
        #adamUIO.set_all_coils([1,0])
        time.sleep(5)
        #adamDIO.set_all_coils([0, 0, 0, 0, 0, 0, 0, 0])
        #adamUIO.set_all_coils([0,1])

        time.sleep(3)
        iteration = iteration + 1


    # adam6052_set_coil(0, True)
    # time.sleep(4)
    # adam6052_set_coil(0, False)
    # time.sleep(4)
    # time.sleep(5)
    # adam6052_set_all_coils(DO_state)
    # time.sleep(4)
    # time.sleep(5)
    # adam6052_set_all_coils([0,0,0,0,0,0,0,0])



if __name__ == "__main__":
    main()
    print("Program Quit")

