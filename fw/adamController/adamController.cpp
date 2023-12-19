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

/*  Anatomy of a ModBus Message


  0x  (in hex)
message prefix
  01  station address
  0F  function code   (01, 02, 03, 04,05, 06, 08, 0f, 10 )
  00  end of prefix
message contents
  10  coil/register address High Byte
  17  coil/register address low byte
  0A  ??
  02  ??
  CD  ??
  01  ??

ASCII Commands
$aaM  = $01M


*/

int adamController::set_coils(uint8_t coilStates = 0b00000000) {

  char buffer[64];
  int16_t response;
  response = modbusTCP.beginTransmission(COILS, 0x10, 0x08);  // type, address (any val) , nb (no bytes to be sent)

  response = modbusTCP.write(coilStates & 0b00000001);
  response = modbusTCP.write(coilStates & 0b00000010);  // Fun bitmasking operation
  response = modbusTCP.write(coilStates & 0b00000100);
  response = modbusTCP.write(coilStates & 0b00001000);
  response = modbusTCP.write(coilStates & 0b00010000);
  response = modbusTCP.write(coilStates & 0b00100000);
  response = modbusTCP.write(coilStates & 0b01000000);
  response = modbusTCP.write(coilStates & 0b10000000);

  response = modbusTCP.endTransmission();
  char binString[9];

  itoa(coilStates, binString, 2);

  Serial.println(int(8 - strlen(binString)));  //%.*d%s  trying some magic to make sprinf work! aaah


  if (response == 1) {
    sprintf(buffer, "Set Coils to: %8s ", binString);
  } else {
    sprintf(buffer, "ERROR: Unable to Set Coils to:  %bi ", coilStates);
  }
//  Serial.println(response);
#if DEBUG == true
  Serial.println(buffer);
#endif
  return true;
}



bool adamController::read_digital_input(uint8_t inputNum) {
  char buffer[64];
  if ((inputNum >= 0) && (inputNum < 8)) {
    int16_t inputState = modbusTCP.discreteInputRead(inputNum);
    if (inputState == -1) {
      sprintf(buffer, "Error Code %i: Unable to Read Input %i :(", inputState, inputNum);
    } else {
      sprintf(buffer, "Input %i Status: %i", inputNum, inputState);
    }
  } else {
    sprintf(buffer, "Unable to Read Input %i - out of range :(", inputNum);
  }

#if DEBUG == true
  Serial.println(buffer);
#endif
  return true;
}

bool adamController::get_output_state(uint8_t outputNum) {
  char buffer[64];
  if ((outputNum >= 0) && (outputNum < 8)) {
    int16_t outState = modbusTCP.coilRead(d_out[outputNum]);
    if (outState == -1) {
      sprintf(buffer, "Error Code %i: Unable to Read Output Status %i :(", outState, outputNum);
    } else {
      sprintf(buffer, "Output %i Status: %i", outputNum, outState);
    }
  } else {
    sprintf(buffer, "Unable to Read Output Status %i - out of range :(", outputNum);
  }

#if DEBUG == true
  Serial.println(buffer);
#endif
  return true;
}


uint8_t adamController::read_digital_inputs() {

  for (int i = 0; i < 8; i++) {
    int16_t outState = modbusTCP.coilRead(d_in[i]);
    Serial.print(outState);
  }
  return 0;
}
