/* Refrigeration - State Machine



State machine boilerplate from https://www.edn.com/electronics-blogs/embedded-basics/4406821/Function-pointers---Part-3--State-machines



*/

#include "ArduinoJson-v6.9.1.h"
#define COMMAND_SIZE 64

StaticJsonDocument<COMMAND_SIZE> doc;
char command[COMMAND_SIZE];

bool debug = true;

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
  STATE_SELECT_RELAY,
  STATE_FANS_ON,
  STATE_FANS_OFF
} StateType;

// State Names Array (Makes printing the current state prettier)
char* stateNames[] = {
  "STATE_INIT",
  "STATE_WAIT",
  "STATE_STOP",
  "STATE_RUNNING",
  "STATE_SELECT_VALVE",
  "STATE_SELECT_RELAY",
  "STATE_FANS_ON",
  "STATE_FANS_OFF"
};

//state Machine function prototypes
void sm_state_init(void);
void sm_state_wait(void);
void sm_state_stop(void);
void sm_state_running(void);
void sm_state_valve(void);
void sm_state_relay(void);
void sm_state_fans_on(void);
void sm_state_fans_off(void);

/**
 * Type definition used to define the state
 */

typedef struct
{
  StateType State;    /**< Defines the command */
  void (*func)(void); /**< Defines the function to run */
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
  { STATE_SELECT_RELAY, sm_state_relay },
  { STATE_FANS_ON, sm_state_fans_on },
  { STATE_FANS_OFF, sm_state_fans_off }
};

int NUM_STATES = 8;

/**
 * Stores the current state of the state machine
 */

StateType smState = STATE_INIT;
StateType lastState;

/**
* Define the functions for each state
*/

void sm_state_init() {
  Serial.println("State Machine: Init");
  // Init all o/ps to default state
  smState = STATE_WAIT;
}


void sm_state_wait() {
  // Check to see if first time state has been called in sequence
  if (lastState != smState) {
    // If first iteration print state machine status
    Serial.println("State Machine: Waiting");
    Serial.println("Enter Command in format: \n{\"cmd\":\"value\"}\n\n");
    lastState = smState;
    // Do anything else that needs to happen first time state is called
  }
  // Do everything that repeats in this state

  // Define the next state if required
  // smState = STATE_WAIT;
}

void sm_state_stop() {
  Serial.println("State Machine: Stop");
  // Stop Compressor
  // Stop Fans
  // Close V1-4
  // Close V5 & V6
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_running() {
  Serial.println("State Machine: Running");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_valve() {
  Serial.print("State Machine: Set Valve");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_fans_on() {
  Serial.print("State Machine: Fans On");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_fans_off() {
  Serial.print("State Machine: Fans Off");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_relay() {
  Serial.println("State Machine: Set Relay");
  lastState = smState;
  smState = STATE_WAIT;
}



/**
* Define the State Machine Function
*/

void sm_Run(void) {
  if (smState < NUM_STATES) {
    if (lastState != smState) {
      if (debug) {
        Serial.print("{\"State\":");
        Serial.print(stateNames[smState]);
        Serial.println("}");
      }
    }
    smState = readSerialJSON(smState);
    (*StateMachine[smState].func)();
  } else {
    Serial.println("Exception in State Machine");
  }
}



/**
* Define the JSON Parsing Function
*/

StateType readSerialJSON(StateType smState) {
  if (Serial.available() > 0) {
    char start[] = "start";
    char stop[] = "stop";
    char valve[] = "valve";
    char fans[] = "fans";
    char comp[] = "comp";

    char report_interval[] = "interval";
    char loaded[] = "loaded";
    char unloaded[] = "unloaded";
    char brake[] = "brake";
    char drive[] = "drive";

    Serial.readBytesUntil(10, command, COMMAND_SIZE);

    Serial.println("command");
    Serial.print(command);

    deserializeJson(doc, command);

    //   Serial.println("doc: ");
    //    Serial.print(doc);

    const char* cmd = doc["cmd"];

    if (strcmp(cmd, stop) == 0) {
      smState = STATE_STOP;
      Serial.println("{\"result\":\"ok\"}");
    } else {
      // Serial.println("{\"error\":\"Unable to stop\"}");
    }


    if (strcmp(cmd, valve) == 0) {
      int valveNum = doc["param"];
      if ((valveNum >= 0) && (valveNum <= 6)) {
        smState = STATE_SELECT_VALVE;
        Serial.println("{\"result\":\"ok\"}");
      } else {
        Serial.println("{\"error\":\"Unknown Valve Selected)\"}");
      }
    }


    if (strcmp(cmd, fans) == 0) {
      int fanState = doc["param"];
      if (fanState >= 0) {
        smState = STATE_FANS_ON;
        Serial.println("{\"result\":\"ok\"}");
      } else {
        smState = STATE_FANS_OFF;
        Serial.println("{\"result\":\"ok\"}");
      }
    }

  }  //if bytes available
  return smState;
}



void setup() {
  Serial.begin(115200);
  Serial.println("\n\nDeploying Refrigeration State Machine");
}

void loop() {
  sm_Run();
}
