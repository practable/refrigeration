# Remote Labs Refrigeration Experiment


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

_Note: Before starting experiment ensure that manual valves V9 and V10 (to be fitted) are OPEN_

1. Open Valves 5 & 6
```
{"valve":5, "state":1}
{"valve":6, "state":1}
```
2. Select one of Expansion Valves 1-4
	- V1: Thermostatic Expansion valve - self regulating
	- V2: Short Capillary
	- V3: Medium Capillary
	- V4: Long Capillary
```
{"valve":1, "state":1}
```

3. Turn on Fans
```
{"fans":1}
```

4. Turn on Compressor
```
{"comp":1}
```

5. Wait for system to reach homostasis and record efficiency data

#### Selecting Another Expansion Valve

6. Turn off Compressor
```
{"comp":0}
```
7. Close open Expansion Valve
```
{"valve":1, "state":0}
```

8. Select a different Expansion Valves 1-4
	- V1: Thermostatic Expansion valve - self regulating
	- V2: Short Capillary
	- V3: Medium Capillary
	- V4: Long Capillary
```
{"valve":2, "state":1}
```

10. Wait for system to reach homostasis and record efficiency data


### Ending Experiment

11. Turn off Compressor
```
{"comp":0}
```

12. Turn off Fans
```
{"fans":0}
```

13. Close Expansion Valve
```
{"valve":4, "state":0}
```

14. Close valves 5 & 6
```
{"valve":5, "state":0}
{"valve":6, "state":0}
```
15. Ensure that Flow is at 0 and system can be safely powered down

### Safe Shutdown

_Experiment can be stopped at any time using the mode:stop command_
	- Powers off Compressor
	- Powers off Fans
	- Closes all open valves
```
{"mode":"stop"}
```


## Commands List
_list of suitable commands (Examples, not exhaustive)_
```
{"valve":1, "state":0}
{"valve":2, "state":0}
{"valve":3, "state":0}
{"valve":4, "state":0}
{"valve":5, "state":0}
{"valve":6, "state":0}
{"valve":7, "state":0}

{"valve":1, "state":1}
{"valve":2, "state":1}
{"valve":3, "state":1}
{"valve":4, "state":1}
{"valve":5, "state":1}
{"valve":6, "state":1}
{"valve":7, "state":1}

{"fans":0}
{"fans":1}
  
{"comp":0}
{"comp":1}

{"mode":"stop"}
{"mode":"quick"}

{"cmd":"fans","param":0}  
 
```
## JSON Report
_The system will report all sensor values and status in the following format:
```
"{
  "timestamp" : 15260,
  "valves" : {
    "V1" : 0,
    "V2" : 0,
    "V3" : 0,
    "V4" : 0,
    "V5" : 0,
    "V6" : 0,
    "V7" : 0,
    "V8" : 0,
  },
  "relays" : {
    "W1" : 0,
    "W2" : 0,
    "comp" : 0,
  },
  "sensors" : {
    "pressure" : {
      "PS1" :  -2.04,
      "PS2" :  -6.00,
      "PS3" :  -6.00,
    },
    "temperature" : {
      "TS1" :   0.00,
      "TS2" :   0.00,
      "TS3" :   0.00,
      "TS4" :   0.00,
      "TS5" :   0.00,
    },
    "misc" : {
      "flow" :   0.00,
      "power" :   0.00,
      "TSA" :   0.00,
      "PSA" :   0.00,
      "HSA" :   0.00,
    }
  },
"status" : {
    "ok" : 1,
    "state" : "STATE_WAIT",
    "code" : 0,
    "message" : " "
  }
}"

```
Additionally, some errors are also sent as standalone message in the following format, These messages are mostly used during the debugging process and are not expected to be seen during normal operation,
though they may be seen on a reboot and errors could indicate that the system is not plugged in correctly to the ADAM Industrial Controllers or other periferal hardware.
```
{"model":"frig00","version":"refrigerationFirmware-V1.1.2"}
{"error":"Arduino: Ethernet cable is not connected."}
{"error":"ADAM-6052-A: Modbus TCP Client failed to connect!"}
{"error":"ADAM-6052-B: Modbus TCP Client failed to connect!"}
{"status":"BME280:0"}
{"error":" BME280 Error"}
 
{"error":"ADAM-6052-A: Modbus TCP Client failed to connect!"}
{"error":"ADAM-6052-B: Modbus TCP Client failed to connect!"}
{"error":"ADAM-6217-C: Modbus TCP Client failed to connect!"}
{"error":"ADAM-6217-D: Modbus TCP Client failed to connect!"}``

```

## Engineering Commands
_Note: Only to be used by qualified technicians_

1. Enter Regas mode:
	- Opens all valves except V7
	- Powers on Expansion Fans
	- Powers on Compressor
	- Notifies user over Serial interface the filling procedure (1.1kg of refrigerant OR untill sight glass is full)
```
  {"mode":"regas"}
```
2. To exit regas mode, navigate to stop mode
```
  {"mode":"stop"}
```
Experiment can then be operated as normal

## Maintainance & long Term Storage

- System MUST be run for 5 minutes at least once per week to ensure proper distribution of refrigerant and prevent compressor damage

- For long term storage follow long term storage procedure

### Long Term Storage Procedure
_To avoid migration of refrigerent fluid into the compressor during storage, fluid must be pumped into reciever._
Note: This is due to solenoid valves allowing small flow of refrigerent over time, manual valves do not.

1. Shut all solenoid valves (1-6) and manual valves (7, 8, 9, 10) (V9 7 V10 to be fitted)
2. Open valve V6
3. Open Manual Valve 10 (to be fitted)
4. Open Solenoid Valve V6
5. Run compressor until LP Pressure switch trips and shuts off compressor.
6. Close Manual V10
7. Close Solenoid V6
8. Power off compressor

System is now safed for long term storage.

### Recommissioning Procedure
To re-commission equipment undertake the following procedure:

1. Open V9
2. Open V10
3. Open V5
4. Open Valves V1-4
5. Start Fans
6. Allow pressure to equalise between High pressure & Low pressure sides `P3 ~= P1`
7. Open Valves V6
8. Close V1-3
10. Start compressor and run experiment for ~30 mins to ensure correct function
11. Shut down system as normal, ensuring that manual valves V9 and V10 remain in the open position.
