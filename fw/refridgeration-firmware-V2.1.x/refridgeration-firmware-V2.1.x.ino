
/*   refrigeration firmware Version 2.1.x


-> Old version was running low on memory, porting to new practable-core framework

*/


/*  Changelog

V2.1.0
Sketch uses 33924 bytes (13%) of program storage space. Maximum is 253952 bytes.
Global variables use 6119 bytes (74%) of dynamic memory, leaving 2073 bytes for local variables. Maximum is 8192 bytes.
- No memory Warning
- jsonMessenger devolved parsing function proof of concept (expand out to each datatype + add new entry for DUAL_INT)
- States need implementing copying previous implementation

V2.1.1
Sketch uses 45292 bytes (17%) of program storage space. Maximum is 253952 bytes.
Global variables use 6155 bytes (75%) of dynamic memory, leaving 2037 bytes for local variables. Maximum is 8192 bytes.
- Memory Warning
- Crashing



*/

#include "globals.h"

#define ADAM6052A_ACTIVE false
#define ADAM6052B_ACTIVE false
#define ADAM6217C_ACTIVE false
#define ADAM6217D_ACTIVE false
#define I2C_ACTIVE false

#define SAMPLING_DELAY 500
#define JSON_REPORT_DELAY_mS 1000
#define BUILD_JSON true

void setup() {
  Serial.begin(115200);
  delay(1000);
  print_program_info();

  ethernet_begin();
  adams.adams_begin();
  // sensors_begin();
  Serial.println(F(" "));
}



void loop() {
  jsonRX.jsonReadSerialLoop(nextState_data);  // function needs to be called periodically to accept incoming serial messages, parse & return jsonStateData_t with new state /and data required for new state

  if (nextState_data.cmd_received) {  // If command is receive
                                      // LEDS[0].callBlink(4, 20, 60);

    // This is the bit that parses the command recieved by user, and sets the state machine to go to the correct state
    if (nextState_data.stateEnum != STATE_NULL) {
      sm.change_state(nextState_data.stateEnum);
    }
  }

  sm.sm_Run(nextState_data);

  // Sample all Data inputs
  if (millis() - lastSample >= SAMPLING_DELAY) {
#if ADAM6052A_ACTIVE == true
    adams.check_modbus_connection(ADAM6052_A);
    adams.sample_adam6052A();
#endif
#if ADAM6052B_ACTIVE == true
    adams.check_modbus_connection(ADAM6052_B);
    adams.sample_adam6052B();
#endif

#if ADAM6217C_ACTIVE == true
    adams.check_modbus_connection(ADAM6217_C);
    adams.sample_adam6217C();
#endif
#if ADAM6217D_ACTIVE == true
    adams.check_modbus_connection(ADAM6217_D);
    adams.sample_adam6217D();
#endif
#if I2C_ACTIVE == true
    sample_bme280();
#endif
    lastSample = millis();
    sampleTimestamp = lastSample;  // This takes a "generic" timestamp that should be accurate enough for most purposes
  }

  if (millis() - lastReport >= JSON_REPORT_DELAY_mS) {
    report.print_json();
    lastReport = millis();
  }
}
