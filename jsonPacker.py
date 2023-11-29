"""
JSON Parse

Library to parse JSON messages and output state as a string?

# Defining JSON Commands as python dictionary

# SET COMMANDS (ideas)
{"cmd":"set", "V1":"open"}
{"cmd":"set", "V5":"open","V6":"open"}
{"cmd":"set","item":"V1","state":"open"}
{"cmd":"V1", "value":"open"}

{"set":"V1", "state":"open"}

# all these should work
{"set:"V_comp","state":"on"}
{"set:"V_comp","state":1}
{"set:"V_comp","state":"true"}

{"set:"V_comp","state":"off"}
{"set:"V_comp","state":0}
{"set:"V_comp","state:"false"}


# GET COMMANDS
- Get commands for data return entire data packet for all values
{"cmd":"get"} - get all data
{"get":"V1"}
{"get":"all"}



https://www.w3schools.com/python/python_json.asp

"""

import json
import acUnitGlobals as glbs


valves_list = [1,0,1,0,1,0,1,0]
relays_list = [1,0,1]
pressures_list = [10.23, 8.34, 6.25]
temps_list = [20.24,4.34,8.22,24.8,53.67]
miscs_list = [16.3, 200.1, 1024, 20.34]
histories_list = [0.2, 20.3, 5.82, 4.12, 25.23]



class jsonPacker:
    def __init__(self):
        #self.data_dic = glbs.acUnit_dictionary   ## Decision time do we want to update the global variable or keep it local
        #NOTE: CURRENTLY USING GLOBAL VARIABLE
        #glbs.acUnit_dictionary
        #self.json_template = json.dumps(glbs.acUnit_dictionary, indent=2)
        self.valve_list = glbs.valve_list
        self.relay_list = glbs.relay_data_list
        self.ps_list = glbs.ps_list
        self.ts_list = glbs.ts_list
        self.ms_list = glbs.sense_misc_list
        #self.history_param_list = glbs.history_param_list
        self.sensor_param_list = glbs.sensor_param_list
        self.status_list = glbs.status_list

    def dump_json(self):
        json_template = json.dumps(glbs.acUnit_dictionary, indent=2)
        #print(json_template)
        return json_template

    def print_json(self, dic):
        json_print = json.dumps(dic, indent=2)
        print(json_print)
        return json_print


    def unpack_json(self, json_byteobject):
        data_dic = json.loads(json_byteobject)
        return data_dic



    def load_valve_data(self, valve_state_list):
        new_zip = zip(self.valve_list, valve_state_list)  ## zips two lists together into an object of tuples
        new_dic = dict(new_zip)
        glbs.acUnit_dictionary["valves"].update(new_dic)

    def load_relay_data(self, relay_state_list):
        new_zip = zip(self.relay_list, relay_state_list)  ## zips two lists together into an object of tuples
        new_dic = dict(new_zip)
        glbs.acUnit_dictionary["power_relays"].update(new_dic)

    # This method should load all data including history for named sensor #TODO INCOMPLETE
    def load_sensor_data(self, sensor_name, sensor_data):
        new_zip = zip(self.sensor_param_list, sensor_data)
        new_dic = dict(new_zip)
        if sensor_name.lower() in [x.lower() for x in self.ps_list]:
            glbs.acUnit_dictionary["sensors"]["pressure"][sensor_name].update(new_dic)
        elif sensor_name.lower() in [x.lower() for x in self.ts_list]:
            glbs.acUnit_dictionary["sensors"]["temperature"][sensor_name].update(new_dic)
        elif sensor_name.lower() in [x.lower() for x in  self.ms_list]:
            glbs.acUnit_dictionary["sensors"]["misc"][sensor_name].update(new_dic)
        else:
            print("Error: No valid dictionary found for named sensor")
            glbs.update_error_status(1, f'({sensor_name}) load_sensor_data failed')



## This one works now but is kind of depreciated
    def load_pressure_data(self, pressure_list):
        #new_zip = zip(self.ps_list, pressure_list)  ## zips two lists together into an object of tuples
        #new_dic = dict(new_zip)
        i = 0
        for sensor in self.ps_list:
            glbs.acUnit_dictionary["sensors"]["pressure"][sensor]["val"]=(pressure_list[i]) ## no error checking generic method is better, this left in for backwards compatibility
            i +=1      

    def load_temp_data(self, temp_list):
        new_zip = zip(self.ts_list, temp_list)   ## zips two lists together into an object of tuples
        new_dic = dict(new_zip)
        glbs.acUnit_dictionary["sensors-temperature"].update(new_dic)

    def load_misc_data(self, misc_list):
        new_zip = zip(self.ms_list, misc_list)  ## zips two lists together into an object of tuples
        new_dic = dict(new_zip)
        glbs.acUnit_dictionary["sensors-misc"].update(new_dic)


## This is now totally depreciated, sensorObject calculate history changed to return current value as well as historical values
    ## USE LOAD SENSOR DATA
    def load_history_data(self, sensor_name, history_list, ):
        new_zip = zip(self.sensor_param_list, history_list)  ## zips two lists together into an object of tuples
        new_dic = dict(new_zip)
        glbs.acUnit_dictionary["sensors-history"][sensor_name].update(new_dic)

    def load_status_data(self):
        error_list = [glbs.error_status[0], glbs.acUnitState, glbs.error_status[1], glbs.error_status[2]]
        new_zip = zip(self.status_list, error_list)  # zips name together with value
        new_dic = dict(new_zip)
        glbs.acUnit_dictionary["status"].update(new_dic)




def main():
    pack = jsonPacker()
    #pack.load_valve_data(valves_list)
    #pack.load_relay_data(relays_list)
    pack.load_pressure_data(pressures_list)
    #pack.load_temp_data(temps_list)
    #pack.load_misc_data(miscs_list)
    #pack.load_history_data(histories_list, "TS3")
    #pack.load_status_data()
    pack.dump_json()   ##glbs.acUnit_dictionary



if __name__ == "__main__":
    main()
    print("Program Quit")




