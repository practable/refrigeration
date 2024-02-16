/*   sensorunctions

  All functions relating to sensor scaleing and signal processing



*/


void sensors_begin() {
  // init Temp Sensors
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    temp_s[i].set_range_min(0, 0);  // (processVariable, measuredVal)
    temp_s[i].set_range_max(100, 10);
    temp_s[i].setCalibration();
  }
  for (int i = 0; i < NUM_PRESSURE_SENSORS; i++) {
    pressure_s[i].set_range_min(1, 0);
    pressure_s[i].set_range_max(6, 30);
    pressure_s[i].setCalibration();
  }
  flow_s.set_range_min(4, 0);
  flow_s.set_range_max(20, 25);
  flow_s.setCalibration();
  power_s.set_range_min(0, 0);
  power_s.set_range_max(20, 1053);
  power_s.setCalibration();
  // No longer needed as using i2C sensor
  //  t_ambi.set_range_min(4, -10);  // guessing at these values for now
  //  t_ambi.set_range_max(20, 100);
  //  t_ambi.setCalibration();
  //  p_ambi.set_range_min(4, 600);  // mBar
  //  p_ambi.set_range_max(20, 1500);
  //  p_ambi.setCalibration();
  // Instead use!
  unsigned status;
  status = bme.begin(0x76);
  Serial.print(F("BME280 Status: "));
  Serial.println(status);
  if (status == 0){
    Serial.println(F("BME280 Error"));
  } else {
    Serial.println(F("BME280 Detected"));
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
