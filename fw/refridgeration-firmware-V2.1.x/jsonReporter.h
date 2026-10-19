
/*  jsonReporter.h

 Functions to load data into a json template and print to Serial Output

*/



#ifndef jsonReporter_h
#define jsonReporter_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <wProgram.h>
#endif



#define JSON_TX_BUFFER_SIZE 300


//
//#include "datastore.h"

extern bool print_json_active; //= false;

// rounds a number to 2 decimal places
// example: round(3.14159) -> 3.14
float round2(double value);

// rounds a number to X decimal places and ensures fixed width of signed and unsigned
void formatFloat(float value, char *buffer, size_t length, int decimalPlaces = 2);

void update_json();    //const instrumentData_t &data

#endif