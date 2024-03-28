/*   sensorunctions

  All functions relating to sensor scaleing and signal processing



*/


void sensors_begin() {
  // init Temp Sensors
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    temp_s[i].setCalibration(0, 100, 0, 10);  // (process low, process high, voltage low, voltage high, postoffset) Linear sensor scaling
  }

  pressure_s[0].setCalibration(-0.8, 7, 1, 6, -0.48);  // (process low, process high, voltage low, voltage high, postoffset) Linear sensor scaling
  pressure_s[1].setCalibration(0, 30, 1, 6);           // (process low, process high, voltage low, voltage high) Linear sensor scaling
  pressure_s[2].setCalibration(0, 30, 1, 6);           // (process low, process high, voltage low, voltage high) Linear sensor scaling

  flow_s.setCalibration(0, 25, 0, 20);     // (process low, process high, current low, current high) Linear sensor scaling
  power_s.setCalibration(0, 1300, 0, 20);  // (process low, process high, current low, current high) Linear sensor scaling
  // No longer needed as using i2C sensor
  //  t_ambi.setCalibration(-10, 100, 4, 20);        // (process low, process high, current low, current high) Linear sensor scaling
  //  p_ambi.setCalibration(600, 1500, 4, 20);       // (process low, process high, current low, current high) Linear sensor scaling
  // Instead use!
  unsigned status;
  status = bme.begin(0x76);
 // Serial.print(F("{\"status\":\"BME280:"));
 // Serial.print(status);
 // Serial.println(F("\"}"));
  if (status == 0) {
    Serial.println(F("{\"error\":\" BME280 Error\"}"));
  } else {
 //   Serial.println(F("{\"status\":\" BME280 Detected\"}"));
  }
}



// #TODO: is it worth seperating misc vals into 2 different arrays now? - lets try not to


void sample_bme280() {
  misc_vals[2] = bme.readTemperature();        // °C
  misc_vals[3] = bme.readPressure() / 100.0F;  // hPa
  misc_vals[4] = bme.readHumidity();           // %
#if DEBUG_SAMPLING == true
  for (int i = 2; i < 5; i++) {  // changed loop from i < 4 to i < 2
    Serial.print(i);
    Serial.print(": ");
    Serial.print(misc_names[i]);
    Serial.print(F(" : "));
    Serial.print(misc_vals[i]);
    Serial.print(F(" "));
    Serial.println(misc_units[i]);
    delay(2000);
  }
#endif
}
