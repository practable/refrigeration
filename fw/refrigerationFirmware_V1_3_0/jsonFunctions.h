/*   jsonFunctions

  All functions relating to JSON messages that are not wrapped up in state machine



*/


#if PRETTY_PRINT_JSON == true
  #pragma JSON set to Pretty Print! - May experience problems with Machine Parsing!
  char newline[3] = {"\n"};
#else
  #pragma JSON set to standard JSON output - For human readability try enabling Pretty Print!
  char newline[3] = {" "};
#endif



void build_json() {
  char json_header[] = "\"{";
  char json_buffer[JSON_BUFFER_SIZE] = { "" };  // this needs to be sized correctly 512 is too small 600 seems to work for now
  char float_buffer[16];
  char json_footer[] = "}\"";
  char valves[] = "valves";
  char relays[] = "relays";
  char sensors[] = "sensors";
  char temperature[] = "temperature";
  char pressure[] = "pressure";
  char misc[] = "misc";
  char s_status[] = "status";


  // start json string building
  sprintf(json_buffer, "%s%s  \"timestamp\" : %lu,", json_header, newline, sampleTimestamp);


  // load valve data
  sprintf(json_buffer, "%s%s  \"%s\" : {", json_buffer,newline, valves);
  for (int i = 0; i < 8; i++) {
    sprintf(json_buffer, "%s%s    \"V%i\" : %i,", json_buffer,newline, i + 1, bool(adam6052_A.g_coilState & 1 << i));  // fancy binary operation to bitmask the valvestate variable with a power of 2 to get true or false for each valve based on valvestate int
  }
  sprintf(json_buffer, "%s%s  },", json_buffer, newline);

  //load power relay data
  sprintf(json_buffer, "%s%s  \"%s\" : {", json_buffer,newline, relays);
  for (int i = 0; i < 3; i++) {
    sprintf(json_buffer, "%s%s   \"%s\" : %i,", json_buffer,newline, relay_names[i], bool(adam6052_B.g_coilState & 1 << i));
  }
  sprintf(json_buffer, "%s%s  },", json_buffer,newline);

  // Load sensor data
  sprintf(json_buffer, "%s%s  \"%s\" : {", json_buffer,newline, sensors);

  // load pressure sensors
  sprintf(json_buffer, "%s%s    \"%s\" : {", json_buffer,newline, pressure);
  for (int i = 0; i < NUM_PRESSURE_SENSORS; i++) {
    dtostrf(ps_vals[i], 6, 2, float_buffer);
    sprintf(json_buffer, "%s%s      \"PS%i\" : %6s,", json_buffer,newline, i + 1, float_buffer);
  }
  sprintf(json_buffer, "%s%s    },", json_buffer, newline);


  // load temp sensors
  sprintf(json_buffer, "%s%s    \"%s\" : {", json_buffer,newline, temperature);
  for (int i = 0; i < NUM_TEMP_SENSORS; i++) {
    dtostrf(ts_vals[i], 6, 2, float_buffer);
    sprintf(json_buffer, "%s%s      \"TS%i\" : %6s,", json_buffer,newline, i + 1, float_buffer);
  }
  sprintf(json_buffer, "%s%s    },", json_buffer, newline);


  // load misc sensors
  sprintf(json_buffer, "%s\%s    \"%s\" : {", json_buffer,newline, misc);
  for (int i = 0; i < 5; i++) {  //# Changed loop here from i < 4 to i < 5 due to additional datapoint
    dtostrf(misc_vals[i], 6, 2, float_buffer);
    sprintf(json_buffer, "%s%s      \"%s\" : %6s,", json_buffer,newline, misc_names[i], float_buffer);
  }
  sprintf(json_buffer, "%s%s    }", json_buffer,newline);

  // close sensors
  sprintf(json_buffer, "%s%s  },", json_buffer,newline);

  // load status message
  sprintf(json_buffer, "%s%s\"%s\" : {", json_buffer,newline, s_status);
  sprintf(json_buffer, "%s%s    \"%s\" : %i,", json_buffer,newline, status_names[0], status.ok);
  sprintf(json_buffer, "%s%s    \"%s\" : \"%s\",", json_buffer,newline, status_names[1], status.state);
  sprintf(json_buffer, "%s%s    \"%s\" : %i,", json_buffer,newline, status_names[2], status.code);
  sprintf(json_buffer, "%s%s    \"%s\" : \"%s\"", json_buffer,newline, status_names[3], status.message);
  sprintf(json_buffer, "%s%s  }", json_buffer,newline);


  // close json string
  sprintf(json_buffer, "%s%s%s", json_buffer,newline, json_footer);

  if (PRINT_JSON) {
    Serial.println(json_buffer);
  }
}
