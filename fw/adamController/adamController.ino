/*
  Ethernet Modbus TCP Client Toggle

  This sketch toggles the coil of a Modbus TCP server connected
  on and off every second.

  Circuit:
   - Any Arduino MKR Board
   - MKR ETH Shield

  created 16 July 2018
  by Sandeep Mistry
*/

#include <SPI.h>
#include <Ethernet.h>

// These should be depreciated
//#include <ArduinoRS485.h>  // ArduinoModbus depends on the ArduinoRS485 library
//#include <ArduinoModbus.h>

#include "adamController.h"  // Now all modbus is handled internally to adamController class

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
// The IP address will be dependent on your local network:
byte mac[] = {
  0xA8, 0X61, 0x0A, 0xAE, 0xE1, 0x48
};

//Define the ip address for the client (local modbus controller) (the device this firmware is running on)
IPAddress ip(192, 168, 1, 100);

// Define the IP for the server (remote modbus device)
IPAddress server(192, 168, 1, 111);  // update with the IP Address of your Modbus server (the remote IO controller)

// Create an Ethernet Client
EthernetClient ethClient;
// Create a Modbus client passing the ethernet client as argument
//ModbusTCPClient modbusTCPClient(ethClient);  DEPRECIATED (now inside class)
// Create an adamController object and pass the Ethernet Client and IP Address for the server
adamController adam6052(ethClient, server);






void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1);  // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  adam6052.begin();
}





void loop() {

  adam6052.check_modbus_connect();

  if (adam6052.modbusConnected) {

    int error = adam6052.set_coil(0, true);

    delay(2000);

    error = adam6052.set_coil(0, false);

    delay(2000);

    // if client connected
  }
}
