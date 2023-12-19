/*  adamController.cpp

  arduino/c++ library for control of generic Advantech Data Aquisition Modules (ADAM-xxxx) 


*/


#include "adamController.h"


#define DEBUG true


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
  uint8_t state;
  if (coilState) {
    state = 0x01;
  } else {
    state = 0x00;
  }

  char buffer[64];

  if ((coilNum >= 0) && (coilNum < 8)) {
    if (!modbusTCP.coilWrite(0x10, state)) {
      sprintf(buffer, "Failed to set coil: %i ( %#0x ) to %i. %s", coilNum, d_out[coilNum], coilState, modbusTCP.lastError());
      // Serial.println(modbusTCP.lastError());
    } else {
      sprintf(buffer, "Setting Coil: %i ( %#0x ) to %i", coilNum, d_out[coilNum], coilState);
    }
  } else {
    sprintf(buffer, "Unable to set Coil %i - out of range :(", coilNum);
  }
#if DEBUG == true
  Serial.println(buffer);
#endif
}





int adamController::set_coils(uint8_t coilStates = 0b00000000) {
}



bool adamController::read_digital_input(uint8_t inputNum) {
}



uint8_t adamController::read_digital_inputs() {
}
