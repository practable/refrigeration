/* stateMachine.cpp

Here use the templates to fully define the contents of each state.

Good states should set variables and do things quickly, then exit so the state machine can continue to run.

Blocking states are acceptable if you understand why they will be blocking and account for this within the implementation.

e.g. In these states, the pulse state is blocking while it sends one wave out. This is okay because this event happens very quickly and then exits immediatly


*/

#include "jsonStateMachine.h"

#include "globals.h"
#include "jsonReporter.h"

// #include "jsonStateData.h"
//  #include "jsonError.h"
//  #include "ArduinoJson.h"
//
//  #include "globals.h"

// #define DEBUG_STATES true

stateMachine::stateMachine() {}

stateDef_t stateMachine::get_state() { return smState; }

void stateMachine::sm_state_null(jsonStateData_t &stateData) {
    Serial.println(F("ERROR: NULL STATE!"));
    stateData.uintData++;
    smState = STATE_WAIT;
}

// Init state, only called at startup
void stateMachine::sm_state_init(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println("state: INIT");
#endif
        stateData.uintData++;
        lastState = smState;
    }

    smState = STATE_WAIT;
}

// State Wait is the default state for this program
void stateMachine::sm_state_wait(jsonStateData_t &stateData) {
    if (lastState != smState) {
        stateData.uintData++;
        // If first iteration print state machine status
#if DEBUG_STATES == true
        Serial.println(F("state: WAIT"));
#endif
#if COMMAND_HINTS == true // print suggested commands
        Serial.println(F("\nEnter cmd in format:"));
        jsonRX.print_cmds();
#endif
        lastState = smState;
    }
}

// stop compressor, after delay, close valves
void stateMachine::sm_state_stop(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: STOP"));
#endif
        // Serial.print("abs_diff: ");
        // Serial.println(absDiff(0.0, stateData.floatData));
        lastState = smState;
    }
    smState = STATE_WAIT;
}

// Dont know if needed any longer
void stateMachine::sm_state_running(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: RUNNING"));
#endif
        lastState = smState;
    }
    stateMachine::change_state(STATE_WAIT);
    //  smState = STATE_WAIT;
}

// Set Valve to State
void stateMachine::sm_state_valve(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: VALVE"));
#endif
        if (stateData.uintData > 0 && stateData.uintData <= 7) {
            adams.set_DO(ADAM6052_A, (stateData.uintData - 1), stateData.intData);
        } else {
            error.json_error("ERROR", "Valve Number Out of Bounds");
        }
        lastState = smState;
    }
    // stateMachine::change_state(STATE_WAIT);  // this function only needed outside of library
    smState = STATE_WAIT;
}

// Set compressor state
void stateMachine::sm_state_comp(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: COMP"));
#endif
        // stateData.uintData++;

        lastState = smState;
    }
    smState = STATE_WAIT;
}

enum ADAM6052_B_DO { ADAM6052B_COMP = 0, ADAM6052B_COND = 1, ADAM6052B_EVAP = 2, ADAM6052B_LAMP = 3 };

// set lights state
void stateMachine::sm_state_lights(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: LIGHTS"));
#endif
        // stateData.uintData++;
        Serial.println(stateData.boolData);
        adams.set_DO(ADAM6052_B, ADAM6052B_LAMP, stateData.boolData);
        lastState = smState;
    }
    smState = STATE_WAIT;
}

// set both fans state
void stateMachine::sm_state_fans(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: FANS"));
#endif

        lastState = smState;
    }
    smState = STATE_WAIT;
}

// set the state of the evaporation fan
void stateMachine::sm_state_evap(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: EVAP"));
#endif

        lastState = smState;
    }
    smState = STATE_WAIT;
}

// set the state of the condensing fan
void stateMachine::sm_state_cond(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: COND"));
#endif

        lastState = smState;
    }
    smState = STATE_WAIT;
}

// set both fan speeds to the same value
void stateMachine::sm_state_fanspeed(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: FANSPEED"));
#endif

        lastState = smState;
    }
    smState = STATE_WAIT;
}

// set the speed of the evaporation fan
void stateMachine::sm_state_evapspeed(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: EVAPSPEED"));
#endif

        lastState = smState;
    }
    smState = STATE_WAIT;
}

// Set the speed of the condensing fan
void stateMachine::sm_state_condspeed(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: CONDSPEED"));
#endif

        lastState = smState;
    }
    smState = STATE_WAIT;
}

// enter regas state (what does this mean rn?)
void stateMachine::sm_state_regas(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: REGAS"));
#endif

        lastState = smState;
    }
    smState = STATE_WAIT;
}

// set up fridge with default working values (what does this mean?)
void stateMachine::sm_state_quickstart(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("state: QUICKSTART"));
#endif
        Serial.println(stateData.msg);
        lastState = smState;
    }
    smState = STATE_WAIT;
}

// Change the samplerate of streamed or snapshotted data (Init at 10 Hz)
void stateMachine::sm_state_samplerate(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("st: SAMPLERATE"));
#endif
        error.json_error("WARNING", "Sample Rate Update Disabled");
        lastState = smState;
    }
    if (stateData.uintData < 1 || stateData.uintData > 200) {
        // errors.set_error(false, -10, "Out of Bounds Sample Rate Commanded", errors.WARNING, "state-samplerate");
        //  errors.print_json_status();
        // } else if (stateData.uintData < print_rate_Hz) {
        //  errors.set_error(false, -10, "Cannot set sample rate less than print rate", errors.WARNING, "state-samplerate");
        //  errors.print_json_status();
    } else {
        //   sampleRate_Hz = stateData.uintData;
        // sampleDelay_mS = 1000 / sampleRate_Hz;
        //   sampleDelay_mS = 1E3 / sampleRate_Hz - SAMPLE_DELAY_OFFSET;
        //   num_samples_req = uint8_t(sampleRate_Hz / print_rate_Hz);  // Number of samples required to collect between each print cycle
    }
    smState = STATE_WAIT;
}

// Change the samplerate of streamed or snapshotted data (Init at 10 Hz)
void stateMachine::sm_state_printrate(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("st: PRINT RATE"));
#endif
        //   error.json_error("WARNING", "Print Rate Update Disabled");
        lastState = smState;
    }
    if (stateData.uintData < 1 || stateData.uintData > 50) {
        //   errors.set_error(false, -10, "Out of Bounds Print Rate Commanded", errors.WARNING, "state-printrate");
        //   errors.print_json_status();
    } // else if (stateData.uintData > sampleRate_Hz) {
    //   errors.set_error(false, -10, "Cannot set print rate greater than sample rate", errors.WARNING, "state-printrate");
    //   errors.print_json_status();
    // } else {
    //  print_rate_Hz = stateData.uintData;
    //  print_delay_mS = 1000 / print_rate_Hz;
    //  num_samples_req = uint8_t(sampleRate_Hz / print_rate_Hz);  // Number of samples required to collect between each print cycle
    //}
    smState = STATE_WAIT;
}

// Start streaming data
void stateMachine::sm_state_start_stream(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("st: STARTSTREAM"));
#endif
        stateData.uintData++;
        report.start_printing();
        lastState = smState;
    }

    // streaming_active = true;
    // samples_written = 0;  // start sampling again, wondering if this is the cause of the issues
    //  snapshot_timer_mS = jsonStateData_t.intData;
    smState = STATE_WAIT;
}

// Stop streaming data
void stateMachine::sm_state_stop_stream(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("st: STOPSTREAM"));
#endif
        stateData.uintData++;
        report.stop_printing();
        lastState = smState;
    }
    // streaming_active = false;
    // snapshot_timer_mS = 0;
    smState = STATE_WAIT;
}

// NEWER FUNCTIONS from here -------------------------------->>>>

// Trigger a snapshot of data to be taken over X amount of time
void stateMachine::sm_state_set_secret(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("st: SET SECRET"));
#endif
        lastState = smState;
        if (stateData.msg[0] == '\0') { // empty string
            Serial.println(F("{\"WARNING\":\"Secret not Set\"}"));
            smState = STATE_WAIT;
            return;
        } else {
            //      memory.set_secret(stateData.msg);
        }
    }
    smState = STATE_WAIT;
}

void stateMachine::sm_state_reset(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("st: RESET"));
#endif
        //   error.json_error("WARNING", "Reset State Undefined");
        stateData.uintData++;
        Serial.print("Secret: ");
        Serial.print(stateData.auth);
        Serial.print(" float: ");
        Serial.println(stateData.msg);
        lastState = smState;
    }
    smState = STATE_WAIT;
}

// Print the commands list to the Serial Output
void stateMachine::sm_state_info(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("st: help"));
#endif
        //   error.json_error("WARNING", "Info State Undefined");
        stateData.uintData++;
        lastState = smState;
    }

    smState = STATE_WAIT;
}

// Print the commands list to the Serial Output
void stateMachine::sm_state_help(jsonStateData_t &stateData) {
    if (lastState != smState) {
#if DEBUG_STATES == true
        Serial.println(F("st: help"));
#endif
        stateData.uintData++;
        lastState = smState;
    }
    // print_cmds();
    print_cmds2();
    smState = STATE_WAIT;
}

void stateMachine::change_state(stateDef_t new_state) { smState = new_state; }

// 6. Finally define the state machine function
void stateMachine::sm_Run(jsonStateData_t &stateData) {
    if (smState < NUM_STATES) {
#if DEBUG_STATE_MACHINE == true
        if (lastState != smState) {
            char buffer[14];
            Serial.print("{\"sm\":\"");
            //    strcpy_P(buffer, (char *)pgm_read_ptr(&(stateNames[smState])));  // Necessary casts and dereferencing, just copy.
            //     Serial.print(buffer);
            Serial.print(stateNames[smState]); // old RAM heavy version
            Serial.println(F("\"}"));
        }
#endif
        (this->*stateHandler[smState].func)(stateData);

    } else {
        sm_state_wait(stateData);
        Serial.println(F("sm: Exception -> NUM_STATES exceeded"));
    }
}
