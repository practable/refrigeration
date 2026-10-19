

#include <ArduinoJson.h> // installed version 6.21.5 [Arduino Library Manager]

#include "jsonStateData.h"

// CMND Descriptions -> Write a short description for each CMD

extern const char null_desc[];
// Unique Cmnds
extern const char desc_0[];
extern const char desc_1[];
extern const char desc_2[];
extern const char desc_3[];
extern const char desc_4[];
extern const char desc_5[];
extern const char desc_6[];
// new cmnds
extern const char desc_7[];
extern const char desc_8[];
extern const char desc_9[];
extern const char desc_10[];

// Common Commands
extern const char desc_A[];
extern const char desc_B[];
extern const char desc_C[];
extern const char desc_D[];
extern const char desc_E[];
extern const char desc_F[];
extern const char desc_G[];
extern const char desc_H[];

extern const int16_t NUM_CMDS;

extern const char *const cmdDesc[];

void print_cmds();

// prints a single command from lists
void print_cmd2(uint8_t cmnd_num);

void print_cmds2();
