
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


*/

#include "globals.h"


void setup() {
  Serial.begin(115200);
  delay(1000);
  print_program_info();

  // ethernet_begin();
  //  adams_begin();
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
}