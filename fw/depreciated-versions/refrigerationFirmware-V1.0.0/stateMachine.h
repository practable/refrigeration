/* Refrigeration - State Machine



State machine boilerplate from https://www.edn.com/electronics-blogs/embedded-basics/4406821/Function-pointers---Part-3--State-machines



*/

#pragma once

#ifndef stateMachine_h
#define stateMachine_h

#include "ArduinoJson-v6.9.1.h"
#include "adamController.h"

#define COMMAND_SIZE 64

StaticJsonDocument<COMMAND_SIZE> doc;  // This is the JSON object
char command[COMMAND_SIZE];



/**
 * Defines the valid states for the state machine
 * 
 */
typedef enum {
  STATE_INIT,
  STATE_WAIT,
  STATE_STOP,
  STATE_RUNNING,
  STATE_SELECT_VALVE,
  STATE_FANS_ON,
  STATE_FANS_OFF,
  STATE_COMP_ON,
  STATE_COMP_OFF,
  STATE_REGAS,
  STATE_QUICKSTART
} StateType;

// State Names Array (Makes printing the current state prettier)
char stateNames[][20] = {
  "STATE_INIT",
  "STATE_WAIT",
  "STATE_STOP",
  "STATE_RUNNING",
  "STATE_SELECT_VALVE",
  "STATE_FANS_ON",
  "STATE_FANS_OFF",
  "STATE_COMP_ON",
  "STATE_COMP_OFF",
  "STATE_REGAS",
  "STATE_QUICKSTART"
};

//state Machine function prototypes
void sm_state_init(void);
void sm_state_wait(void);
void sm_state_stop(void);
void sm_state_running(void);
void sm_state_valve(void);
void sm_state_fans_on(void);
void sm_state_fans_off(void);
void sm_state_comp_on(void);
void sm_state_comp_off(void);
void sm_state_regass(void);
void sm_state_quick(void);

/**
 * Type definition used to define the state
 */




typedef struct
{
  StateType State;     //< Defines the command
  void (*func)(void);  //< Defines the function to run
} StateMachineType;



/**
 * A table that defines the valid states of the state machine and
 * the function that should be executed for each state
 */
StateMachineType StateMachine[] = {
  { STATE_INIT, sm_state_init },
  { STATE_WAIT, sm_state_wait },
  { STATE_STOP, sm_state_stop },
  { STATE_RUNNING, sm_state_running },
  { STATE_SELECT_VALVE, sm_state_valve },
  { STATE_FANS_ON, sm_state_fans_on },
  { STATE_FANS_OFF, sm_state_fans_off },
  { STATE_COMP_ON, sm_state_comp_on },
  { STATE_COMP_OFF, sm_state_comp_off },
  { STATE_REGAS, sm_state_regass },
  { STATE_QUICKSTART, sm_state_quick }
};

int NUM_STATES = 11;

/**
 * Stores the current state of the state machine
 */

StateType smState = STATE_INIT;
StateType lastState;


// Global Variables

int valveNum = 0;    // when command is Rxed theses values are updated so when state_valves is called, the valve and its new state are saved globally.
int valveState = 0;  // after state has finished setting valves it should set these variables back to 0

int fanState = 0;



/**
* Define the functions for each state
*/

void sm_state_init() {
  // Serial.println("State Machine: Init");
  // Init all o/ps to default state
  smState = STATE_WAIT;
}

#if COMMAND_HINTS == true
char exampleCommands[][32] = {
  "{\"mode\":\"stop\"}",
  "{\"cmd\":\"fans\",\"param\":0}",
  "{\"valve\":1, \"state\":1}",
  "{\"fans\":1}",
  "{\"fans\":0}",
  "{\"comp\":0}"
};
#endif

void sm_state_wait() {
  // Check to see if first time state has been called in sequence
  if (lastState != smState) {
    // If first iteration print state machine status
#if DEBUG_STATES == true
    Serial.println(F("State Machine: Waiting"));
#endif
    // print suggested commands
#if COMMAND_HINTS == true
    Serial.println(F("\nEnter Command in format:"));
    int numExamples = sizeof(exampleCommands) / sizeof(exampleCommands[0]);  // just get the size of the example commands array
    for (int i = 0; i < numExamples; i++) {
      Serial.println(exampleCommands[i]);  // print example commands
    }
#endif
    lastState = smState;
    // Do anything else that needs to happen first time state is called
  }
  // Do everything that repeats in this state
  // Define the next state if required
  // smState = STATE_WAIT; // In this case this is the default state
}

void sm_state_stop() {
#if DEBUG_STATES == true
  Serial.println(F("State Machine: Stop"));
#endif
  // Stop Compressor
  adam6052_B.set_coil(2, false);
  // Stop Fans
  adam6052_B.set_coils(0b00000000);  // or set everything off
  // Close V1-4
  // Close V5 & V6
  adam6052_A.set_coils(0b00000000);
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_quick() {
#if DEBUG_STATES == true
  Serial.println(F("State Machine: Quickstart"));
#endif
  // open V1, V5, V6
  adam6052_A.set_coils(0b00110001);  // or set everything off
  delay(1000);
  // Start Fans
  adam6052_B.set_coils(0b00000011);  // or set everything off
  delay(2000);
  //Start Compressor (disabled for now)
  //adam6052_B.set_coil(2, true);
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_running() {
  //  Serial.println("State Machine: Running");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_valve() {
#if DEBUG_STATES == true
  Serial.println(F("State Machine: Set Valve"));
  Serial.print(F("Valve Num: "));
  Serial.print(valveNum);
  Serial.print(F(",  Valve Status: "));
  Serial.println(valveState);
#endif
  adam6052_A.set_coil(valveNum - 1, valveState);  // -1 as array is indexed at 0
  valveNum = 0;
  valveState = 0;
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_fans_on() {
#if DEBUG_STATES == true
  Serial.println(F("State Machine: Fans On"));
#endif
  adam6052_B.set_coil(0, true);
  adam6052_B.set_coil(1, true);
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_fans_off() {
#if DEBUG_STATES == true
  Serial.println(F("State Machine: Fans Off"));
#endif
  adam6052_B.set_coil(0, false);
  adam6052_B.set_coil(1, false);
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_comp_on() {
#if DEBUG_STATES == true
  Serial.println(F("State Machine: Compressor On"));
#endif
  adam6052_B.set_coil(2, true);
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_comp_off() {
#if DEBUG_STATES == true
  Serial.println(F("State Machine: Compressor Off"));
#endif
  adam6052_B.set_coil(2, false);
  lastState = smState;
  smState = STATE_WAIT;
}


void sm_state_regass() {
  if (lastState != smState) {
    Serial.println(F("State Machine: Regas System"));
    Serial.println(F("Opening Cut-Off Valves (1-4, 5, 6)"));
    adam6052_A.set_coils(0b00111111);
    delay(1000);
    Serial.println(F("Starting Condenser Fan"));
    adam6052_A.set_coil(0, true);
    delay(1000);
    Serial.println(F("Starting Compressor"));
    adam6052_A.set_coil(2, true);
    delay(1000);
    Serial.println(F("Refill with 1.1 kg of refrigerant, or until sightglass is full"));
    delay(1000);
    lastState = smState;
  }
}


/**
* Define the JSON Parsing Function

Origionally defined as:
StateType readSerialJSON(StateType smState) {
  but no reason for it as it uses global variables for tracking state,
  therefore should be

  void readSerialJSON(void)
*/

//StateType readSerialJSON(StateType smState) {
int readSerialJSON(void) {
  bool commandParsed = false;
  int error = 0;
  if (Serial.available() > 0) {
    //  char start[] = "start";
    char stop[] = "stop";
    //  char cmd_wd[] = "cmd";
    //  char md_wd[] = "mode";
    //   char valve[] = "valve";
    char fans[] = "fans";
    char comp[] = "comp";
    char regas[] = "regas";
    char quick[] = "quick";
    char ok_response[20] = "{\"result\":\"ok\"}";

    Serial.readBytesUntil(10, command, COMMAND_SIZE);

#if DEBUG_SERIAL == true
    Serial.print(F("\ncommand received: "));
    Serial.println(command);
#endif
    deserializeJson(doc, command);


    // First check if state is not equal to wait
    // :p you idiot how would you ever get out of this - think!
    //   if (smState != STATE_WAIT) {
    //     Serial.println(F("State is not STATE_WAIT, try sending:\n{\"mode\":\"stop\"}"));
    //     return -1;  // return and do not continue parsing JSON
    //   }

    // Now to parse the JSON message
    // First work out what the command word is

    // First check if the first index is "valve"**** SEE NOTE!
    // In this case we can just test if valve has a value.
    // If valve == 0 we know there is no real value there and can ignore

    valveNum = doc["valve"];
    if ((valveNum > 0) && (valveNum < 8)) {
      valveState = doc["state"];
#if DEBUG_JSON == true
      Serial.print(F("valveNum: "));
      Serial.print(valveNum);
      Serial.print(F("   Valve Status: "));
      Serial.println(valveState);
#endif
      commandParsed = true;
      smState = STATE_SELECT_VALVE;
    } else if (valveNum == 0) {
      Serial.println(F("Unknown Valve Number Selected"));
    } else if ((valveNum >= 8) || (valveNum < 0)) {
    //  Serial.println(F("Unknown Valve Number Selected"));
    }

    // This step added to allow parsing keys but unsure of best practice
    JsonObject root = doc.as<JsonObject>();  // this was previously doc.to<JsonObject>(); DID NOT WORK! does now with "as"


    // First check if the first index is "fans"**** SEE NOTE!
    // In this case fans value could be 0, therefore we need to lookup and see if key exists first

    if (root.containsKey("fans")) {
      int fanState = doc["fans"];
#if DEBUG_JSON == true
      Serial.print(F("fanState: "));
      Serial.println(fanState);
#endif
      if (fanState > 0) {
        commandParsed = true;
        smState = STATE_FANS_ON;
      } else if (fanState == 0) {
        commandParsed = true;
        smState = STATE_FANS_OFF;
      }
    } else {
      // Serial.println("Could not find key \"fans\"");
      // Do nothing - Look for other keys
    }

    if (root.containsKey("comp")) {
      int compState = doc["comp"];
#if DEBUG_JSON == true
      Serial.print(F("compState: "));
      Serial.println(compState);
#endif
      if (compState > 0) {
        commandParsed = true;
        smState = STATE_COMP_ON;
      } else if (fanState == 0) {
        commandParsed = true;
        smState = STATE_COMP_OFF;
      }
    } else {
      // Serial.println("Could not find key \"comp\"");
      // Do nothing - Look for other keys
    }


    // Then check if first index contains a "mode"
    if (root.containsKey("mode")) {
      const char* mode = doc["mode"];
#if DEBUG_JSON == true
      Serial.println(F("mode detected: "));
      Serial.println(mode);
#endif
      if (strcmp(mode, stop) == 0) {
        smState = STATE_STOP;
        Serial.println(ok_response);
      } else if (strcmp(mode, regas) == 0) {
        smState = STATE_REGAS;
        Serial.println(ok_response);
      } else if (strcmp(mode, quick) == 0) {
        smState = STATE_QUICKSTART;  
        Serial.println(ok_response);
      } else {
        Serial.println(F("{\"result\":\"error - unknown mode\"}"));
      }
      commandParsed = true;
    }

    // Then check if first index contains a "cmd"
    if (root.containsKey("cmd")) {
      const char* cmd = doc["cmd"];
#if DEBUG_JSON == true
      Serial.println(F("cmd detected: "));
      Serial.println(cmd);
#endif
      commandParsed = true;

      // Then check to see what cmd has been sent
      if (strcmp(cmd, stop) == 0) {
        smState = STATE_STOP;
        Serial.println(ok_response);
      } else {
        Serial.println(F("{\"error\":\"Unable to stop\"}"));
      }


      if (strcmp(cmd, fans) == 0) {
        int fanState = doc["param"];
        if (fanState > 0) {
          smState = STATE_FANS_ON;
          Serial.println(ok_response);
        } else {
          smState = STATE_FANS_OFF;
          Serial.println(ok_response);
        }
      }


      if (strcmp(cmd, comp) == 0) {
        int compState = doc["param"];
        if (compState > 0) {
          smState = STATE_COMP_ON;
          Serial.println(ok_response);
        } else {
          smState = STATE_COMP_OFF;
          Serial.println(ok_response);
        }
      }

    }  // end of "cmd"

    if (commandParsed) {
#if DEBUG_JSON == true
      Serial.println(F("Command Parsed Successfully\n"));
#endif
      // Error should still be zero, can be set to other values earlier to pass out other errors
    } else {
      Serial.println(F("Error Parsing JSON Command\n"));
      error = -1;
    }
  }              //if bytes available
  return error;  // if success returns 0, else -1 or other error int
}



/**
* Define the State Machine Function
*/

void sm_Run(void) {
  // smState = readSerialJSON(smState);  // no longer needs to return variable
  readSerialJSON();  // listen for incoming serial commands and update global smState variable

  if (smState < NUM_STATES) {
#if DEBUG_STATE_MACHINE == true
    if (lastState != smState) {
      Serial.print("{\"State\":");
      Serial.print(stateNames[smState]);
      Serial.println("}");
    }
#endif
    sprintf(status.state, "%s", stateNames[smState]);  // added function doesnt seem to work - causing wider issues?
    (*StateMachine[smState].func)();                   // This function does the magic
  } else {
    // could have a default function that runs here in case of exception
    (*StateMachine[STATE_STOP].func)();
    Serial.println(F("Exception in State Machine"));
  }
}





#endif