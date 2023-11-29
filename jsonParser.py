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





https://www.w3schools.com/python/python_json.asp

"""

import json
import acUnitGlobals as glbs




## Proposed command set
json_commands = {
    "set" : {
        "V1" : 0,
        "V2" : 0,
        "V3" : 0,
        "V4" : 0,
        "V5" : 0,
        "V6" : 0,
        "V7" : 0,
        "V8" : 0,
        "W1" : 0,
        "W2" : 0,
        "comp" : 0,
        "fans" : 0
    },
    "get" : {
        "data" : 0,
        "valves" : 0,
        "sensors" : 0
    },
    "change" : 0
}

test_command = '{"cmd": "set", "V1": "open", "v2":"ON", "V3":"OPEN", "comp":"OFF", "w1":"true", "w2":"close"}'
test_2 = '{"cmd": "change", "state":5}'
test_3 = '{"cmd":"get"}'
test_4 = '{"cmd":"change", "state": "manual"}'

'''
JSON Command -> output
if command is "set" "item" "status:
    return "set" "item" "status"    
if command is "get"
    return "get"
if command is "change" "new-state"
    return "new-state"

this will be input into the state machine controller to change/set the state

'''

class jsonParser:
    def __init__(self):
        #self.data_dic = glbs.acUnit_dictionary
        #self.json_template = json.dumps(self.data_dic, indent=2)
        self.valve_list = glbs.valve_list
        self.relay_list = glbs.relay_data_list
        self.outputs_list = glbs.outputs_list
        self.ps_list = glbs.ps_list
        self.ts_list = glbs.ts_list
        self.sense_misc_list = glbs.sense_misc_list
        self.history_param_list = glbs.sensor_param_list
        self.error_list = glbs.status_list
        self.true_words = ["open", "opened","on",  "true", "high","start"]    ## list all words that could mean true
        self.false_words = ["close" ,"shut" ,"closed" ,"off" ,"false" ,"low" ,"stop"]

        #print(self.json_template)




    def parse_json(self, json_string):
        if (json_string):
            print(f"jsonParse: JSON String: {json_string}")
            #TODO WHY PROGRAM HANGS NEAR HERE WHEN SENDING COMMAND {"cmd":"set","fans":"on"}
            #json_string = json_string.replace("\n", " ").replace("\r", " ")
            try:
                command_dic = json.loads(json_string)
            except ValueError:
                glbs.update_error_status(1, "jsonParse: Error: ValueError Unknown JSON string")
                print("jsonParse: Error: ValueError Unknown JSON string")
                return 1
            ## function to make all values lowercase
            try:
                command_dic = {key.lower(): val.lower() for key, val in command_dic.items()} ## Using dict comprehension (memory intensive?)
                #print(f" Command Dic: {command_dic}")
                cmd = command_dic.get("cmd")   ## NOTE better method for extracting from dictionary
            except:
                print(f"jsonParse: Error Extracting cmd from JSON")
                glbs.update_error_status(1, "jsonParse: Error: ValueError Unknown JSON string")
                return 1
            #print(f" cmd: {cmd}")
            if (cmd == "set"):
                #print("Set Command Received")
                #TODO RETURN KEYS THEN CHECK AGAINST OUTPUT LISTS - DONE
                key_list = list(command_dic.keys())
                if any(x.lower() in key_list for x in self.outputs_list) or any(x.upper() in key_list for x in self.outputs_list):
                    print("jsonParse: key exists")
                else:
                    print("jsonParse: KEY DOES NOT EXIST")
                    glbs.update_error_status(3, f"jsonParse: keys:{key_list} do not exist. Unable to parse json Message")
                #TODO Do not like the function of below - iterates through all named inputs and checks if any value in the command dictionary matches it
                #clunky
                for output in self.outputs_list:
                    #print(f"checking output: {output}")
                    # This will only look for items with defined names, if other names are used no error return but also no unexpected function
                    #TODO THIS NEED TO RETURN ERROR IF NAME NOT MATCHED
                    state = command_dic.get(output.casefold())
                    #print(f"{output} State: {state}")
                    if state == None:
                        #print(f"{state} Value Found for {output} ")
                        continue
                    else:
                        state = state.lower()
                    if state in [x.lower() for x in self.true_words] or state == True:
                        glbs.command_queue.append(output)
                        glbs.command_queue.append(True)
                        glbs.command_received = True
                    elif state in [x.lower() for x in self.false_words] or state == False:
                        glbs.command_queue.append(output)
                        glbs.command_queue.append(False)
                        glbs.command_received = True
                    else:
                        glbs.update_error_status(2, f"jsonParse: Error: No Value found for: {cmd}:{output}:{state}")
                        return 2
                return(0)
            elif (cmd == "get"):
                print("jsonParse: Get Command Received")
                return 3
            elif (cmd == None):
                glbs.update_error_status(4, "jsonParse: Error: cmd returned NoneType")
                return 4
            else:
                glbs.update_error_status(5, "jsonParse: Error: Unable to Parse JSON cmd")
                return 5
        else:
            return 6

    def user_input_json(self):
        try:
            user_input = input('\nPlease Input JSON command. Format: {"cmd":"set","V1":"open"}\n')
            response = self.parse_json(user_input)
            #print(response)
            return response
        except:
            print("user-input cancelled")






    def dump_json(self, dictionary):
        self.json_template = json.dumps(glbs.acUnit_dictionary, indent=2)
        print(self.json_template)
        return self.json_template








def main():
    parse = jsonParser()
    #parse.parse_json(test_command)
    parse.user_input_json()






if __name__ == "__main__":
    main()
    print("Program Quit")




