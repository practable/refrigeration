# refrigeration
Refrigeration teaching experiment remote lab


 Current Testing Instructions:
 ## Prerequisits
`Python3` <br>
External modules used: <br>
`pyModbusTCP` <br>
`numpy` <br>
I believe this was all that was nessissary to install to run the software on RPi Ubuntu

## Setup
 1. Ensure that `testCommandServer.py` HOST variable is set to loopback address `127.0.0.1` OR address of server host.
 2. Ensure that `testReportingServer.py` HOST variable is set to loopback address `127.0.0.1` OR address of server host.
 3. Ensure that `commandClient.py` HOST variable is set to same address as server
 4. Ensure that `reportingClient.py` HOST variable is set to same address as server
 5. If testing without hardware, ensure that `simulate_hardware = True` set in `acUnitGlobals.py`
 6. Run `testCommandServer.py` and `testReportingServer.py` on host server
 7. Run `main.py` on client server (raspberrypi/SBC in final implementation) It should connect to server with no issues

## Operation
1. Enter commands as prompted in `testCommandServer.py` CLI. Track changes in state and function using CLI for `main.py`. view logfile during operation for debug messages, based on logging level set in `init_logging` in `acUnitGlobals`
2. Ensure that JSON messages reported by `testReportingServer.py` display "correct" values (if simulated hardware these values somewhat random and static at the moment

## Issues

1. NOTE: 1st command sent from `testCommandServer.py` causes websocket to loose connection & reset. All commands after this should be handled normally.

## Command Examples
`{"cmd":"set","{item}":"{state}"}`

```
{"cmd":"set","V1":"open"}
{"cmd":"set","V2":"open"}
{"cmd":"set","V3":"open"}
{"cmd":"set","V4":"open"}
{"cmd":"set","V5":"open"}
{"cmd":"set","V6":"open"}
{"cmd":"set","V7":"open"}

{"cmd":"set","V5":"open","V6":"open"}
{"cmd":"set","V5":"close","V6":"close"}

{"cmd":"set","V1":"close"}
{"cmd":"set","V2":"close"}
{"cmd":"set","V3":"close"}
{"cmd":"set","V4":"close"}
{"cmd":"set","V5":"close"}
{"cmd":"set","V6":"close"}
{"cmd":"set","V7":"close"}

{"cmd":"set","W1":"on"}
{"cmd":"set","W1":"off"}
{"cmd":"set","W2":"on"}
{"cmd":"set","W2":"off"}
{"cmd":"set","fans":"on"}
{"cmd":"set","fans":"off"}

{"cmd":"set","comp":"start"}
{"cmd":"set","comp":"stop"}

All the following words evaluate to True:
"open","opened","on","true","high","start"

All the following words evaluate to False:
"close","shut","closed","off","false","low","stop"
    
```

## Future Commands
download CSV of all datapoints
`{"cmd":"get","item":"csv"}`

safe shutdown
`{"cmd":"set","mode":"shutdown"}`

run experiment with expansion valve Vx
`{"cmd":"set","mode":"V2"}`

![image](https://github.com/ImogenWren/adam-controller/assets/97303986/7265be20-a3c5-4dae-9d01-df3e64b89851)


