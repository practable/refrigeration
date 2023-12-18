/*  adamController.cpp

  arduino/c++ library for control of generic Advantech Data Aquisition Modules (ADAM-xxxx) 


*/


#include "adamController.h"


void adamController::begin() {
}

void adamController::check_modbus_connect() {

  if (!modbusTCP.connected()) {
    // client not connected, start the Modbus TCP client
    Serial.println("Attempting to connect to Modbus TCP server");
    modbusConnected = false;
    if (!modbusTCP.begin(serverIP, 502)) {
      Serial.println("Modbus TCP Client failed to connect!");

    } else {
      Serial.println("Modbus TCP Client connected");
      modbusConnected = true;
    }
  }
}





int adamController::set_coil(int coilNum, bool coilState) {
      // write the value of 0x01, to the coil at address 0x00
    if (!modbusTCP.coilWrite(0x10, coilState)) {
      Serial.print("Failed to write coil! ");
      Serial.println(modbusTCP.lastError());
    }
}

/*
    // write the value of 0x00, to the coil at address 0x00
    if (!modbusTCPClient.coilWrite(0x10, 0x00)) {
      Serial.print("Failed to write coil! ");
      Serial.println(modbusTCPClient.lastError());
    }
*/

int adamController::set_coils(uint8_t coilStates = 0b00000000) {
}



bool adamController::read_input(uint8_t inputNum) {
}



uint8_t adamController::read_inputs() {
}
