/*   adamController.h

  arduino/c++ library for control of generic Advantech Data Aquisition Modules (ADAM-xxxx) 


*/

#pragma once

#ifndef adamController_h
#define adamController_h

#include <Ethernet.h>
#include <ArduinoRS485.h>  // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class adamController {


private:

  

  EthernetClient ethClient;
  IPAddress serverIP;
  ModbusTCPClient modbusTCP;

public:

  // Constructor

  adamController(EthernetClient client, IPAddress server)
    : ethClient(client),
      serverIP(server),
      modbusTCP(ethClient) {
  }

  // Constants

  const int d_out[8] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 };
  const int d_in[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

  // Methods

  void begin();

  void check_modbus_connect();

  int set_coil(int coilNum, bool coilState = false);
  int set_coils(uint8_t coilStates = 0b00000000);

  bool read_digital_input(uint8_t inputNum);
  uint8_t read_digital_inputs();


  // Variables

  bool modbusConnected = false;
};


#endif