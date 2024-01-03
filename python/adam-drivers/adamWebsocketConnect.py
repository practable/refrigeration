'''

 adamConnect

 A class for connecting to and controlling ADAM Data aquisition modules

 ADAM Manual Found @:

 http://advdownload.advantech.com/productfile/Downloadfile4/1-1M99LTH/ADAM-6000_User_Manaul_Ed_9.pdf
 pg 141 for command explanations




Using Guidence on opening a websocket from:
https://control.com/forums/threads/send-ascii-command-to-adam-6017-with-python.32502/


Additional added commands for use with adamEmulator for Raspberry Pi. Allows direct swap of ADAM controller
 or Raspberry pi with no change in framework, but additional functions available, eg polling of SPI & I2C sensors.

ADAM MODULE DEFAULT PASSWORDS FOR WEB SERVER

root
00000000

'''


import socket
import time


import adamGlobals as aG





# Adam Commands

com_start = "#01"
com_end = "\r"
# For single channels, next two bytes are 0, then CH number
# For all channels next two bytes are 00
#

DEVICE_INFO = b'#01\r'

# READ_INS    = b'#017\r'     # For universal ADAM Controllers
READ_INPUTS  = b'$016\r'    # For Digital OI Modules (6050, 6051, 6052, 6060, 6066) (note $ instead of #)


ALL_HIGH    = b"#010001\r"
ALL_LOW     = b"#010000\r"
ZERO_HIGH   = b"#011001\r"
ONE_HIGH    = b"#011101\r"

'''
Example command: #011201(cr)
response: >(cr)
An output bit with value 1 is sent to Channel 2 of the digital output module at
Address 01h.
Channel 2 of the digital output module is thus set to ON.
'''

# Pi Specific Commands
GET_DO       = b"$021\r"

# Ethernet Delarations (Only used for Example main()
ADAM_6052_IP = "192.168.1.111"
ADAM_6217_IP = "192.168.1.112"
PORT = 1025    #1024-1029 valid
BUFFER = 1024


class adamConnect:
    def __init__(self, adam_ip, port = 1025, buf = 1024):
        print(f'Initializing adamConnect..')
        self._IP = adam_ip
        self.port = port
        self.addr = (self._IP, self.port)
        self.buf = buf
        self.connected = False
        self.i_am_adam = False
        self.i_am_pi = False
        self.s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.s.settimeout(2)
        self.output_states = "00000000"

    def open_socket(self):
        print(f'Connecting to ADAM Controller...')
        print(f'ADAM Address: [ {self._IP} : {self.port} ]')
        try:
            self.s.bind(('', self.port))
            response = self.get_device_info()
            error_check = self.check_response(response)   # Checks response against specific flags
            if error_check:
                aG.success_message()
                self.connected = True
                return True
            else:
                self.connected = False
                return False
        except socket.timeout:
            aG.timeout_message()
            self.connected = False
            return False
        except OSError:
            aG.os_errormessage()
            self.connected = False
            return False

    def keep_alive(self):                           # Checks connection & Keeps alive. BROKEN ATM
        self.s.sendto(DEVICE_INFO, self.addr)
        response = self.s.recvfrom(self.buf)
        print(response)

# General Command Methods

    def send_command(self, command):               # generic command method, command must be constructed before passing
        try:
            self.s.sendto(command, self.addr)
            response = self.s.recvfrom(self.buf)
            print(response)
            self.check_response(response)
        except socket.timeout:
            aG.timeout_message()
            return False
        except OSError:
            aG.os_errormessage()
            return False



    def set_do_state(self, channel, level):    # Constructs correct command for given channel and input level
        print(F"setting DO {channel}, {level} ")
        command = com_start
        command += "1" + str(channel)
        command += "0"
        if level:
            command += "1"
        elif not level:
            command += "0"
        else:
            print("Error defining channel state")
            return False
        command += com_end
        command = command.encode('utf-8')
        print("Sending Command")
        print(command)
        response = self.send_command(command)
        return response


    def set_all_do(self, channel_status: bytes):         # Sate byte passed as 8 bits representing the sate if each output channel
        print(F"Setting DO.s")
        command = com_start
        command += "00"
        command += "1"
#missing commands, try below but untested.
        return False




    def read_di_state(self):                # Reads all Digital Inputs and Returns a channel list & state of all inputs
        print("Reading Digital Input States")
        try:
            self.s.sendto(READ_INPUTS, self.addr)
            response = self.s.recvfrom(self.buf)
            print(response)
            ch_list = self.decode_response(response)   # Line here does the heavy lifting of decoding the response
            return ch_list
        except socket.timeout:
            aG.timeout_message()
            return False
        except OSError:
            aG.os_errormessage()
            return False


    def read_ai_state(self):
        print("Method to send command to return Analog input states")


# General Response Methods

# Check responses to get_device_info against known flags
    def check_response(self, response):                         # Checks response to see if it matches known responses
        if response == (b'>01\r', self.addr):                        # Note: delimiter on successful command is >
            print("ADAM Response Received\n\n")                 # This method is used to check responses to KEEP ALIVE
            self.define_remote_host("adam")                        # keep_alive() and get_device_info() Commands
            return True
        elif response == (b'02\r', self.addr):
            print("Pi Response Received")
            self.define_remote_host("pi")
            return True
        else:
            print("***** Error *****")
            print(" Response Not Recognised\n\n")
            return False

# Extracts data from data requests by working out what data packets have been sent
    def decode_response(self, response):                           # Method for extracting data from
        data, address = response
        ch_data = str(data)
        data_list = ch_data.split("!")
        words = data_list[1]
        ch_group_b = aG.hex_to_binary(words[6:7], 4)      # conversion of data string to
        ch_group_a = aG.hex_to_binary(words[7:8], 4)      # 4 bit binary value returned as a string
        ch_status = ch_group_b + ch_group_a
        print(ch_status)
        ch_list = aG.split(ch_status)
        print(f"DI0:{ch_list[7]}, DI1:{ch_list[6]}, DI2:{ch_list[5]}, DI3:{ch_list[4]}, DI4:{ch_list[3]}, DI5:{ch_list[2]}, DI6:{ch_list[1]}, DI7:{ch_list[0]}")
        return ch_list

    def extract_di_data(self, response):
        print("Method here for extracting Digital Input Data")
        return response

    def extract_ai_data(self, response):
        print("Method here for extracting Analog Input Data")
        return response

    def extract_do_data(self, response):
        print("Method here for extracting Current Digital Output States")
        return response

# Utilities
# Defines if remote host is ADAM or Raspberry Pi
    def define_remote_host(self, host_type):    # defines if remote host is ADAM controller or Raspberry Pi
        if host_type == "adam":
            self.i_am_adam = True
            self.i_am_pi = False
            return True
        elif host_type == "pi":
            self.i_am_pi = True
            self.i_am_adam = False
            return True
        else:
            print("Unknown Host, check remote device")
            return False

    def check_connected_status(self):
        if self.connected:
            return True
        else:
            return False


# Specific Methods

    def get_device_info(self):
        self.s.sendto(DEVICE_INFO, self.addr)
        response = self.s.recvfrom(self.buf)
        print(response)
        return response

    def set_all_low(self):
        print("All Channels Low")
        self.s.sendto(ALL_LOW, self.addr)
        response = self.s.recvfrom(self.buf)
        print(response)


# Pi Specific Methods
    def get_do_state(self):
        self.s.sendto(GET_DO, self.addr)
        print("method to send command to return Digital Output State")



# Example to control ADAM controller

def main():
    while True:
        print("Start Loop")
        counter = 0
        adam_DO = adamConnect(ADAM_6052_IP, PORT)
        print("finished adamConnect")
        connected = adam_DO.open_socket()
        print(f"Connected = {connected}")
        adam_DO.set_do_state(0, 1)
        while connected:
            print("reading DI state..")
            connected = adam_DO.read_di_state()
            print(connected)
            time.sleep(5)
            print(str(counter) + "\n")
            counter += 1
        print("Connection May Have Been Lost, Retrying Connection...")
        time.sleep(2)


main()














'''


s.sendto(all_high, addr)
response = s.recvfrom(buf)
print(response)
time.sleep(5)

s.sendto(all_low, addr)
response = s.recvfrom(buf)
print(response)

'''

'''
7.4.5 Universal I/O Command Set from page 141

Set digital output status
Description This command sets a single or all digital output channels to the specific
ADAM-6000 module.
Syntax #aabb(data)(cr)
# is a delimiter.
aa (range 00~FF) is the 2-character hex slave address of the specified module (always 01)
bb specifies which channel(s) you want to set
Write to all channels (byte): Both characters should be equal to 0 (BB=00)
Write to a single channel (bit): The first character is 1, the second character
indicates the channel number (range 0h~Fh)
(data) is the hex representation of the digital output value(s)
Write to a single channel (bit): The first character is always 0, the second
character is either 0 or 1
Write to all channels (byte): the binary equivalent of these hex values represents the channel values
137 ADAM-6000 User Manual
Chapter 7 Planning Your Application Program
$aaJCFFFFssmm
Response >(cr) if the command is valid
?aa(cr) if an invalid command was entered
There is no response if the module detects a syntax error, communication
error, or if the address does not exist
> is a delimiter indicating a valid command was received
? is a delimiter indicating the command was invalid
aa (range 00~FF) is the 2-character hex slave address of the responding
module
(cr) is the terminating character, carriage return (0Dh)
Example command: #011201(cr)
response: >(cr)
An output bit with value 1 is sent to Channel 2 of the digital output module at
Address 01h.
Channel 2 of the digital output module is thus set to ON.
command: #010012(cr)
response: >(cr)
An output byte with value 12h (00010010) is sent to the digital output module
at Address 01h. Thus, Channels 1 and 4 will be set to ON, and all other channels will be set to OFF.



http://advdownload.advantech.com/productfile/Downloadfile4/1-1M99LTH/ADAM-6000_User_Manaul_Ed_9.pdf pg 106
Function Code 05
Forces a single coil to either ON or OFF. The requested ON/OFF state is specified by
a constant in the query data field. A value of FF 00 (hex) requests it to be ON; a value
of 00 00 (hex) requests it to be OFF; a value of FF FF (hex) requests the forced value
to be released.
Request message format:
Example: Force Coil 3 (Address 00003) to ON in an ADAM-6000 module.
01 05 00 03 FF 00
Response message format:
The normal response is an echo of the query, returned after the coil state has been
forced.
'''