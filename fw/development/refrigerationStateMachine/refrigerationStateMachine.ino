/* Refrigeration - State Machine



State machine boilerplate from https://www.edn.com/electronics-blogs/embedded-basics/4406821/Function-pointers---Part-3--State-machines



*/

#include "ArduinoJson-v6.9.1.h"
#define COMMAND_SIZE 64

StaticJsonDocument<COMMAND_SIZE> doc;  // This is the JSON object
char command[COMMAND_SIZE];

#define DEBUG true
#define COMMAND_HINTS true

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
  STATE_COMP_OFF
} StateType;

// State Names Array (Makes printing the current state prettier)
char stateNames[][32] = {
  "STATE_INIT",
  "STATE_WAIT",
  "STATE_STOP",
  "STATE_RUNNING",
  "STATE_SELECT_VALVE",
  "STATE_FANS_ON",
  "STATE_FANS_OFF",
  "STATE_COMP_ON",
  "STATE_COMP_OFF"

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
  { STATE_COMP_OFF, sm_state_comp_off }
};

int NUM_STATES = 9;

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
  Serial.println("State Machine: Init");
  // Init all o/ps to default state
  smState = STATE_WAIT;
}

char exampleCommands[][64] = {
  "{\"mode\":\"stop\"}",
  "{\"cmd\":\"fans\",\"param\":0}",
  "{\"valve\":1, \"state\":1}",
  "{\"fans\":1}",
  "{\"fans\":0}",
  "{\"comp\":0}"
};


void sm_state_wait() {
  // Check to see if first time state has been called in sequence
  if (lastState != smState) {
    // If first iteration print state machine status
    Serial.println("State Machine: Waiting");
    // print suggested commands
#if COMMAND_HINTS == true
      Serial.println("\nEnter Command in format:");
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
  Serial.println("State Machine: Set Valve");
  Serial.print("Valve Num: ");
  Serial.print(valveNum);
  Serial.print(",  Valve Status: ");
  Serial.println(valveState);
  valveNum = 0;
  valveState = 0;
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_fans_on() {
  Serial.println("State Machine: Fans On");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_fans_off() {
  Serial.println("State Machine: Fans Off");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_comp_on() {
  Serial.println("State Machine: Compressor On");
  lastState = smState;
  smState = STATE_WAIT;
}

void sm_state_comp_off() {
  Serial.println("State Machine: Compressor Off");
  lastState = smState;
  smState = STATE_WAIT;
}





/**
* Define the State Machine Function
*/

void sm_Run(void) {
  // smState = readSerialJSON(smState);  // no longer needs to return variable
  readSerialJSON();  // listen for incoming serial commands and update global smState variable

  if (smState < NUM_STATES) {
#if DEBUG == true
    if (lastState != smState) {
      Serial.print("{\"State\":");
      Serial.print(stateNames[smState]);
      Serial.println("}");
    }
#endif
    (*StateMachine[smState].func)();  // This function does the magic
  } else {
    // could have a default function that runs here in case of exception
    Serial.println("Exception in State Machine");
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
void readSerialJSON(void) {
  bool commandParsed = false;
  if (Serial.available() > 0) {
    char start[] = "start";
    char stop[] = "stop";
    char cmd_wd[] = "cmd";
    char vlv_wd[] = "valve";
    char md_wd[] = "mode";
    char valve[] = "valve";
    char fans[] = "fans";
    char comp[] = "comp";

    Serial.readBytesUntil(10, command, COMMAND_SIZE);

    Serial.print("\ncommand received: ");
    Serial.println(command);

    deserializeJson(doc, command);




    // First work out what the command word is

    // First check if the first index is "valve"**** SEE NOTE!
    // In this case we can just test if valve has a value.
    // If valve == 0 we know there is no real value there and can ignore

    valveNum = doc["valve"];
    if ((valveNum > 0) && (valveNum < 8)) {
      Serial.print("valveNum: ");
      Serial.print(valveNum);
      Serial.print("   Valve Status: ");
      valveState = doc["state"];
      Serial.println(valveState);
      commandParsed = true;
      smState = STATE_SELECT_VALVE;
    } else if (valveNum == 0) {
      // do nothing
    } else if ((valveNum >= 8) || (valveNum < 0)) {
      Serial.println("Unknown Valve Number Selected");
    }

    // This step added to allow parsing keys but unsure of best practice
    JsonObject root = doc.as<JsonObject>();  // this was previously doc.to<JsonObject>(); DID NOT WORK! does now with "as"


    // First check if the first index is "fans"**** SEE NOTE!
    // In this case fans value could be 0, therefore we need to lookup and see if key exists first

    if (root.containsKey("fans")) {
      int fanState = doc["fans"];
      Serial.print("fanState: ");
      Serial.println(fanState);
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
      Serial.print("compState: ");
      Serial.println(compState);
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

      Serial.println("mode detected: ");
      Serial.println(mode);
      if (strcmp(mode, stop) == 0) {
        smState = STATE_STOP;
        Serial.println("{\"result\":\"ok\"}");
      } else {
      }
      commandParsed = true;
    }

    // Then check if first index contains a "cmd"
    if (root.containsKey("cmd")) {
      const char* cmd = doc["cmd"];

      Serial.println("cmd detected: ");
      Serial.println(cmd);
      commandParsed = true;

      // Then check to see what cmd has been sent
      if (strcmp(cmd, stop) == 0) {
        smState = STATE_STOP;
        Serial.println("{\"result\":\"ok\"}");
      } else {
        // Serial.println("{\"error\":\"Unable to stop\"}");
      }


      if (strcmp(cmd, fans) == 0) {
        int fanState = doc["param"];
        if (fanState > 0) {
          smState = STATE_FANS_ON;
          Serial.println("{\"result\":\"ok\"}");
        } else {
          smState = STATE_FANS_OFF;
          Serial.println("{\"result\":\"ok\"}");
        }
      }


      if (strcmp(cmd, comp) == 0) {
        int compState = doc["param"];
        if (compState > 0) {
          smState = STATE_COMP_ON;
          Serial.println("{\"result\":\"ok\"}");
        } else {
          smState = STATE_COMP_OFF;
          Serial.println("{\"result\":\"ok\"}");
        }
      }

    } // end of "cmd"

      if (commandParsed) {
        Serial.println("Command Parsed Successfully\n");
      } else {
        Serial.println("Error Parsing JSON Command\n");
      }
    }  //if bytes available

    // return smState;  // This is a global variable it does not need to be returned.
  }



  void setup() {
    Serial.begin(115200);
    Serial.println("\n\nDeploying Refrigeration State Machine");
  }

  void loop() {
    sm_Run();
  }



  /*
***NOTE:
Avoid this function when you can!
The function can be avoided most of the time.
Because ArduinoJson implements the Null Object Pattern, it is always safe to read the object: if the key doesn’t exist, it returns an empty value.
-> This cannot be avoided in this case as one of the possible values will be zero!


*/