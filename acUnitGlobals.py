'''
 acUnit Global variable and type definitions

'''
import traceback   ## for debugging
import pdb         ## most mortum analysis
import jsonPacker
import jsonParser
import acUnitHardware

# USER OPTIONS
COMMAND_SERVER_IP = "10.42.0.1"
REPORT_SERVER_IP = "10.42.0.1"

#SERVER_IP = "127.0.0.1"

COMMAND_PORT = 65432
REPORT_PORT = 65433

simulate_hardware = False


#Wrap all this inside a class?

acUnitState = "init"

valve_list = ["V1","V2","V3","V4","V5","V6","V7","V8"]
relay_data_list = ["W1","W2","comp"]
fan_names = ["W1","W2", "fans", "fan"]
compressor_names = ["comp", "compressor", "pump"]
outputs_list = valve_list + fan_names + compressor_names
ps_list = ["PS1","PS2","PS3"]
ts_list = ["TS1","TS2","TS3","TS4","TS5"]
sense_misc_list = ["flow", "power", "APS", "ATS"]
#history_param_list = ["dTdt", "average", "least_mean_sqr", "min", "max"]
sensor_param_list = ["val", "min", "max","avg","dxdt", "lms" ]
status_list = ["ok" , "state", "code", "message"]

# Creating Instances of Global Methods here to ensure that only 1 object of each. Can be renamed in local files
acHardware = acUnitHardware.acUnitHardware()
jsonParse = jsonParser.jsonParser()
jsonPack = jsonPacker.jsonPacker()




command_received = False
command_queue = []  ##  queue is processed by state machine untill empty


test_valve_status = [0,0,0,0,0,0,0,0]


import logging

'''
Logging - Explanation
Logging Levels:
DEBUG: Detailed - use when debugging problems
INFO: Confirmation things are working
WARNING: Indication something unexpected happened
ERROR: More serious problem, software has been unable to perform some function
CRITICAL: Serious error indicating software may be unable to continue running

default is WARNING, everything below this level is logged
'''
def init_logging():
    logging.basicConfig(filename='acunit.log', filemode='w', encoding='utf-8', level=logging.DEBUG, format='%(asctime)s %(levelname)-8s %(message)s',
    datefmt='%Y-%m-%d %H:%M:%S')
    logging.info("Logging Module Started")






error_status = [True, 0, ""]
last_error = 0
def update_error_status(error_code=0, error_message= " "):
    global last_error
    logging.error(f"Error:{error_code}: {error_message}")
    if error_code != last_error:
        error_status[0] = False
        error_status[1] += error_code
        error_status[2] += (error_message + ", ")
        last_error =  error_code

'''
  "ok": "True",
        "state": " ",
        "code":0,
        "message":" "
'''



acUnit_dictionary = {
    "valves" : {
        "V1" : 0,
        "V2" : 0,
        "V3" : 0,
        "V4" : 0,
        "V5" : 0,
        "V6" : 0,
        "V7" : 0,
        "V8" : 0
    },
    "power_relays"  :  {
        "W1" : 0,
        "W2" : 0,
        "comp": 0
    },
    "sensors": {
        "pressure":{
            "PS1":  {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            },
            "PS2": {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            },
            "PS3": {
                "val": 0,
                "min": 0,
                "max": 0,
                "avr": 0,
                "dxdt": 0,
                "lms": 0
            },
        }, #end of pressure
        "temperature": {
            "TS1" : {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            },
            "TS2" : {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            },
            "TS3" : {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            },
            "TS4" : {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            },
            "TS5" : {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            }
        },  #end of temperature
        "misc":{
            "flow": {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            },
            "power": {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            },
            "APS" : {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            },
            "ATS" : {
                "val": 0,
                "min": 0,
                "max": 0,
                "avg": 0,
                "dxdt": 0,
                "lms": 0
            }
        } # end of misc
    }, # end of sensors
    "status":{
        "ok": "True",
        "state": " ",
        "code":0,
        "message":" "
    }
}

def generic_exception_handler(ex, location="null "):
    template = "An exception of type {0} occured. Arguments: \n{1!r}"
    message = template.format(type(ex).__name__, ex.args)
    print(message)
    print(" ")
    print(traceback.format_exc())
    logging.exception(f"{location} Generic Exception Handler Triggered: {ex}")
    #pdb.post_mortem()
    print("Program Error")