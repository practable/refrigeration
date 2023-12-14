/* Refrigeration - State Machine



State machine boilerplate from https://www.edn.com/electronics-blogs/embedded-basics/4406821/Function-pointers---Part-3--State-machines



*/

#include "ArduinoJson-v6.9.1.h"

#define COMMAND_SIZE 64

StaticJsonDocument<COMMAND_SIZE> doc;
char command[COMMAND_SIZE];


/**
 * Defines the valid states for the state machine
 * 
 */
typedef enum {
  STATE_START_CALIBRATION,
  STATE_ZERO_ENCODER,
  STATE_AWAITING_STOP,
  STATE_DRIVING,
  STATE_START,
  STATE_STOPPED,
} StateType;

//state Machine function prototypes
void sm_state_init(void);
void sm_state_wait(void);
void sm_state_stop(void);
void sm_state_running(void);
void sm_state_valve(void);
void sm_state_relay(void);


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
  { STATE_SELECT_RELAY, sm_state_relay }
};

int NUM_STATES = 6;

/**
 * Stores the current state of the state machine
 */

StateType SmState = STATE_INIT;


/**
* Define the functions for each state
*/

void sm_state_init() {
  Serial.begin(115200);
  Serial.println("State Machine: Init");
  // Init all o/ps to default state
  SmState = STATE_WAIT;
}


void sm_state_wait() {
  Serial.println("State Machine: Waiting");
  SmState = STATE_WAIT;
}

void sm_state_stop() {
  Serial.println("State Machine: Stop");
  // Stop Compressor
  // Stop Fans
  // Close V1-4
  // Close V5 & V6
  SmState = STATE_WAIT;
}

void sm_state_running() {
  Serial.println("State Machine: Running");
  SmState = STATE_WAIT;
}

void sm_state_valve() {
  Serial.println("State Machine: Set Valve");
  SmState = STATE_WAIT;
}

void sm_state_relay() {
  Serial.println("State Machine: Set Relay");
  SmState = STATE_WAIT;
}



/**
* Define the State Machine Function
*/

void sm_Run(void){
    if (SmState < NUM_STATES)
  {
    if (debug){
      Serial.print("{\"State\":");
      Serial.print(SmState);
      Serial.println("}");
    }
    SmState = readSerialJSON(SmState);
    (*StateMachine[SmState].func)();
    
  }
  else{
    Serial.println("Exception in State Machine");
  }  
}



/**
* Define the JSON Parsing Function
*/

StateType readSerialJSON(StateType SmState){
  

  
  if (Serial.available() > 0) 
  {

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
                
    deserializeJson(doc, command);

    const char* cmd = doc["cmd"];
    
    if (strcmp(cmd,stop)==0)
    {
        SmState = STATE_STOPPED; 
        Serial.println("{\"result\":\"ok\"}");
      }
      else
      {
        Serial.println("{\"error\":\"Unable to stop\"}");
      }
    

    if (strcmp(cmd,drive)==0)
    {
      int newDriveThresh = doc["param"];
      if ((newDriveThresh >= 0) && (newDriveThresh <= 100))
      {
        driveThresh = newDriveThresh;
        Serial.println("{\"result\":\"ok\"}");
      }
      else
      {
        Serial.println("{\"error\":\"drive must be between 0 - 100 (inclusive)\"}");
      }
    }

    
    if (strcmp(cmd,brake)==0)
    {
      int newBrakeThresh = doc["param"];
      if ((newBrakeThresh >= 0) && (newBrakeThresh <= 100))
      {
        brakeThresh = newBrakeThresh;
        Serial.println("{\"result\":\"ok\"}");
      }
      else
      {
        Serial.println("{\"error\":\"break must be between 0 - 100 (inclusive)\"}");
      }
    }
    
    if (strcmp(cmd,stop)==0)
    {
      if (((SmState == STATE_DRIVING) || (SmState == STATE_STOPPED)))
      { 
        Serial.print("{\"result\":\"stopped\"");
        const char * param = doc["param"];
      
        if (strcmp(param, loaded)==0){
          //load is on
          digitalWrite(loadLed,HIGH); 
          digitalWrite(loadPin,HIGH); 
          loadMessage(HIGH);
          brakeStop = false;

        }
        else if (strcmp(param, unloaded)==0){
          //load is off
          digitalWrite(loadLed,LOW); 
          digitalWrite(loadPin,LOW); 
          loadMessage(LOW);
          brakeStop = false;
        }
        else if (strcmp(param, brake)==0){
          //load is off - else short circuit!
          digitalWrite(loadLed,LOW); 
          digitalWrite(loadPin,LOW); 
          loadMessage(LOW);
          brakeStop = true;
        }        
        Serial.print(",\"loaded\":");
        Serial.print(digitalRead(loadPin));
        Serial.print(",\"brake\":");
        Serial.print(brakeStop);
        Serial.print("}");
        SmState = STATE_STOPPED;
      }
      else
      {
        Serial.print("{\"error\":\"In wrong state to stop\"}");
      } 
  
    }//if stop
    
    if (strcmp(cmd,cal)==0)
    {
    
      if ((SmState == STATE_DRIVING) || (SmState == STATE_STOPPED))
      { 
        Serial.println("{\"result\":\"calibrating\"}");
        SmState = STATE_START_CALIBRATION;
      }
      else{
      
      Serial.println("{\"error\":\"In wrong state to calibrate\"}");
      }
    } //if cal
    if (strcmp(cmd,start)==0)
    {
    
      if ((SmState == STATE_DRIVING) || (SmState == STATE_STOPPED))
      { 

        int newStartDelay = doc["param"];
        if ((newStartDelay >= 0) && (newStartDelay <= 500))
        {
          startDelay = newStartDelay;

          Serial.println("{\"result\":\"starting\"}");
          SmState = STATE_START;
          
        }
        else
        {
          Serial.println("{\"error\":\"start must be between 0 - 500 [ms](exclusive)\"}");
        }
        

      }
      else{
      
      Serial.println("{\"error\":\"In wrong state to start\"}");
      }
    } //if cal

  } //if bytes available
  return SmState;
}




