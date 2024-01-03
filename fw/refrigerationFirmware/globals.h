/*   globals.h

Global variables for Refrigeration Experiment


*/

#pragma once

#ifndef globals_h
#define globals_h

#include "ArduinoJson-v6.9.1.h"
#include "adamController.h"
#include "sensorObj.h"

#define DEBUG true

#define NUM_TEMP_SENSORS 5

sensorObj temp_s[NUM_TEMP_SENSORS] = {
  sensorObj(VOLTAGE_SENSOR, "degC", "TS1"),
  sensorObj(VOLTAGE_SENSOR, "degC", "TS2"),
  sensorObj(VOLTAGE_SENSOR, "degC", "TS3"),
  sensorObj(VOLTAGE_SENSOR, "degC", "TS4"),
  sensorObj(VOLTAGE_SENSOR, "degC", "TS5")
};

// Arrays for Sensor Vals
  float ts_vals[NUM_TEMP_SENSORS] = {0.0,0.0,0.0,0.0,0.0};               // create array for TS data 
  uint32_t ts_times[NUM_TEMP_SENSORS] = {1000,1000,1000,1000,1000};         // create array for TS timestamps


#define NUM_PRESSURE_SENSORS 3
sensorObj pressure_s[NUM_PRESSURE_SENSORS] = {
  sensorObj(VOLTAGE_SENSOR, "bar", "PS1"),
  sensorObj(VOLTAGE_SENSOR, "bar", "PS2"),
  sensorObj(VOLTAGE_SENSOR, "bar", "PS3")
};

// Arrays for Sensor Vals
  float ps_vals[NUM_PRESSURE_SENSORS] = {0.0, 0.0, 0.0};              // create array for TS data 
  uint32_t ps_times[NUM_PRESSURE_SENSORS] = {1000,1000,1000};         // create array for TS timestamps

sensorObj power_s(CURRENT_SENSOR, "W", "power");
sensorObj flow_s(CURRENT_SENSOR, "flow", "flow");

sensorObj t_ambi(CURRENT_SENSOR, "degC", "TS_ambi");
sensorObj p_ambi(CURRENT_SENSOR, "mBar", "PS_ambi");

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
// The IP address will be dependent on your local network:
byte mac[] = { 0xA8, 0X61, 0x0A, 0xAE, 0xE1, 0x48 };

//Define the ip address for the client (local modbus controller) (the device this firmware is running on)
IPAddress ip(192, 168, 1, 100);

// Define the IP for the server (remote modbus device)
IPAddress adam6052A_ip(192, 168, 1, 111);  // update with the IP Address of your Modbus server (the remote IO controller)
IPAddress adam6052B_ip(192, 168, 1, 114);  // update with the IP Address of your Modbus server (the remote IO controller)
IPAddress adam6217A_ip(192, 168, 1, 114);  // update with the IP Address of your Modbus server (the remote IO controller)
IPAddress adam6217B_ip(192, 168, 1, 115);  // update with the IP Address of your Modbus server (the remote IO controller)

// Create an Ethernet Client
EthernetClient ethClient;


// Create an adamController object and pass the Ethernet Client and IP Address for the server
adamController adam6052A(ethClient, adam6052A_ip, DAC_OUTPUT, "ADAM-6052-A");
adamController adam6052B(ethClient, adam6052B_ip, DAC_OUTPUT, "ADAM-6052-B");
adamController adam6217A(ethClient, adam6217A_ip, VOLTAGE_OUTPUT, "ADAM-6217-A");
adamController adam6217B(ethClient, adam6217B_ip, DAC_OUTPUT, "ADAM-6217-B");

//adamController adam6024(ethClient, adam6024_ip, DAC_OUTPUT, "ADAM-6024-C");



#endif
