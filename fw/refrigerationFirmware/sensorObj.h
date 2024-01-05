/*  sensorObj.h - The Generic Sensor Conversion Library for Arduino

    Convert Voltage, 4-20mA and 0-20mA  linear signals into process values


    Imogen Heard
    21/12/23


*/

#pragma once

#ifndef sensorObj_h
#define sensorObj_h

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "stdio.h"

#define VOLTAGE_SENSOR 0
#define CURRENT_SENSOR 1
#define OTHER_SENSOR 2

#define SENSOR_BUFFER_SIZE 10

class sensorObj {

public:

  sensorObj(int _sensorType, const char _sensorUnits[16], const char _sensorID[32] = { "xx_sensor" })
    : sensorType(_sensorType) {
    strcpy(sensorID, _sensorID);
    strcpy(process_units, _sensorUnits);
    if (sensorType == VOLTAGE_SENSOR){
      strcpy(ADC_units, " V ");
    } else if (sensorType == CURRENT_SENSOR){
      strcpy(ADC_units, " mA ");
    } else if (sensorType == OTHER_SENSOR){
      strcpy(ADC_units, " n/a ");
    } else {
      strcpy(ADC_units, " ? ");
    }
  }

  int sensorType;


  float dac_min;  // measured value min
  float dac_max;  // measured value max
  float process_min;
  float process_max;
  float input_range;
  float process_range;
  int rangeSet = 0;

  float currentVal = 0;  //current value of the sensor
  uint32_t timeStamp;   // timeStamp for last datapoint taken

  // Should be called in series to get sensor calibration correctly
  void set_range_min(float _process_min = 0, float _dac_min = 0);
  void set_range_max(float _process_max = 100, float _dac_max = 65535);
  void setCalibration();

  float calcProcessVar(float _dacVal);   // generic method uses set range functions to do a quick scaling operation and return the process val. Explicit conversion methods will be added below

  float calcPressure(float _voltage);

  float returnVal();   // returns the current process val

  float sensorHistory[SENSOR_BUFFER_SIZE];
  //std::vector<float> sensorHistory;

  void updateHistory(float _sensorVal);
  float calAverage();
  float calcMin();
  float calcMax();
  float calcDxDy();
  float calcLMS();

  char sensorID[32] = { " sensor_xx " };
  char process_units[16] = { " unit " };
  char ADC_units[16] = {" unit "};

  bool calSet = false;
  struct calData {
    float offset;
    float factor;
  } cal;

private:
  int buggy;
};


#endif