#!/usr/bin/env python3
'''
Manual Server

 Test server for websockets. Broadcast a JSON command following user input
https://realpython.com/python-sockets/
'''


# broadcastServer.py


import socket
import time
import json
import acGlobals as glbs
pack = glbs.jsonPack

#HOST = "127.0.0.1"
#TESTHOST = "10.42.0.1"
#HOST = TESTHOST
HOST = glbs.COMMAND_SERVER_IP
PORT = glbs.COMMAND_PORT

TEST_COMMAND = '{"cmd":"set", "V1":"open"}'

exceptions = 0


def input_cmd():
    print("get USR input")
    

while(exceptions < 2):
    stop = False
    try:
        print(f"Starting acUnit Command Test Server:\nListening on {HOST}:{PORT}")
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.bind((HOST, PORT))
            while (stop == False):
                s.listen()
                conn, addr = s.accept()
                with conn:
                    iteration = 0
                    while(conn):
                        print(f"Connected by {addr}")
                        json_valid = True
                        try:
                            json_input = input(f"\nPlease Enter JSON command in format: {TEST_COMMAND}\n\n")
                            try:
                                json_obj = json.loads(json_input)
                            except ValueError:
                                print("JSON format Not Recognised")
                                json_valid = False
                        except:
                            print("User Input Escaped - Closing Server")
                            stop = True
                        #print(iteration)
                        print(f"JSON Valid? {json_valid}")
                        if stop == False and json_valid == True:
                            #print("Sending a command you cant stop me")
                            json_command = json_input.encode("UTF-8")
                            conn.sendall(json_command)
                            data = conn.recv(2048)
                            try:
                                reply = int(data.decode())
                            except ValueError:
                                print("non integer ack reply (likely due to testing half built client) ignore error codes from next few lines")
                            print(f"Returned Value: {reply}")
                            if (reply == 0):
                                print("Command Successfully Sent")
                            else:
                                print(f"Error Returned Code: {data}")
                            if not data:
                                print("No Data Rx - break")
                                break
                        #data_dic = pack.unpack_json(data)
                        #json_print = pack.dump_json()
                        #print(data_dic)
                        else:
                            print("else")
                        iteration += 1
                        if (stop):
                            break
                        #time.sleep(1)
    except ConnectionResetError:
        print("Caught Connection Reset Error: Likely Cause Client Drop Connection")
        print("Restarting")
    except KeyboardInterrupt:
        print("Caught keyboard interrupt, exiting")
        break
    except Exception as ex:  ## generic exception handler
        glbs.generic_exception_handler(ex)
        print("Exception Handled, restarting")
        exceptions += 1
print("Program Quit")








