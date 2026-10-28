/*   otherFunctions.h

  All other utility and setup functions



*/
#ifndef utility_h
#define utility_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif

#include "globals.h"
#include "jsonStateData.h"

void ethernet_begin();

void print_json_state_data(jsonStateData_t &data);

void print_program_info();

void sensors_begin();

#endif