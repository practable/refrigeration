

#include <ArduinoJson.h>  // installed version 6.21.5 [Arduino Library Manager]

#include "jsonStateData.h"

// CMND Descriptions -> Write a short description for each CMD

extern const char null_desc[];
// Unique Cmnds
extern const char PROGMEM desc_0[];
extern const char PROGMEM desc_1[];
extern const char PROGMEM desc_2[];
extern const char PROGMEM desc_3[];
extern const char PROGMEM desc_4[];
extern const char PROGMEM desc_5[];
extern const char PROGMEM desc_6[];
// new cmnds
extern const char PROGMEM desc_7[];
extern const char PROGMEM desc_8[];
extern const char PROGMEM desc_9[];
extern const char PROGMEM desc_10[];

// Common Commands
extern const char PROGMEM desc_A[];
extern const char PROGMEM desc_B[];
extern const char PROGMEM desc_C[];
extern const char PROGMEM desc_D[];
extern const char PROGMEM desc_E[];
extern const char PROGMEM desc_F[];
extern const char PROGMEM desc_G[];
extern const char PROGMEM desc_H[];

extern const int16_t NUM_CMDS;

extern const char *const cmdDesc[];

void print_cmds();

// prints a single command from lists
void print_cmd2(uint8_t cmnd_num);

void print_cmds2();
