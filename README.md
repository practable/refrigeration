# Remote Labs Refigeration Experiment


## Outline
This system is to allow automation of a refrigeration teaching experiment, using COTS (commercial off the shelf) industrial automation controllers, 
controlled via Arduino Mega and ModBusTCP protocol.
## System P&ID
![image](https://github.com/practable/refrigeration/assets/97303986/fb311af3-5c09-40ce-975f-c99266231b8e)
## Hardware
- Refrigeration Experiment:
	- 7x Solenoid Valves (24v)
	- Compressor (240VAC)
	- 2x Fans (240VAC)
	- 3x Pressure Sensors (Voltage 1-6 v)
	- 5x Temperature Sensors (Voltage 0-10v)
	- Flow Meter (Current 4-20mA)
	- Power Meter (Current 4-20mA)
	- Ambient Pressure Sensor (to be added)
	- Ambient Temperature Sensor (to be added)
	- Thermocouple to track compressor temperature (to be added)

- Electronics:
	- Arduino Mega 2560 development board
	- [Arduino Ethernet Shield 2](https://uk.rs-online.com/web/p/shields-for-arduino/8732285?gb=s)
	- 2x [ADAM 6052 Advantech Data Aquisition Module (DIO)](https://www.impulse-embedded.co.uk/products/adam_6052--Ethernet-Digital-IO-Module.htm) 
	- 2x [ADAM 6271 Advantech Data Aquisition Module (AI)](https://www.impulse-embedded.co.uk/products/adam_6217--Ethernet-Analog-Input-Module.htm)
	- Network Switch
	- 3x DPDT Relays, 24v coil, 240VAC Switching
	- SBC (Single Board Computer) Raspberry Pi/Odroid or similar
	
## Firmware
1. Complete Firmware is found in the `fw` directory within this repo
2. Open `refrigerationFirmware.ino` in a suitable IDE ([Arduino IDE 2.2.1 reccomended](https://www.arduino.cc/en/software))
3. Plug Arduino into PC and select correct board in IDE.
4. Press `Upload` sketch to flash firmware.

## Connecting Automation Hardware
* For detailed wiring diagram see ******

5. Arduino Ethernet sheild can now be mated to Arduino Mega 2560 development board
6. Connect Arduino Mega 2560 to SBC using USB cable
7. Connect Arduino Ethernet Shield to Network Switch using Ethernet Cables
8. Connect 4x ADAM modules to Network Switch using Ethernet Cables


## Controlling Experiment
The experimental hardware can now be controlled using JSON formatted commands sent over Serial USB or UART connection to the Arduino.

### Features:
- Arduino will report system status including all sensor data every 1000mS in JSON format

## Running Experiment (Example Commands)
To setup experiment for basic operation, use the following commands:

### Starting Experiment

1. Open Valves 5 & 6
```
"{"valve":5, "state":1}"
"{"valve":6, "state":1}"
```
2. Select one of Expansion Valves 1-4
	- V1: Thermostatic Expansion valve - self regulating
	- V2: Short Capillary
	- V3: Medium Capillary
	- V4: Long Capillary
```
"{"valve":1, "state":1}"
```

3. Turn on Fans
```
"{"fans":1}"
```

4. Turn on Compressor
```
"{"comp":1}"
```

5. Wait for system to reach homostasis and record efficiency data

#### Selecting Another Expansion Valve

6. Turn off Compressor
```
"{"comp":0}"
```
7. Close open Expansion Valve
```
"{"valve":1, "state":0}"
```

8. Select a different Expansion Valves 1-4
	- V1: Thermostatic Expansion valve - self regulating
	- V2: Short Capillary
	- V3: Medium Capillary
	- V4: Long Capillary
```
"{"valve":2, "state":1}"
```

10. Wait for system to reach homostasis and record efficiency data


### Ending Experiment

11. Turn off Compressor
```
"{"comp":0}"
```

12. Turn off Fans
```
"{"fans":0}"
```

13. Close Expansion Valve
```
"{"valve":4, "state":0}"
```

14. Close valves 5 & 6
```
"{"valve":5, "state":0}"
"{"valve":6, "state":0}"
```
15. Ensure that Flow is at 0 and system can be safely powered down

### Safe Shutdown

_Experiment can be stopped at any time using the mode:stop command_
	- Powers off Compressor
	- Powers off Fans
	- Closes all open valves
```
"{"mode":"stop"}"
```


## Commands List
_list of suitable commands (Examples, not exhaustive)_
```
"{"valve":1, "state":0}"
"{"valve":2, "state":0}"
"{"valve":3, "state":0}"
"{"valve":4, "state":0}"
"{"valve":5, "state":0}"
"{"valve":6, "state":0}"
"{"valve":7, "state":0}"

"{"valve":1, "state":1}"
"{"valve":2, "state":1}"
"{"valve":3, "state":1}"
"{"valve":4, "state":1}"
"{"valve":5, "state":1}"
"{"valve":6, "state":1}"
"{"valve":7, "state":1}"

"{"fans":0}"
"{"fans":1}"
  
"{"comp":0}"
"{"comp":1}"

"{"mode":"stop"}",

"{"cmd":"fans","param":0}"  
 
```

## Engineering Commands
_Note: Only to be used by qualified technicians_

1. Enter Regas mode:
	- Opens all valves except V7
	- Powers on Expansion Fans
	- Powers on Compressor
	- Notifies user over Serial interface the filling procedure (1.1kg of refrigerant OR untill sight glass is full)
```
  "{"mode":"regas"}"
```
2. To exit regas mode, navigate to stop mode
```
  "{"mode":"stop"}"
```
Experiment can then be operated as normal

